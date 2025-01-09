#ifndef STRACE_HDR_H
#define STRACE_HDR_H

/***** LIBRARIES *****/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/***** PROTOTYPES *****/

/* STRACE_0.C */

int child_function(char *, char **);
int parent_function(pid_t);

#endif /* STRACE_HDR_H */
