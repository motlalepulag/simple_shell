#include <stdio.h>
#include <stdlib.h>

/**
 * Reads a line of input from a file and stores it in a buffer.
 *
 * @param[in]   file    The file to read from.
 * @param[out]  buffer  The buffer to store the input in.
 * @param[in]   size    The maximum number of characters to read.
 *
 * @return      The number of characters read, or -1 if an error occurred.
 */

char *my_getline()
{
	static char buf[1024];
	char *line = NULL;
	int line_len = 0, buf_len = 0;

	while (1)
	{
		if (pos == len)
		{
			pos = 0;
			len = fread(buf, sizeof(char), 1024, stdin);
			if (len == 0)
			{
				if (line_len == 0)
				{
					return (NULL);
				}
				else
				{
					break;
				}
			}
		}
		if (buf[pos] == '\n')
		{
			pos++;
			break;
		}
		if (line_len == buf_len)
		{
			buf_len += 1024;
			line = realloc(line, buf_len * sizeof(char));
			if (!line)
			{
				return (NULL);
			}
		}
		line[line_len++] = buf[pos++];
	}
	if (line_len == 0)
	{
		return (NULL);
	}
	line[line_len] = '\0';
	return (line);
}

