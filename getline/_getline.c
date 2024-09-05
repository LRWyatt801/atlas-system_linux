#include "_getline.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *_getline(const int fd)
{
	static char *buffer;
	static size_t size;


	buffer = malloc(sizeof(char) * READ_SIZE);
	if (!buffer)
		return(NULL);

	size = read(fd, buffer, READ_SIZE);
	if (size <= 0)
	{
		free(buffer);
		return(NULL);
	}
	buffer[size] = '\0';

	return(buffer);
}
