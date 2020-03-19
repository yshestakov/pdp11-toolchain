/* OUTPUT_FORMAT("a.out-pdp11") */
OUTPUT_FORMAT("binary")
/* TARGET("pdp11-aout") */
ENTRY(start)
phys = 00001000;
SECTIONS
{
    .savhdr : AT(0) {
        SHORT(0); /* RAD50(VIR) of LINK /V opt is specified */
        SHORT(0); /* Virtual high limit if Linker /V option was used */
        SHORT(0); /* Job definition word ($JSX) bits. See Table 2–11 for bit definitions */
        SHORT(0); /* 006 */
        SHORT(0); /* 010 */
        SHORT(0); /* 012 */
        SHORT(0); /* 014 BPT trap PC(mapped monitors only) */
        SHORT(0); /* 016 BPT trap PSW (mapped monitors only) */
        SHORT(0); /* 020 IOT trap PC (mapped monitors only) */
        SHORT(0); /* 022 IOT trap PSW (mapped monitors only) */
        SHORT(0); /* 024 */
        SHORT(0); /* 026 */
        SHORT(0); /* 030 */
        SHORT(0); /* 032 Overlay definition word (SV.CVH) bits */
        SHORT(0); /* 034 Trap vector PC (TRAP) */
        SHORT(0); /* 036 Trap vector PSW (TRAP) */
        SHORT(start); /* 040 Program’s relative start address */
        SHORT(start); /* 042 Initial location of stack pointer (changed by /M option) */
        SHORT(0); /* 044 Job Status Word */
        SHORT(0); /* 046 USR swap address */
        _prg_high_limit = .;
        SHORT(0); /* 050 Program’s high limit */ 
        /* . = 0360; /* 0360-0377 Bitmap are */
    }
    .savbitmap 0360 : AT(0360) {
        /* 0360-0377 Bitmap are */
        SHORT(0200); /* FIXME */
        . = ALIGN(0400);
    }
    .text phys : AT(phys) {
        code = .;
        crt0.o(.text)
        *(.text)
        *(.rodata)
        . = ALIGN(0100);
    }
    .data : AT(phys + (data - code))
    {
      data = .;
      *(.data)
      . = ALIGN(0100);
    }
    .bss : AT(phys + (bss - code))
    {
      bss = .;
      *(.bss)
      . = ALIGN(0100);
    }
    end = .;
}

