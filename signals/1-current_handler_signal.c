#include "signals.h"

/**
 * current_handler_signal - returns a pointer to the current handler
 * of the signal SIGINT
 *
 * Return: a pointer to the current handler of the signal SIGINT
 */

void (*current_handler_signal(void))(int)
{
	/*Declare a variable to store the original handler*/
	void (*original_handler)(int);

	/*Save the current SIGINT handler*/
	original_handler = signal(SIGINT, SIG_IGN);

	if (original_handler == SIG_ERR)
		return (NULL);

	/*Restore the original handler*/
	signal(SIGINT, original_handler);

	return (original_handler);
}
