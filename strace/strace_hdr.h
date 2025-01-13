#ifndef STRACE_HDR_H
#define STRACE_HDR_H

/***** LIBRARIES *****/

#include <unistd.h>

/***** PROTOTYPES *****/

int child_function(char *, char **);
int parent_function(pid_t);
void get_syscall_name(unsigned long int);
void get_syscall_info(unsigned long int);

#endif /* STRACE_HDR_H */
