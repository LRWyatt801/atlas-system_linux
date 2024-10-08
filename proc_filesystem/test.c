#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    int i = 0;
    __pid_t pid = getpid();
    char *name = "Holberton";
    char *heap_name = strdup(name);

    while (i < 200)
    {
        printf("[%d] [PID: %d] %s\n", i, pid, heap_name);
        sleep(2.5);
        i++;
    }
    free(heap_name);
    return (0);
}