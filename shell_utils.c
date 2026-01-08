#include "main.h"

/**
 * handle_builtin - Executes a shell builtin command if recognized
 * @av: array of arguments
 * @last_status: Stores the exit status of the last executed command
 * @line: Pointer to input buffer
 *
 * Return: 1 if executed, 0 otherwise.
*/


int handle_builtin(char **av, int *last_status, char *line)
{
	if (!av[0])
		return (0);

	if (strcmp(av[0], "exit") == 0)
	{
		free(av);
		free(line);
		exit(*last_status);
	}

	if (strcmp(av[0], "env") == 0)
	{
		print_env();
		free(av);
		return (1);
	}

	return (0);
}

/**
 * print_env - prints the current environment
*/

void print_env(void)
{
	int i;

	if (!environ)
		return;

	for (i = 0; environ[i]; i++)
		printf("%s\n", environ[i]);
}
