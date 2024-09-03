#include "_getline.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/**
 * _getline - reads the a line from a file descriptor
 * @fd: file descriptor to read from
 *
 * Return: read line
**/

char *_getline(const int fd)
{
	char *buffer;
	size_t bytes_read;

	buffer = malloc((READ_SIZE + 1) * sizeof(char));

	if (!buffer)
		return (NULL);

	bytes_read = read(fd, buffer, READ_SIZE);
	if (bytes_read <= 0)
	{
		free(buffer);
		return (NULL);
	}

	buffer[bytes_read] = '\0';

	if (buffer[bytes_read - 1] == '\n')
		buffer[bytes_read - 1] = '\0';
	
	return (buffer);
}

