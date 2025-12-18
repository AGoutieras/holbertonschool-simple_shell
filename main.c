#include "main.h"

/**
 * starts_with - Checks if a string starts with a certain prefix
 * @s: The string to check
 * @prefix: The prefix
 * Return: 1 on sucess, 0 otherwise
*/
int starts_with(const char *s, const char *prefix)
{
	return (strncmp(prefix, s, strlen(prefix)) == 0);
}

/**
 * find - Finds the absolute path of an executable
 * @filename: The name of the file to find
 * Return: A string of the absolute path
*/
char *find(const char *filename)
{
	(void)filename;
	return (NULL);
}

/**
 * _exec - Executes a program
 * @filepath: The absolute path to the executable
 * @argv: The arguments to pass to the program
 * Return: 1 on success, 0 otherwise
*/
int _exec(const char *filepath, char **argv)
{
	struct stat st;
	pid_t child;

	if (stat(filepath, &st) == -1)
	{
		printf("File '%s' not found.\n", filepath);
		return (0);
	}

	child = fork();
	if (child == -1)
	{
		printf("Couldn't fork process.\n");
		return (0);
	}

	if (child == 0)
	{
		int err;

		err = execve(filepath, argv, NULL);
		if (err == -1)
		{
			printf("Couldn't execute program.\n");
			return (0);
		}
	}

	wait(NULL);
	return (1);
}

/**
 * main - Simple Shell, read code
 * @argc: Argument count.
 * @argv: Argument values.
 * Return: 1 on success, failure otherwise
*/
int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	while (1)
	{
		char *line = NULL;
		size_t size = 0;
		split_t res;

		printf("($) ");
		getline(&line, &size, stdin);
		line[strlen(line) - 1] = 0;
		res = split(line, " ");
		if (strcmp(res.data[0], "exit") == 0)
		{
			free_split(&res);
			return (0);
		}
		_exec(res.data[0], &res.data[0]);
		free_split(&res);
	}

	return (0);
}
