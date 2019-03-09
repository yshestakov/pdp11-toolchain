
# GNU bintuils and PDP11

hello

## Dependencies

 - GNU binutils
 - bin2load  https://github.com/jguillaumes/retroutils/tree/master/bin2load
 - simh

## Compile hello-world using GNU as

    %.o:    %.s
        pdp11-aout-as -o $@ $<

## Link into static file

    hello.out: $(OBJS)
        pdp11-aout-ld -T pdp11-aout.ld -o $@ $(OBJS)

## Run in the simh

	$(SIMH) simh.ini

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
