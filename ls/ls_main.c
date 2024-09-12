#include "list.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * main - entry point for 'ls' program
 * @argc: number CL inputs
 * @argv: matrix of argument inputs
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */

int main(int argc, char **argv)
{
	dir_lister_t parser;
	const char *directory_path = NULL;

	/* if no directory path input is given default to '.'/current dir */
	if (argc == 1)
		directory_path = ".";
	/* otherwise use directory path input */
	else
		directory_path = argv[1];

	directory_lister_init(&parser, directory_path);

	print_dir(&parser);
	close_dir(&parser);
	return (0);
}
