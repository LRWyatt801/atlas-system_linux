#include <signal.h>

/**
 * pid_exist - check if a pid exist
 * @pid: pid to check
 *
 * Return: 1 if exist, 0 if not
 */

int pid_exist(pid_t pid)
{
	return (kill(pid, 0) == 0 ? 1 : 0);
}
