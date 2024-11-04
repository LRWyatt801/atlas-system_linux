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

#endif /* _SIGNALS_H */
