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

		if (directory_lister_init(&parser, directory_path) == -1)
			error_handler(ERR_FAILURE_TO_OPEN_DIR, directory_path, parser.program_name);
		if (argc > 2)
			printf("%s: \n", directory_path);
		print_dir(&parser);
		close_dir(&parser);
		if (argc > 2)
			printf("\n");
	}
	return (EXIT_SUCCESS);
}
