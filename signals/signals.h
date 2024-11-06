#ifndef _SIGNALS_H
#define _SIGNALS_H

/* LIBRARIES */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/* PROTOTYPES */

int handle_signal(void);
void (*current_handler_signal(void))(int);
int handle_sigaction(void);
void (*current_handler_sigaction(void))(int);
int trace_signal_sender(void);
int pid_exist(pid_t pid);

#endif /* _SIGNALS_H */
