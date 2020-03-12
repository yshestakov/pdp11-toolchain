extern void putconch(char c);

static char msg[] = "Hello, GCC world!\n";

void main(int argc, char** argv)
{
    char* p = msg;
    for (int c = *p++; c != '\0'; c = *p++) {
        putconch(c);
    }
}
