#include "multithreading.h"
#include <bits/pthreadtypes.h>
#include <stdio.h>
#include <pthread.h>
#include <stdarg.h>

static pthread_mutex_t mutex;

/**
* init_mutex - initializes need mutex
*
* Return: n/a
**/

__attribute__((constructor))
static void init_mutex(void)
{
	pthread_mutex_init(&mutex, NULL);
}

/**
* destroy_mutex
*
* Return: n/a
**/

__attribute__((destructor))
static void destroy_mutex(void)
{
	pthread_mutex_destroy(&mutex);
}

/**
* tprintf - prints out a given formatted string
* @format: given formatted string
*
* Return: int
**/

int tprintf(char const *format, ...)
{
	va_list ptr;

	pthread_mutex_lock(&mutex);
	va_start(ptr, format);

	printf("[%lu] ", pthread_self());
	vprintf(format, ptr);

	va_end(ptr);
	pthread_mutex_unlock(&mutex);

	return (0);
}
