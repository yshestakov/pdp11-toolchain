OUTPUT_FORMAT("a.out-pdp11")
ENTRY(start)
STARTUP(crt0rt.o)
phys = 00001000;
SECTIONS
{
    .text phys : AT(phys) {
        code = .;
/*        crt0rt.o(.text)  => STARTUP(...) */
        *(.text)
        *(.rodata)
        *(.data)
        . = ALIGN(010);
    }
    /*
    .data : AT(phys + (data - code))
    {
      data = .;
      . = ALIGN(010);
    }
    .bss : AT(phys + (bss - code))
    {
      bss = .;
      *(.bss)
      . = ALIGN(010);
    }
    */
    end = .;
}

