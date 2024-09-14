#include "list.h"

#include <unistd.h>
#include <stdio.h>

int check_file_type(const char *path)
{
    struct stat path_info;
    if (lstat(path, &path_info) == -1)
	{
		fprintf(stderr, "%s: cannot access %s: No such file or directory\n",
				path, path);
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