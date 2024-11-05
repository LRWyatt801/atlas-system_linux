#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, -1 on failure
 */

int main(int argc, char **argv)
{
	const char *signum = (const char *)argv[1];
	const char *signame = NULL;

	if (argc == 1)
	{
		printf("Usage: %s <signum>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	signame = strsignal(atoi(signum));
	if (signame != NULL)
		printf("%s: %s\n", signum, signame);
	return (EXIT_SUCCESS);
}
