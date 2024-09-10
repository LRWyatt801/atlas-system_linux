#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int directory_lister_init(dir_lister_t *parser,
						  const char *path)
{
	DIR *dir = NULL;

	if (!parser || !path)
		return(-1);

	dir = opendir(path);

	if (!dir)
		return(-1);

	parser->directory = dir;
	parser->path = path;
	parser->current_entry = NULL;
	parser->stop = 0;

	return(0);
}

int print_dir(dir_lister_t *parser)
{
	if (!parser)
		return(-1);

	while (next_entry(parser))
	{
		if (*parser->current_entry->d_name != '.')
			printf("%s ", parser->current_entry->d_name);
	}
	printf("\n");

	return(0);
}

struct dirent *next_entry(dir_lister_t *parser)
{
	struct dirent *next_entry = NULL;

	if (parser->stop)
		return(NULL);

	next_entry = readdir(parser->directory);

	if (next_entry)
		parser->current_entry = next_entry;
	else
	{
		parser->current_entry = NULL;
		parser->stop = 1;
	}

	return(next_entry);
}

void close_dir(dir_lister_t *parser)
{
	if (!parser)
		return;

	closedir(parser->directory);
	memset(parser, 0, sizeof(*parser));
	return;
}
