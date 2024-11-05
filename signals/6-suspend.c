#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

static sig_atomic_t signal_recieved;

/**
 * sigint_handler - handles the SIGINT signal
 *
 * @signum: signal number
 */

void sigint_handler(int signum)
{
	printf("Caught %d\n", signum);
	signal_recieved = 1;
}

/**
 * main - entry point
 *
 * Return: 0 on success, otherwise -1
 */

int main(void)
{
	struct sigaction act;

	act.sa_handler = sigint_handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	if (sigaction(SIGINT, &act, NULL) == -1)
		return (EXIT_FAILURE);

	pause();

	if (signal_recieved)
	{
		printf("Signal received\n");
		return (EXIT_SUCCESS);
	}
}
