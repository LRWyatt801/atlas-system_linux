#include "multithreading.h"
#include <stdio.h>
#include <pthread.h>

/**
* tprintf - prints out a given formatted string
* @format: given formatted string
*
* Return: int
**/

int tprintf(char const *format, ...)
{
	printf("[%lu] %s", pthread_self(), format);
	return (0);
}

