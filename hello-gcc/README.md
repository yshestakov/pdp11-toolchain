
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


## some notes

    In [20]: oct(0xff ^ ((1<<(8-n))-1))
    Out[20]: '0360'

    In [21]: n=2

    In [22]: oct(0xff ^ ((1<<(8-n))-1))
    Out[22]: '0300'

    In [23]: oct(0xff ^ ((1<<(32-n))-1))
    Out[23]: '07777777400'

    In [24]: oct(0xffffffff ^ ((1<<(32-n))-1))
    Out[24]: '030000000000'

