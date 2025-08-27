/*
 * hello word
 */
// #include "hello.h"
volatile int foobar;
const char msg[] = "\tHello, GCC world!\r\n";
// const char* msg = _msg;
volatile int barfoo;

extern int puts(const char* msg);
// extern int putchar(int c);
void rt11_ttyout(char c)
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

int rt11_print(const char* ptr) 
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

int main(int argc, char** argv)
{
    /*
    int *rt11_jsw = (int*)044;
    *rt11_jsw |= 010000;
    */
    for(register int c=0; c< 8; c++)
        rt11_ttyout('@');
    rt11_ttyout('\r'); 
    rt11_ttyout('\n');
#if 0
    const char* p = msg;
    int cnt = 0;
    for (register char c = *p++; c != '\0'; c = *p++) {
        ++cnt;
        rt11_ttyout(c);
    }
    for(register int c=0; c< 8; c++)
        rt11_ttyout((int)'@'+cnt);
#else
    rt11_print(msg);
#endif
    rt11_ttyout('\r'); 
    rt11_ttyout('\n');
    
    rt11_ttyout('='); 
    rt11_ttyout('\r'); 
    rt11_ttyout('\n');

    // rt11_print(msg);
    puts(msg);
    rt11_ttyout('='); 
    rt11_ttyout('\r'); 
    rt11_ttyout('\n');
    return 0;
}
