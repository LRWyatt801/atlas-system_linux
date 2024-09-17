#include "list.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * print_single_dir - prints the contents of the given directory
 * @parser: pointer to dir_lister_t struct, contains pointers to DIR
 *			and current_entry
 * @path: a given path to a directory or file
 *
 * Return: 0 on success otherwise -1
 */

int print_single_dir(dir_lister_t *parser, const char *path)
{
	int filetype;
	int (*printer)(dir_lister_t *);

	filetype = check_file_type(parser, path);
	if (filetype == ISFILE)
		return (0);
	else if (filetype == FILEERR)
		return (-1);
	if (directory_lister_init(parser, path) == -1)
	{
		error_handler(ERR_FAILURE_TO_OPEN_DIR, path, parser->program_name);
		return (-1);
	}
	printer = get_flag_func(parser->flags);
	printer(parser);
	close_dir(parser);

	return (0);
}

/**
 * print_multi_inputs - prints the contents of multiple given directoris
 * @parser: pointer to dir_lister_t struct, contains pointers to DIR
 *			and current_entry
 * @argc: number of CL inputs
 * @argv: matrix of CL inputs
 *
 * Return: 0 on success, otherwise -1
 */

int print_multi_inputs(dir_lister_t *parser,
					   int argc, char **argv)
{
	const char *input_path = NULL;
	int (*printer)(dir_lister_t *);
	int filetype;
	int i;

	parser->flags = parser->flags % 16;

	for (i = 1; i < argc; i++)
	{
		if (*argv[i] != '-') /* input is not flag */
			input_path = argv[i];
		else /* if input is flag continue */
			continue;
		filetype = check_file_type(parser, input_path);
		if (filetype == ISFILE)
			continue;
		else if (filetype == FILEERR)
			continue;
		if (directory_lister_init(parser, input_path) == -1)
		{
			error_handler(ERR_FAILURE_TO_OPEN_DIR, input_path, parser->program_name);
			continue;
		}
		printf("%s:\n", input_path);
		printer = get_flag_func(parser->flags);
		printer(parser);
		printf("\n");
		close_dir(parser);
	}
	return (0);
}

/**
 * get_flag_func - evaluates any given flags and returns func pointer
 * @flag: given flag
 *
 * Return: pointer to printer function
 */

int (*get_flag_func(unsigned int flags))(dir_lister_t *)
{
	static const print_flags_t flag_table[] = {
		{1, print_oneperline},
		{0, print_dir}};
	int i = 0;

	while (flag_table[i].flag_value != 0)
	{
		if (flag_table[i].flag_value == flags)
		{
			return (flag_table[i].printer); /* currect op */
		}
		i++;
	}
	return (print_dir); /* no match function */
}