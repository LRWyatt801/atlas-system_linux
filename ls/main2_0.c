#include "list.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * set_flags - sets a bit map for given CL input flags
 * @parser: pointer to dir_lister_t struct, contains pointers to DIR
 *			and current_entry
 * @argc: number of CL inputs
 * @argv: matrix of CL inputs
 */

void set_flags(dir_lister_t *parser, int argc, char **argv)
{
	int i = 0;

	parser->flags = 0;
	parser->num_dirs = 0;

	for (; i < argc; i++)
	{
		if ((argv[i][0]) == '-')
		{
			int pos = 1;

			while (argv[i][pos] != '\0')
			{
				switch (argv[i][pos])
				{
				case '1':
					parser->flags |= 1; /* 00000001 = 1*/
					break;
				case 'a':
					parser->flags |= 1 << 1; /* 00000010 = 2*/
					break;
				case 'A':
					parser->flags |= 1 << 2; /* 00000100 = 4 */
					break;
				case 'l':
					parser->flags |= 1 << 3; /* 00001000  = 8 */
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

	if (parser->num_dirs > 1)	 /* flag for multiple dirs input*/
		parser->flags |= 1 << 4; /* 00010000 = 16 */
}

/**
 * main - entry point for 'ls' program
 * @argc: number of CL inputs
 * @argv: matrix of CL inputs
 *
 * Return: 'EXIT_SUCCESS' or 'EXIT_FAILURE'
 */

int main(int argc, char **argv)
{
	dir_lister_t parser;

	parser.program_name = argv[0];
	set_flags(&parser, argc, argv);

	if (parser.flags < MULTIPLEDIRS) /* check for multiple directory input*/
	{
		const char *directory_path = NULL;

		/* if no directory is given set dirctory_path to '.'/current dir */
		if (parser.num_dirs == 0)
			directory_path = ".";
		else
		{
			if (*argv[1] != '-')
				directory_path = argv[1];
			else
				directory_path = argv[2];
		}
		if (print_single_dir(&parser, directory_path) == -1)
			return (EXIT_FAILURE);
	}
	else if (print_multi_inputs(&parser, argc, argv) == -1)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}
