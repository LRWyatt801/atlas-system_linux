#include "list.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int print_single_dir(dir_lister_t *parser, const char *path)
{
	int filetype;

	filetype = check_file_type(parser, path);
	if (filetype == ISFILE)
		return (0);
	else if (filetype == FILEERR)
		return (-1);
	if (directory_lister_init(parser, path) == -1)
	{
		error_handler(ERR_FAILURE_TO_OPEN_DIR, path, parser->program_name);
		close_dir(parser);
		return (-1);
	}
	print_dir(parser); /* repalce with function pointer for flags */
	close_dir(parser);

	return (0);
}

int print_multi_input_dirs(dir_lister_t *parser,
						   int argc, char **argv)
{
	const char *input_path = NULL;
	int filetype;
	int i;

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
			close_dir(parser);
			continue;
		}
		printf("%s:\n", input_path);
		print_dir(parser); /*replace with function pointer for flags*/
		printf("\n");
		close_dir(parser);
	}
	return (0);
}