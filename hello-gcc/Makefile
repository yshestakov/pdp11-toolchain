OBJS:=	hello.o puts.o
SIMH := simh-pdp11
# built from sources
# SIMH := ../simh/BIN/pdp11

all:	crt0lda.o crt0rt.o lda2sav hello.lda hello.hex hello.sav 

savbmap:	savbmap.c
	gcc -o savbmap savbmap.c

%.o:	%.c
	pdp11-aout-gcc -mbm2 -c -o $@ $<
	# pdp11-aout-gcc -m10 -c -o $@ $<
	#  -Wl,-Tpdp11-sav.ld -nostdlib 

%.o:	%.s
	pdp11-aout-as -o $@ $<

%.lda:	%.out
	bin2load -a -f $< -o $@

hello.sav:	hello.lda
	./lda2sav -o $@ $<

# hello.out: $(OBJS) crt0lda.o
hello.out: $(OBJS) crt0rt.o
	pdp11-aout-ld -T pdp11-aout.ld -o $@ $(OBJS) -Map=hello.out.map 

hello.hex: hello.out
	pdp11-aout-objcopy -O ihex $< $@

hello.bin: hello.out
	pdp11-aout-objcopy -O binary $< $@

#hello.mcs: hello.out
#	pdp11-aout-objcopy -O mcs  $< $@
hello.srec: hello.out
	pdp11-aout-objcopy -O srec $< $@

run:	hello.sav rl0.dsk
	# cp rl0.dsk-orig rl0.dsk
	rt11dsk d rl0.dsk hello.sav
	rt11dsk a rl0.dsk hello.sav
	$(SIMH) run-sav.ini

clean:
	@-rm hello.lda hello.out *.o

