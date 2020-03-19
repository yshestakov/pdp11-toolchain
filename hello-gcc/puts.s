        .TITLE puts: send a string to the system console RT11
        .IDENT "V01.00"

		.data

        .text
        .GLOBAL _puts
_puts:
;       .GLOBAL _msg
		mov		_msg, r0
		mov		2(sp), r0
		emt		0351
        rts     pc

.end
;--- https://en.wikipedia.org/wiki/MACRO-11
