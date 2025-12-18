#include "main.h"

/**
 * dll2split - Converts a doubly linked list into a split_t struct
 * @head: The head of the list
 * @size: The size of the list
 * Return: All the splitted strings.
*/
split_t dll2split(list_t *head, size_t size)
{
	split_t res = {0};
	char **buf;
	size_t i;

	buf = (char **)malloc(sizeof(char *) * size + 1);
	for (i = 0; (i < size) && head; ++i)
	{
		buf[i] = head->data;
		if (!head->next)
		{
			free(head);
			head = NULL;
		}
		else
		{
			head = head->next;
			free(head->prev);
		}
	}
	buf[i] = NULL;
	res.data = buf;
	res.len = size;
	return (res);
}

/**
 * split - Splits a string into substrings that were separeted by @sep
 * @string: The string to split
 * @sep: The separator
 * Return: A structure containing all the splitted strings.
*/
split_t split(char *string, char *sep)
{
	list_t *head = NULL;
	list_t *current = NULL;
	char *token;
	size_t size = 0;

	token = strtok(string, sep);
	while (token)
	{
		list_t *new;
		size_t tok_len = strlen(token);
		char *tok_cpy = malloc(tok_len + 1);

		strcpy(tok_cpy, token);
		new = (list_t *)malloc(sizeof(list_t));
		new->data = tok_cpy;
		new->len = tok_len;
		if (current)
			current->next = new;
		else
			head = new;
		current = new;
		++size;
		token = strtok(NULL, sep);
	}

	return (dll2split(head, size));
}

/**
 * free_split - frees a spli_t struct
 * @res: The struct to free
*/
void free_split(split_t *res)
{
	size_t i = 0;

	for (; i < res->len; ++i)
	{
		free(res->data[i]);
	}
	free(res->data);
}
