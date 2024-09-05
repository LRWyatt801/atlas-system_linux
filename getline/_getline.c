#include "_getline.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *_getline(const int fd)
{
	static char *buffer;
	static size_t size;
	size_t len = 0;
	char *nxtlineptr = NULL;
	char *line = NULL;
	static int calls;

	printf("%d\n", ++calls);
	printf("%p\n", (void*)&buffer);
	/* read file if buffer is empty */
	// if (buffer == NULL)
	// {
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
	// }

	/* parse line */
	nxtlineptr = buffer;
	while(*nxtlineptr != '\n')
	{
		nxtlineptr++;
		len++;
	}
	line = strndup(buffer, len);
	line[len] = '\0';

	/* move buffer */
	size -= len * sizeof(char);

	return(line);
}
