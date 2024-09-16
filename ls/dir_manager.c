#include "list.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * directory_lister_init - initializes values for parser struct
 * @parser: pointer to dir_lister_t struct, contains pointers to DIR
 *			and current_entry
 * @path: path of directory
 *
 * Return: 0 on success or -1 on failure
 */

int directory_lister_init(dir_lister_t *parser,
						  const char *path)
{
	DIR *dir = NULL;

	if (!parser || !path)
		return (-1);

	dir = opendir(path);

	if (!dir)
		error_handler(ERR_CANNOT_ACCESS_DIR, path, parser->program_name);

	parser->directory = dir;
	parser->path = path;
	parser->current_entry = NULL;
	parser->stop = 0;

	return (0);
}

/**
 * print_dir - prints current directory
 * @parser: pointer to dir_lister_t struct, contains pointers to DIR
 *			and current_entry
 *
 * Return: 0 on success or -1 on failure
 */

int print_dir(dir_lister_t *parser)
{
	if (!parser)
		return (-1);

	while (next_entry(parser))
	{
		if (*parser->current_entry->d_name != '.')
			printf("%s ", parser->current_entry->d_name);
	}
	printf("\n");

	return (0);
}

/**
 * next_entry - loads the next entry in 'DIR' struct
 * @parser: pointer to dir_lister_t struct, contains pointers to DIR
 *			and current_entry
 *
 * Return: dirent *next_entry on success, otherwise NULL
 */

struct dirent *next_entry(dir_lister_t *parser)
{
	struct dirent *next_entry = NULL;

	if (parser->stop)
		return (NULL);

	next_entry = readdir(parser->directory);

	if (next_entry)
		parser->current_entry = next_entry;
	else
	{
		parser->current_entry = NULL;
		parser->stop = 1;
	}

	return (next_entry);
}

/**
 * close_dir - closes the open DIR pointer
 * @parser: pointer to dir_lister_t struct, contains pointers to DIR
 *			and current_entry
 *
 * Return: n/a
 */

void close_dir(dir_lister_t *parser)
{
	if (!parser)
		return;

	closedir(parser->directory);
}
