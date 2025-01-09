#include "strace_hdr.h"
#include "syscalls.h"
#include <sys/wait.h>

/**
* main - starting point for strace_0 program
* @argc: count of arguments passed into main
* @argv: vector of argument strings passed into main
* @env: environment variables passed into main
*
* Return: 0 on success, otherwise -1
**/

int main (int argc, char **argv)
{
	if (argc == 1)
	{
		printf("USAGE: ./strace_0 command [args...]\n");
		return (-1);
	}

	pid_t child_pid = fork();

	if (child_pid < 0)
	{
		printf("fork error\n");
		return (-1);
	}
	else if (child_pid == 0)
		child_function(argv[1], &argv[1]);
	else
		parent_function(child_pid);

	printf("you've made it this far\n");
	return (0);
}

/**
* child_function - what the child process should do
* @cmd_path: given command path
* @cmd_args: given command arguments
*
* Return: 0 on success, -1 on failure
**/

int child_function (char *cmd_path, char **cmd_args)
{
	char **environ = {NULL};

	printf("print from child\n");
	if (execve(cmd_path, cmd_args, environ) != 0)
	{
		printf("execve error\n");
		return (-1);
	}
	return (0);
}

/**
* parent_function - what the parent process should do
* @child_pid: pid of the child process
*
* Return: 0 on success, otherwise -1
**/

int parent_function (pid_t child_pid)
{
	int status;
	waitpid(child_pid, &status, 0);
	return (0);
}
