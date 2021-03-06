#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
    struct stat st;
    int         blk_n, blk_f, blk_r;
    int         fd, idx;
    char        *ptr;
    uint16_t    hdr[0400];
    uint8_t     *bmap = ((uint8_t*)hdr) + 0360;

    if (argc == 1) {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(1);
    }
    if (stat(argv[1], &st) == -1) {
        perror("stat");
        exit(2);
    }
    ptr = strchr(argv[1], '.');
    if (ptr == NULL) {
        fprintf(stderr, "%s: is not .sav file\n", argv[1]);
        exit(3);
    }
    if (strncmp(ptr+1, "sav", 4) != 0) {
        fprintf(stderr, "%s: is not .sav file\n", argv[1]);
        exit(3);
    }
    blk_n = (st.st_size + 0777) / 01000;
    printf("%s size is %lld (%d blocks)\n", argv[1], st.st_size, blk_n);
    memset(hdr, 0, sizeof(hdr));
    blk_f = blk_n / 8;
    blk_r = blk_n % 8;
    for(idx=0; idx<blk_f; idx++) {
        bmap[idx] = 0377;
    }
    if (blk_r != 0) {
        bmap[idx] = 0377 ^ ((1<<(8-blk_r))-1);
    }
    /* 040 Program’s relative start address */
    hdr[020] = 01000;
    /* 042 Initial location of stack pointer (changed by /M option) */
    hdr[021] = 01000;
    /* 050 Program’s high limit */
    hdr[024] = st.st_size;
    fd = open(argv[1], O_RDWR);
    if (fd < 0) {
        perror("open");
        exit(3);
    }
    lseek(fd, 0, SEEK_SET);
    assert(sizeof(hdr)== 01000);
    write(fd, hdr, sizeof(hdr));
    close(fd);
    return 0;
}
