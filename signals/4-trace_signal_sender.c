#include "signals.h"

/**
 * sigquit_handler - Prints a message to stdout when a signal is received
 *
 * @sig: The signal number
 * @info: Pointer to a siginfo_t struct
 * @ucontext: Pointer to a ucontext_t struct
 */

void sigquit_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)ucontext;
	printf("SIGQUIT sent by %d\n", info->si_pid);
}

/**
 * trace_signal_sender - Prints a message to stdout when a signal is received
 *
 * Return: 0 on success, or -1 on error
 */

int trace_signal_sender(void)
{
	struct sigaction act;

	act.sa_sigaction = sigquit_handler;
	act.sa_flags = SA_SIGINFO;

	if (sigaction(SIGQUIT, &act, NULL) == -1)
		return (-1);
	return (0);
}
