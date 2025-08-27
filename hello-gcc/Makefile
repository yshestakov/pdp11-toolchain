OBJS:=	hello.o puts.o
SIMH:= pdp11
CC:=pdp11-aout-gcc
# SIMH := simh-pdp11
# built from sources
# SIMH := ../simh/BIN/pdp11

all:	lda2sav crt0lda.o crt0rt.o hello.lda hello.hex hello.sav

savbmap:	savbmap.c
	gcc -o savbmap savbmap.c
lda2sav:	lda2sav.c
	gcc -o lda2sav lda2sav.c

#savhdr.o:	savhdr.s
#	gcc -o $@ $<

%.s:	%.c
	pdp11-aout-gcc -O1 -mbm2 -S -o $@  $<

%.o:	%.c
	pdp11-aout-gcc -O1 -mbm2 -c -o $@ $<
	# pdp11-aout-gcc -m10 -c -o $@ $<
	#  -Wl,-Tpdp11-sav.ld -nostdlib 

%.o:	%.s
	pdp11-aout-as -o $@ $<

%.lda:	%.out
	bin2load -v -a -f $< -o $@

hello.sav:	hello.lda
	./lda2sav -v -o $@ $<

hello2.sav:	hello2.lda
	./lda2sav -v -o $@ $<

# hello.out: $(OBJS) crt0lda.o
hello.out: $(OBJS) crt0rt.o pdp11-aout.ld
	pdp11-aout-ld -T pdp11-aout.ld -o $@ $(OBJS) -Map=hello.out.map

hello2.out: $(OBJS) crt0rt.o pdp11-aout.ld
	pdp11-aout-ld -T pdp11-aout2.ld -o $@ $(OBJS) -Map=hello2.out.map

bhello.bin: $(OBJS) crt0lda.o pdp11-bin.ld
	pdp11-aout-ld -T pdp11-bin.ld -o $@ $(OBJS) -Map=bhello.out.map

hello.hex: hello.out
	pdp11-aout-objcopy -O ihex $< $@

hello.bin: hello.out
	pdp11-aout-objcopy -O binary $< $@

#hello.mcs: hello.out
#	pdp11-aout-objcopy -O mcs  $< $@
hello.srec: hello.out
	pdp11-aout-objcopy -O srec $< $@

rl0.dsk:
	cp ${RT11}/rt11os.dsk rl0.dsk

run:	hello.sav rl0.dsk
	# cp rl0.dsk-orig rl0.dsk
	rt11dsk d rl0.dsk hello.sav
	rt11dsk a rl0.dsk hello.sav
	$(SIMH) run-sav.ini

run2:	hello2.sav rl0.dsk
	# cp rl0.dsk-orig rl0.dsk
	rt11dsk d rl0.dsk hello2.sav
	rt11dsk a rl0.dsk hello2.sav
	$(SIMH) run-sav.ini

clean:
	@-rm hello.lda hello.out *.o

