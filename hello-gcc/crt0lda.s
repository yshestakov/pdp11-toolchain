; 
     .TITLE CRT0 shim
        .IDENT "V00.00"

        # STACK = 0x1000
        STACK = 01000

		.data
$__progname:
		.asciz  "hello.rom"

args:
		.word	$__progname
		.word	0

        .text
        .GLOBAL _main
        .GLOBAL ___main
		.GLOBAL start
start:
        mov     $STACK, sp
		mov		$$__progname, r0
		emt		0351
		mov		$0, -(sp)		// env
		mov		$args, -(sp)	// args
		mov		$1, -(sp)		// argc
		jsr		pc, _main
		add		$6, sp
		emt		0350	// .EXIT
		halt

___main:
        rts     pc
// If no init section is available, when GCC compiles any function called
// @code{main} (or more accurately, any function designated as a program
// entry point by the language front end calling @code{expand_main_function}),
// it inserts a procedure call to @code{__main} as the first executable code
// after the function prologue.  The @code{__main} function is defined
// in @file{libgcc2.c} and runs the global constructors.
        .end   
