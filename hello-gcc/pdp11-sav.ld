/* OUTPUT_FORMAT("a.out-pdp11") */
OUTPUT_FORMAT("binary")
/* TARGET("pdp11-aout") */
ENTRY(start)
phys = 00;
SECTIONS
{
    .savhdr : AT(0) {
        savhdr.o
    }
    savend = .;
    .text : AT(phys + code)
    {
        code = .;
        crt0rt.o(.text)
        *(.text)
        *(.rodata)
        . = ALIGN(010);
    }
    .data : AT(phys + data)
    {
      data = .;
      *(.data)
      . = ALIGN(010);
    }
    .bss : AT(phys + bss)
    {
      bss = .;
      *(.bss)
      . = ALIGN(010);
    }
    end = .;
}

