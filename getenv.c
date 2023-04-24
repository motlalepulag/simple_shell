#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
jj
#define MAX_ARGS 100

/* Function to split a string into tokens */
void split(char *str, char **args)
{
	int i = 0;

	args[i] = strtok(str, " \t\n");

	while (args[i] != NULL && i < MAX_ARGS - 1)
	{
		args[++i] = strtok(NULL, " \t\n");
	}
	args[i] = NULL;
}

/* Implementation of the setenv builtin command */
/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @args: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
void set_env(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		fprintf(stderr, "setenv: incorrect usage\n");
		return;
	}
	if (setenv(args[1], args[2], 1) != 0)
	{
		fprintf(stderr, "setenv: %s\n", strerror(errno));
		return;
	}
}

/* Implementation of the unsetenv builtin command */
void unset_env(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "unsetenv: incorrect usage\n");
		return;
	}
	if (unsetenv(args[1]) != 0)
	{
		fprintf(stderr, "unsetenv: %s\n", strerror(errno));
		return;
	}
}

/* Main function */
int main(void)
{
	char input[1024];
	char *args[MAX_ARGS];

	while (1)
	{
		printf("> ");
		fgets(input, 1024, stdin);
		split(input, args);
		if (args[0] != NULL)
		{
			if (strcmp(args[0], "setenv") == 0)
			{
				set_env(args);
			} else if (strcmp(args[0], "unsetenv") == 0)
			{
				unset_env(args);
			} else
		}
	}
	return (0);
}
