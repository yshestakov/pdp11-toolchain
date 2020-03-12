
# GNU bintuils plus GCC and PDP11

hello

## Dependencies

 - GCC 8.2.0+
 - GNU binutils
 - bin2load  https://github.com/jguillaumes/retroutils/tree/master/bin2load
 - simh

## Compile hello-world

There is the `Makefile` with rules to build the `hello` application

    make

## Generate IHEX or SREC images

    make hello.hex

or

    make hello.srec


## Run in the simh

	$(SIMH) simh.ini

or simply run it:

    make run

Content of simh.ini:

    set cpu 11/05 64K idle
    set console wru=035
    set tto 8b
    sh cpu
    load hello.lda
    e pc
    e -m 001000:01100
    g 
    e sp
    bye


## Decompile IHEX

    pdp11-aout-objdump -m pdp11 -D hello.hex

## Decompile SREC

    pdp11-aout-objdump -m pdp11 -D hello.srec
