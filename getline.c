#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
motl
#define READ_BUF_SIZE 1024

/**
 * _getline - reads input from the command line and returns it as a string
 *
 * Return: a pointer to the input string or NULL on failure
 */
char *_getline(void)
{
	char *buf = NULL, *tmp = NULL;
	size_t buf_size = 0, read_size = 0, total_size = 0;

	do {
		buf_size += READ_BUF_SIZE;
		tmp = realloc(buf, buf_size);
		if (!tmp)
		{
			free(buf);
			return (NULL);
		}
		buf = tmp;
		read_size = read(STDIN_FILENO, buf + total_size, READ_BUF_SIZE);
		if (read_size <= 0)
		{
			free(buf);
			return (NULL);
		}
		total_size += read_size;
	} while (buf[total_size - 1] != '\n');
	buf[total_size - 1] = '\0';
	return (buf);
}
