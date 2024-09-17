#include "list.h"

#include <unistd.h>
#include <stdio.h>

/**
 * check_file_type - checks the type (REG/DIR) of input: 'path'
 * @parser: pointer to dir_lister_t struct, contains pointers to DIR
 *			and current_entry
 * @path: pointer to the given path of file/dir
 *
 * Return: 'ISFILE', 'ISDIR', or 'FILEERR'
 */

int check_file_type(dir_lister_t *parser, const char *path)
{
	struct stat path_info;

	if (lstat(path, &path_info) == -1)
	{
		error_handler(ERR_FILE_NOT_FOUND, path, parser->program_name);
		return (FILEERR);
	}

	/* check for file or dir */
	if ((path_info.st_mode & __S_IFMT) == __S_IFREG)
	{
		printf("%s\n", path);
		return (ISFILE);
	}
	else if ((path_info.st_mode & __S_IFMT) == __S_IFDIR)
		return (ISDIR);

	return (0);
}
