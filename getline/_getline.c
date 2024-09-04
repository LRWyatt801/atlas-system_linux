#include "_getline.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *_getline(const int fd)
{
	char *buffer;
	size_t read_bytes;

	buffer = malloc(READ_SIZE);
	if (!buffer)
		return(NULL);
	
	read_bytes = read(fd, buffer, READ_SIZE);
	if (read_bytes <= 0)
	{
		free(buffer);
		return(NULL);
	}

	return(buffer);
}
