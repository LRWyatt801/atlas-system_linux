#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

/**
 * main - Entry point for signal send
 * @argc: number of arguments
 * @argv: arguments
 *
 * Return: 0 on success, 1 on failure
 */

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: %s <pid>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	pid_t pid = (pid_t)atoi(argv[1]);

	if (kill(pid, SIGINT) == -1)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}
