; 
     .TITLE CRT0 shim
        .IDENT "V00.00"

        STACK = 0x1000

		.data
$__progname:
		.asciz  "hello.rom"

args:
		.word	$__progname
		.word	0

        .text
        .GLOBAL _main
		.GLOBAL start
start:
        mov     $STACK, sp
		mov		$0, -(sp)		// env
		mov		$args, -(sp)	// args
		mov		$1, -(sp)		// argc
		jsr		pc, _main
		add		$6, sp
		halt
		nop

        .end   
