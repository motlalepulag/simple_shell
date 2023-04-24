#include "shell.h"
moth
/**
 * shell_exit - Exit the shell
 * @args: List of arguments. args[1] is the status code
 *
 * Return: 0 on success, 1 on failure
 */
int shell_exit(char **args)
{
	int status = 0;

	if (args[1] != NULL)
	{
		status = _atoi(args[1]);
	}
	exit(status);
	return (0);
}
