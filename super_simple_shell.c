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
		fflush(stdout);
		av = get_command(&line, &len, &nread);

		if (!av)
			break;

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
	char *line_start;
	size_t l;

	*nread = getline(line, len, stdin);

	if (*nread == -1)
		return (NULL);

	line_start = *line;

	while (*line_start && (*line_start == ' ' || *line_start == '\t'))
		line_start++;

	l = strlen(line_start);
	while (l > 0 && (line_start[l - 1] == ' ' ||
					 line_start[l - 1] == '\t' ||
					 line_start[l - 1] == '\n'))
	{
		line_start[--l] = '\0';
	}

		if (!line_start)
			return (NULL);

	av = line_to_av(line_start);

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
	char *path;
	pid_t pid;

	path = get_full_path(av[0]);
	if (!path)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", shell_name, av[0]);
		free(av);
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		execve(path, av, environ);
		perror(shell_name);
		exit(1);
	}
	else if (pid > 0)
		wait(NULL);
	else
		perror("fork");

	free(path);
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

	av = malloc(capacity * sizeof(char *));

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

/**
 * get_full_path - Resolves a command to its full executable path
 * @command: command to locate
 *
 * Return: A newly allocated string containing the full path if found,
 *         or NULL if the command cannot be found or is not executable.
*/

char *get_full_path(char *command)
{
	char *dir, *full_path, *path_copy;
	int i;

	for (i = 0; command[i]; i++)
		if (command[i] == '/')
			return (access(command, X_OK) == 0 ? strdup(command) : NULL);

	for (i = 0; environ[i]; i++)
		if (!strncmp(environ[i], "PATH=", 5))
			break;

	if (!environ[i])
		return (NULL);

	path_copy = strdup(environ[i] + 5);

	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");

	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);

		if (!full_path)
			return (free(path_copy), NULL);

		sprintf(full_path, "%s/%s", dir, command);

		if (access(full_path, X_OK) == 0)
			return (free(path_copy), full_path);

		free(full_path);

		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

