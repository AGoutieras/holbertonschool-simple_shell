#include "main.h"

/**
 * main - Simple Shell
 * @argc: Argument count.
 * @argv: Argument values.
 * Return: always 0.
*/

int main(int argc, char **argv)
{
	char **av, *line = NULL;
	size_t len = 0;
	ssize_t nread;

	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");

		av = get_command(&line, &len, &nread);

		if (!av)
			continue;

		execute_command(av, argv[0]);
	}

	free(line);
	return (0);
}

/**
 * get_command - Reads a line and converts it to an array of words
 * @line: Pointer to input buffer
 * @len: Pointer to buffer size
 * @nread: Pointer to store number of characters read
 *
 * Return: Array of words, or NULL if line is empty.
 * Exits on EOF (Ctrl+D).
*/

char **get_command(char **line, size_t *len, ssize_t *nread)
{
	char **av;

	*nread = getline(line, len, stdin);

	if (*nread == -1)
		exit(0);

	av = line_to_av(*line);

	if (!av || !av[0])
	{
		free(av);
		return (NULL);
	}

		return (av);
}

/**
 * execute_command - Forks and executes a command
 * @av: array of arguments
 * @shell_name: name of the shell
*/

void execute_command(char **av, char *shell_name)
{
	pid_t pid;

	if (access(av[0], X_OK) == -1)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", shell_name, av[0]);
		free(av);
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		execve(av[0], av, environ);
		perror(av[0]);
		exit(1);
	}
	else if (pid > 0)
		wait(NULL);
	else
		perror("fork");

	free(av);
}

/**
 * line_to_av - Splits a line into an array of words
 * @line: Input string containing a command line
 *
 * Return: A pointer to the NULL-terminated array of strings on success,
 *         or NULL if memory allocation fails.
*/

char **line_to_av(char *line)
{
	char **av = NULL, *token;
	int i = 0, capacity = 10;

	av = malloc (capacity * sizeof(char *));

	if (!av)
		return (NULL);

	token = strtok(line, " \t\n");

	while (token != NULL)
	{
		if (i >= capacity - 1)
		{
			capacity *= 2;
			av = realloc(av, capacity * sizeof(char *));
			if (!av)
				return (NULL);
		}
		av[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	av[i] = NULL;

	return (av);
}
