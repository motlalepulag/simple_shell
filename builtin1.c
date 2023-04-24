#include "shell.h"

/**
 * _myhistory - displays the history list, one command per line, preceded
 *              by line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
	history_t *current = info->history;
	int line_number = 0;

	while (current != NULL)
	{
		printf("%d %s\n", line_number, current->command);
		current = current->next;
		line_number++;
	}

	return (0);
}
/**
 * unset_alias - removes an alias from the info_t struct
 * @info: pointer to info_t struct
 * @str: string representing the alias
 *
 * Return: 0 on success, 1 on error
 */
int unset_alias(info_t *info, const char *str)
{
	char *alias_name, *alias_value, *alias_equals;
	int ret;

	alias_equals = strchr(str, '=');
	if (!alias_equals)
		return (1);

	alias_name = strndup(str, alias_equals - str);
	alias_value = alias_equals + 1;

	ret = delete_node_at_index(&(info->alias),
				   get_node_index(info->alias,
					   node_starts_with(info->alias, alias_name, -1)));

	free(alias_name);

	if (ret == 0)
	{
		node_t *alias_node = create_node(alias_name, alias_value);

		if (alias_node)
			append_node(&(info->alias), alias_node);
		else
			ret = 1;
	}

	return (ret);
}
/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);

	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL ? 1 : 0);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
