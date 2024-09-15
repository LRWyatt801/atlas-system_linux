#include "list.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * set_flags -
 */

void set_flags(dir_lister_t *parser, int argc, char **args)
{
	int i = 0;
	parser->flags = 0;
	parser->num_dirs = 0;

	for (; i < argc; i++)
	{
		if ((args[i][0]) == '-')
		{
			int pos = 1;
			while (args[i][pos] != '\0')
			{
				switch (args[i][pos])
				{
				case '1':
					parser->flags |= 1; /* 00000001 */
					break;

				case 'a':
					parser->flags |= 1 << 1; /* 00000010 */
					break;

				case 'A':
					parser->flags |= 1 << 2; /* 00000100 */
					break;

				case 'l':
					parser->flags |= 1 << 3; /* 00001000 */
					break;

				default:
					break;
				}
				pos++;
			}
		}
		else
			parser->num_dirs += 1;
	}
	parser->num_dirs -= 1; /* subtract one for program name */
	if (parser->num_dirs > 1)
		parser->flags |= 1 << 4; /* 00010000 */
}

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
	set_flags(&parser, argc, argv);

	while (argv)
	{
		/* if no directory is given set dirctory_path to '.'/current dir */
		if (argc == 1)
		{
			directory_path = ".";
			argv = NULL;
		}
		else if (parser.num_dirs == 1)
		{
			if (*argv[1] != '-')
				directory_path = argv[1];
			else
				directory_path = argv[2];
			parser.args_stop = 1;
		}
		else
		{
			++argv;
			directory_path = *argv;
		}
		if (directory_path == NULL)
			break;

		filetype = check_file_type(&parser, directory_path);
		if (filetype == ISFILE && !parser.args_stop)
			continue;
		else if (filetype == ISFILE && parser.args_stop)
			break;

		if (directory_lister_init(&parser, directory_path) == -1)
			error_handler(ERR_FAILURE_TO_OPEN_DIR, directory_path, parser.program_name);
		if (parser.num_dirs > 1)
			printf("%s: \n", directory_path);
		print_dir(&parser);
		close_dir(&parser);
		if (parser.num_dirs > 1)
			printf("\n");
		printf("%d\n", parser.flags);
		if (parser.args_stop)
			break;
	}
	return (EXIT_SUCCESS);
}
