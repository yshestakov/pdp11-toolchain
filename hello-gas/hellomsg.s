        .TITLE Say hello on console
        .IDENT "V00.00"

		.GLOBAL hellom, helloc
        .data
hellom: .ascii  "Hello world!\r"
        helloc = . - hellom

        .end   
