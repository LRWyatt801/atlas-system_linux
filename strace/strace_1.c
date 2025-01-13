#include "strace_hdr.h"
#include "syscalls.h"
#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>

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
	if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) != 0)
	{
		printf("traceme error\n");
		return (-1);
	}
	if (execvp(cmd_path, cmd_args) != 0)
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
	int status, entry = 0;
	struct user_regs_struct registers;

	while (1)
	{
		if (waitpid(child_pid, &status, 0) == -1)
			perror("PARENT_FUNCTION: waidpid");
		if (WIFEXITED(status)) break;

		ptrace(PTRACE_GETREGS, child_pid, 0, &registers);

		/* first entry and then every true entry */
		if (entry == 0 || entry % 2 != 0)
		{
			get_syscall_name(registers.orig_rax);
		}

		/* handle entry and exit, check above counts entry */
		if (ptrace(PTRACE_SYSCALL, child_pid, 0, 0) == -1)
			return (-1);

		entry++;
		fflush(NULL);
	}
	return (0);
}

/**
* get_syscall_name - gets the same of a syscall using the syscall number
* @syscall_num: number of syscall
*
* Return: n/a
*/

void get_syscall_name(unsigned long syscall_num)
{
	syscall_t const *syscall_info;

	syscall_info = &syscalls_64_g[syscall_num];
	printf("%s", syscall_info->name);

	if (syscall_num != 1)
		printf("\n");
}
