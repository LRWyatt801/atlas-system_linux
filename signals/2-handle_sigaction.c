#include "signals.h"

/**
 * signal_caught - print a message
 * @sig: signal number
 *
 * Return: void
 */

void signal_caught(int sig)
{
	printf("Gotcha! [%d]\n", sig);
	fflush(stdout);
}

/**
 * handle_sigaction - set handler for SIGINT
 *
 * Return: 0 on success, -1 on error
 */
int handle_sigaction(void)
{
	struct sigaction act;
	act.sa_handler = signal_caught;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if(sigaction(SIGINT, &act, NULL) == -1)
		return (-1);
	
	return (0);
}