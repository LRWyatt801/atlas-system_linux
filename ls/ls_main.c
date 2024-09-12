#include "list.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define IS_REG(mode) (((mode) & S_IFMT) == S_IFREG)

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
	struct stat path_info;

	/* if no directory path input is given default to '.'/current dir */
	if (argc == 1)
		directory_path = ".";
	/* otherwise use directory path input */
	else
		directory_path = argv[1];
	
	if (lstat(directory_path, &path_info) == -1)
	{
		fprintf(stderr, "%s: cannot access %s: No such file or directory\n",
				argv[0], directory_path);
		return (EXIT_FAILURE);
	}
	
	/* check for file or dir */
	if (IS_REG(path_info.st_mode))
	{
		printf("%s\n", directory_path);
		return (EXIT_SUCCESS);
	}

	if (directory_lister_init(&parser, directory_path) == -1)
	{
		fprintf(stderr, "Failure to open directory '%s'\n",
				directory_path);
		return (EXIT_FAILURE);
	}

	print_dir(&parser);
	close_dir(&parser);
	return (0);
}
