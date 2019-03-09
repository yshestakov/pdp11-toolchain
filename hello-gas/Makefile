OBJS:=	hellomain.o putconch.o crt0.o
SIMH := simh-pdp11
# built from sources
# SIMH := ../simh/BIN/pdp11

all:	hello.lda hello.hex

%.o:	%.s
	pdp11-aout-as -o $@ $<

%.lda:	%.out
	bin2load -a -f $< -o $@

hello.out: $(OBJS)
	pdp11-aout-ld -T pdp11-aout.ld -o $@ $(OBJS)

hello.hex: hello.out
	pdp11-aout-objcopy -O ihex $< $@

#hello.mcs: hello.out
#	pdp11-aout-objcopy -O mcs  $< $@
hello.srec: hello.out
	pdp11-aout-objcopy -O srec $< $@

run:	hello.lda
	$(SIMH) simh.ini

clean:
	@-rm hello.lda hello.out *.o
