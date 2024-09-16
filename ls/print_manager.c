#include "list.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int print_single_dir(dir_lister_t *parser, const char *path)
{
	if (check_file_type(parser, path) == ISFILE)
		return (0);
	if (directory_lister_init(parser, path) == -1)
		error_handler(ERR_FAILURE_TO_OPEN_DIR, path, parser->program_name);
	print_dir(parser);
	close_dir(parser);

	return (0);
}

int print_multi_input_dirs(dir_lister_t *parser,
						   int argc, char **argv)
{
	const char *input_path = NULL;
	int i;

	for (i = 1; i < argc; i++)
	{
		if (*argv[i] != '-')
			input_path = argv[i];
		else
			continue;
		printf("%s:\n", argv[i]);
		print_single_dir(parser, input_path);
		printf("\n");
	}
	return (0);
}