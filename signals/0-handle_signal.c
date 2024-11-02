#include "signal.h"

#include <stdio.h>

/**
 * signal_message - print a message
 * @sig: signal number
 *
 * Return: void
 */

void signal_message(int sig)
{
    printf("Gotcha! [%d]\n", sig);
}

/**
 * handle_signal - handle ctrl+c
 * 
 * Return: int - SIGINT
 */

int handle_signal(void)
{
    if (signal(SIGINT, signal_message) == SIG_ERR)
    {
        return (-1);
    }
	return (0);
}
