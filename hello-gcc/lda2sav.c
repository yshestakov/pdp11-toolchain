#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdint.h>

/*
 * AA-PD6PA-TC_RT-11_Volume_and_File_Formats_Manual_Aug91.pdf
 *
 * 2.5 Absolute Binary File Format (.LDA)
 */
struct lda_hdr_s {
    uint8_t     _o0; // == 1
    uint8_t     _o1; // == 0
    uint8_t     bcl; // lsb of byte count
    uint8_t     bch; // msb of byte count
    uint8_t     adl; // lsb of load address
    uint8_t     adh; // msb of load address
};

#define LE2H(lsb, msb) (msb*256+lsb)

#define P_ERR(prog, lda_fn) \
			(void)fprintf(stderr, \
				"%s: %s: %s\n", prog, lda_fn, strerror(errno))

static char*    prog = NULL;
static char*    lda_fn = NULL;
static char*    sav_fn = NULL;
static int      verbose = 0;

void usage()
{
    fprintf(stderr, "Usage: %s -o file.sav file.lda\n", prog);
	exit(1);
}

ssize_t read_hdr(int fd, struct lda_hdr_s* hdr_p)
{
    int pos = lseek(fd, 0, SEEK_CUR);
    ssize_t rc = read(fd, hdr_p, sizeof(struct lda_hdr_s));
    if (rc < 0) {
        P_ERR(prog, lda_fn);
	}
    if (verbose) {
        printf("read_hdr(pos 0o%06o): o0/o1 = %d/%d bc=0%05o ad=0%05o (rc=%ld)\n",
                pos,
                hdr_p->_o0, hdr_p->_o1,
                LE2H(hdr_p->bcl, hdr_p->bch),
                LE2H(hdr_p->adl, hdr_p->adh),
                rc);
    }
    assert(hdr_p->_o0 == 1 && hdr_p->_o1 == 0);
    return rc;
}

int main(int argc, char** argv)
{
    struct stat st;
    int     ch, fd, exit_code = 0;
    ssize_t rc;
    struct lda_hdr_s   hdr;
    static uint8_t     buf[65536];
    uint8_t            *bmap = buf + 0360;
    uint16_t           *sav_hdr = (uint16_t*)buf;
    int                 sav_size = 512;
    int         blk_n, blk_f, blk_r;
    int         idx;

    memset(buf, 0, sizeof(buf));
	prog = argv[0];
	while ((ch = getopt(argc, argv, "vo:")) != -1) {
			switch (ch) {
                case 'v':
                    verbose = 1;
                    break;
			    case 'o':
					sav_fn = optarg;
					break;
			    case '?':
			    default:
					usage();
			}
	}
	argc -= optind;
	argv += optind;

	if (argc != 1) {
		usage();
	}
	lda_fn = argv[0];
    if (verbose)
	    printf("[I] lda_fn: %s\tsav_fn: %s\n", lda_fn, sav_fn);

	if ((fd = open(lda_fn, O_RDONLY, 0)) < 0) {
            P_ERR(prog, lda_fn);
			exit(2);
	}
    if ((rc = read_hdr(fd, &hdr)) < 0) {
        exit_code = 3;
		goto l_exit;
	}
    /* main loop to read LDA blocks */
    memset(buf, 0, sizeof(buf));
    while (LE2H(hdr.bcl, hdr.bch) != 6) {
        uint8_t  csum0 = 0;
        uint8_t  csum = 0;
        char*   ptr = (char*)&hdr;
        for(int i=0; i < sizeof(hdr); i++)
            csum += *ptr++;
        int offs = LE2H(hdr.adl, hdr.adh);
        int blk_sz = LE2H(hdr.bcl, hdr.bch) - sizeof(hdr);
        read(fd, buf + offs, blk_sz);
        if (verbose)
            printf("[I] read at offs %05o %d bytes\n", offs, blk_sz);
        sav_size += blk_sz;
        read(fd, &csum0, 1);
        for(int i=0; i< blk_sz; i++) {
            csum += buf[offs+i];
        }
        csum = 0 - (csum & 0377);
        if (verbose) {
            printf("csum0: 0%03o / 0x%02x <->  0%03o / 0x%02x\n", csum0, csum0, csum, csum);
        }
        assert(csum == csum0);
        if ((rc = read_hdr(fd, &hdr)) < 0) {
            exit_code = 3;
            goto l_exit;
        }
    }
    // set bitmap:
    blk_n = (sav_size + 0777) / 01000;
    if (verbose) {
        printf("[I] %s size is %d (%d blocks)\n", sav_fn, sav_size, blk_n);
    }
    blk_f = blk_n / 8;
    blk_r = blk_n % 8;
    for(idx=0; idx < blk_f; idx++) {
        bmap[idx] = 0377;
    }
    if (blk_r != 0) {
        bmap[idx] = 0377 ^ ((1<<(8-blk_r))-1);
    }
    /* 040 Program’s relative start address */
    sav_hdr[020] = 01000;
    /* 042 Initial location of stack pointer (changed by /M option) */
    sav_hdr[021] = LE2H(hdr.adl, hdr.adh);
    /* 050 Program’s high limit */
    sav_hdr[024] = sav_size;
    close(fd);
    fd = creat(sav_fn, 0644); // O_WRONLY|O_CREAT);
    if (fd < 0) {
        P_ERR(prog, sav_fn);
        exit(4);
    }
    if (verbose)
        printf("[I] write %d to output\n", sav_size);
    write(fd, buf, sav_size);

l_exit:
	close(fd);
}
