#include "strace_hdr.h"
#include "syscalls.h"
#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/syscall.h>

/**
* main - starting point for strace_0 program
* @argc: count of arguments passed into main
* @argv: vector of argument strings passed into main
*
* Return: 0 on success, otherwise -1
**/

int main(int argc, char **argv)
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

int child_function(char *cmd_path, char **cmd_args)
{
	char **environ = {NULL};

	if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) != 0)
	{
		printf("traceme error\n");
		return (-1);
	}
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

int parent_function(pid_t child_pid)
{
	int status, start = 0;
	struct user_regs_struct regs;

	while(1)
	{
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
			break;
		if (WIFSTOPPED(status))
		{
			ptrace(PTRACE_GETREGS, child_pid, NULL, &regs);
			if (start == 0)
			{
				printf("%llu\n", regs.orig_rax);
				start = 1;
			}
			else if (start == 1)
				start = 0;
		}
		ptrace(PTRACE_SYSCALL, child_pid, NULL, NULL);
	}

	return (0);
}

