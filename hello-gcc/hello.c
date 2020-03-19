/*
 * hello word
 */
#include "hello.h"

const char* msg = "\tHello, GCC world?!\r\n";

// extern int putchar(int c);

int main(int argc, char** argv)
{
    for(register int c=0; c< 8; c++)
        RT11_TTYOUT('@');
    RT11_TTYOUT('\r');
    rt11_ttyout('\n');
    const char* p = msg;
    while (*p != '\0')
        RT11_TTYOUT(*p++);
    puts(msg);
    rt11_print(msg);
    return 0;
}
