#ifndef _HELLO_H
#define _HELLO_H 1

extern int puts(const char* msg);

// extern void rt11_ttyout(const char c)  __attribute__((always_inline));
extern int  rt11_print(const char* ptr); // __attribute__((always_inline));

#define RT11_TTYOUT(c) \
    asm (                   \
        "mov    %[input_c], r0\n\t" \
        "emt    0341\n\t"   \
        "bcs    .-2\n\t"    \
        :                   \
        : [input_c] "r" (c)           \
        : "r0", "cc" \
        )

extern void inline rt11_ttyout(const char c) 
{
    asm (
        // "movb   %0, r0\n\t"
        "emt    0341\n\t"
        "bcs    .-2\n\t"
//        "halt\n\t"
        :
        : "r" (c)
        );
}
int inline rt11_print(const char* ptr)
{
    asm (
        "emt    0351;\n\t"
//        "halt;\n\t"
        : 
        : "r" (ptr)
        );
}


//extern int rt11_jsw;

/*
   JSW =: 44    ;(.SYCDF) Job Status Word location
TCBIT$ =: 100   ;(.JSWDF) Return C-bit bit in JSW
TTSPC$ =: 10000 ;(.JSWDF) Special Mode bit in JSW
*/

#endif
