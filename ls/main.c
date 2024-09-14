#include "list.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * main - entry point for 'ls' program
 * @argc: number of CL inputs
 * @argv: matrix of argument inputs
 *
 * Return: 'EXIT_SUCCESS' or 'EXIT_FAILURE'
 */

int main(int argc, char **argv)
{
	dir_lister_t parser;
	const char *directory_path = NULL;
	int filetype = 0;

	parser.program_name = argv[0];

	while (argv)
	{
		/* if no directory is given set dirctory_path to '.'/current dir */
		if (argc == 1)
		{
			directory_path = ".";
			argv = NULL;
		}
		else
		{
			++argv;
			directory_path = *argv;
		}
		if (directory_path == NULL)
			break;

		filetype = check_file_type(&parser, directory_path);
		if (filetype == ISFILE)
			continue;
		else if (filetype == FILEERR)
			return (EXIT_FAILURE);

		if (directory_lister_init(&parser, directory_path) == -1)
		{
			fprintf(stderr, "Failure to open directory '%s'\n",
					directory_path);
			return (EXIT_FAILURE);
		}

		print_dir(&parser);
		close_dir(&parser);
	}
	return (EXIT_SUCCESS);
}
