#include "multithreading.h"
#include <pthread.h>
#include <stdio.h>

/**
* thread_entry - prints a given string
* @arg: pointer to string
*
* Return: n/a
**/

void *thread_entry(void *arg)
{
	printf("%s\n", (char *)arg);
	pthread_exit(NULL);
}
