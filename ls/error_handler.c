#include "list.h"

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * error_handler - handles all errors program may encounter
 * @error: type of error
 *
 * Return: 1 for error
 */

int error_handler(errorCode_t error, ...)
{
	va_list arg;

	va_start(arg, error);
	switch (error)
	{
	case ERR_FILE_NOT_FOUND:
		fprintf(stderr, "%s: cannot access %s: No such file or directory\n",
				va_arg(arg, char *), va_arg(arg, char *));
		break;

	case ERR_CANNOT_ACCESS_DIR:
		fprintf(stderr, "%s: cannot open directory %s: Permission denied\n",
				va_arg(arg, char *), va_arg(arg, char *));
		break;

	case ERR_FAILURE_TO_OPEN_DIR:
		fprintf(stderr, "%s: cannot access %s: No such file or directory\n",
				va_arg(arg, char *), va_arg(arg, char *));
		break;

	default:
		break;
	}
	return (-1);
}
