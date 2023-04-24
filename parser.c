#include "shell.h" motlalepula

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st) != 0)
		return (0);

	return (S_ISREG(st.st_mode));
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	char *buf = NULL;
	int i, k;

	if (start > stop)
		return (NULL);

	buf = malloc(stop - start + 2);
	if (!buf)
		return (NULL);

	for (k = 0, i = start; i <= stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = '\0';
	return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path = NULL;

	if (!pathstr || !cmd)
		return (NULL);

	if (_strlen(cmd) > 2 && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}

	while (pathstr[i])
	{
		if (pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i - 1);
			if (!path)
				return (NULL);

			if (*path != '\0')
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			else
				_strcpy(path, cmd);

			if (is_cmd(info, path))
				return (path);

			curr_pos = i + 1;
		}
		i++;
	}

	path = dup_chars(pathstr, curr_pos, i - 1);
	if (!path)
		return (NULL);

	if (*path != '\0')
	{
		_strcat(path, "/");
		_strcat(path, cmd);
	}
	else
		_strcpy(path, cmd);

	if (is_cmd(info, path))
		return (path);

	free(path);
	return (NULL);
}
