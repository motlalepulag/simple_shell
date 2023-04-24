#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);

		if (interactive(info))
			_puts("$ ");

		_eputchar(BUF_FLUSH);
		r = get_input(info);

		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);

			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
		{
			_putchar('\n');
		}

		free_info(info, 0);
	}

	write_history(info);
	free_info(info, 1);

	if (!interactive(info) && info->status)
	{
		exit(info->status);
	}

	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		else
			exit(info->err_num);
	}

	return (builtin_ret);
}
/**
 * Searches for a builtin command and executes it.
 *
 * @param info a pointer to the info struct
 * @return -1 if the command is not a builtin, 0 on success, 1 on failure,
 *         and -2 if the command signals an exit.
 */
int find_builtin(info_t *info)
{
	static const builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (const builtin_table *p = builtintbl; p->type != NULL; ++p)
	{
		if (_strcmp(info->argv[0], p->type) == 0)
		{
			++info->line_count;
			return (p->func(info));
		}
	}
	return (-1);
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int num_args = 0;

	info->path = info->argv[0];


	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}


	for (int i = 0; info->arg[i]; i++)
	{
		if (!is_delim(info->arg[i], " \t\n"))
			num_args++;
	}


	if (!num_args)
		return;


	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{

		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
		{
			fork_cmd(info);
		}
		else if (*(info->arg) != '\n')
		{

			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}
/**
 * fork_cmd - forks an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		execve(info->path, info->argv, get_environ(info));
		perror("execve");
		free_info(info, 1);
		exit(1);
	}
	else
	{
		waitpid(child_pid, &(info->status), 0);
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
