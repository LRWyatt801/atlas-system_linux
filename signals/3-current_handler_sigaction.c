#include "signals.h"

/**
 * current_handler_sigaction - Retrieves the current
 *							   handler of the SIGINT signal
 *
 * Return: A pointer to the current handler of the SIGINT signal
 */

void (*current_handler_sigaction(void))(int)
{
	struct sigaction current_action;

	if (sigaction(SIGINT, NULL, &current_action) == -1)
	{
		return (NULL);
	}
	return (current_action.sa_handler);
}
