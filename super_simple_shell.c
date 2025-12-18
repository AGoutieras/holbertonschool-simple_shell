#include "main.h"

int main(int argc, char **argv)
{
	char **av, *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;

	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		nread = getline(&line, &len, stdin);
		if (nread == -1)
			break;
		av = line_to_av(line);
		if (av[0] == NULL)
		{
			free(av);
			continue;
		}
		if (access(av[0], X_OK) == -1)
		{
			fprintf(stderr, "%s: 1: %s not found\n", argv[0], av[0]);
			free(av);
			continue;
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
	return (0);
}

char **line_to_av(char *line)
{
	char **av = malloc(10 * sizeof(char *));
	char *token;
	int i = 0;

	if (!av)
		return (NULL);

	token = strtok(line, " \t\n");

	while (token != NULL)
	{
		av[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	av[i] = NULL;

	return (av);
}
