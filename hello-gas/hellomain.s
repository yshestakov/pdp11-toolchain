
     .TITLE Say hello on console
        .IDENT "V00.00"

        .GLOBAL _main
        .GLOBAL _putconch

        .text
_main:
		mov		r1, -(sp)
		mov		r2, -(sp)
        mov     $hellom, r1
        mov     $helloc, r2
10$:    movb    (r1), r0
        jsr     pc, _putconch
        dec     r2
        beq     99$
        inc     r1
        jmp     10$

99$:	nop
		mov		(sp)+, r2
		mov		(sp)+, r1
        rts     pc

        .data
hellom: .ascii  "Hello world!"
        helloc = . - hellom

        .end   
