#include <stdio.h>

int main(int argc, char **argv)
{
    int argcount = 0;
    for (; argcount < argc; argcount++)
    {
        ++argv;
        printf("%s\n", *argv);
        printf("test\n");
    }
    return (0);
}