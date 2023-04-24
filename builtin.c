#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

int main(int argc, char **argv)
{
	char command[MAX_COMMAND_LENGTH];
	pid_t pid;
	int status;

	while (1)
	{
		printf("#cisfun$ ");
		fgets(command, MAX_COMMAND_LENGTH, stdin);
		command[strcspn(command, "\n")] = '\0';
		if (strcmp(command, "exit") == 0)
		{
			exit(EXIT_SUCCESS);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (execlp(command, command, (char *)NULL) == -1)
			{
				perror("execlp");my naame
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			do

				waitpid(pid, &status, WUNTRACED);
		}
		{
			while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	}
	return (0);
}
