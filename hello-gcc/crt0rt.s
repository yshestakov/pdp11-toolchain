; 
     .TITLE CRT0RT shim
        .IDENT "V00.00"

        # STACK = 0x1000
        STACK = 01000

        .text
        .GLOBAL _main
		.GLOBAL start
start:
        mov     $STACK, sp
// debug print
		mov		$$__progname, r0
		emt		0351
		mov		$0, -(sp)		// env
		mov		args, -(sp)	// args
		mov		$1, -(sp)		// argc
		jsr		pc, _main
		add		$6, sp
		// .word	0104350		// .EXIT
		emt		0350	// .EXIT
		nop

        .GLOBAL ___main
___main:
		rts		pc
		.even
		// .data
$__progname:
		.asciz  "hello.rom"

args:
		.word	$__progname
		.word	0

        .end   
