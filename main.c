#include "main.h"
#include <ctype.h>

/**
 * find - Finds the absolute path of an executable
 * @filename: The name of the file to find
 * Return: A string of the absolute path
*/
char *find(const char *filename, char *PATH)
{
	split_t res;
	size_t i = 0;
	char *nPATH;
	char *oPATH;

	PATH = PATH + 5; /*Skips 'PATH='*/
	oPATH = malloc(strlen(PATH) + 1);
	strcpy(oPATH, PATH);
	nPATH = oPATH;
	res = split(nPATH, ":");
	for (; i < res.len; ++i)
	{
		size_t datalen = strlen(res.data[i]);
		char *str = malloc(datalen + 1 + strlen(filename));
		size_t it = 0;

		while (res.data[i][it] != 0)
		{
			str[it] = res.data[i][it];
			++it;
		}
		str[it] = '/';
		it = 0;
		while (filename[it] != 0)
		{
			str[it + datalen + 1] = filename[it];
			++it;
		}
		str[datalen + it + 1] = 0;
		if (access(str, X_OK) != -1)
		{
			free(oPATH);
			free_split(&res);
			return (str);
		}
		free(str);
	}
	free(oPATH);
	free_split(&res);
	return (NULL);
}

/**
 * exec_builtin - Checks and runs buitlin functions.
 * @data: The command line arguments and command
 * @env: The environment of the program.
 * Return: < 0 on failure, > 0 otherwise
*/
int exec_builtin(split_t *data, char **env)
{
	if (!data->data[0])
		return (0);
	if (strcmp(data->data[0], "exit") == 0)
	{
		free_split(data);
		exit(0);
	}
	else if (strcmp(data->data[0], "env") == 0)
	{
		while (*env)
		{
			printf("%s\n", *env);
			++env;
		}
		return (0);
	}
	return (-1);
}

/**
 * _exec - Executes a program
 * @filepath: The absolute path to the executable
 * @argv: The arguments to pass to the program
 * Return: 1 on success, 0 otherwise
*/
int _exec(split_t *data, char *PATH, char **argv, char **env)
{
	pid_t child;
	char *found = NULL;

	found = find(data->data[0], PATH);
	if (!found)
	{
		printf("%s: command not found.", data->data[0]);
		return (0);
	}

	if (access(found, X_OK) == -1)
	{
		printf("%s: no such file or directory\n", found);
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

		err = execve(found, argv, env);
		if (err == -1)
		{
			printf("%s: couldn't execute program.\n", found);
			return (0);
		}
	}

	free(found);
	wait(NULL);
	return (1);
}

/**
 * handle_commands - Executes commands from prompt
 * @env: Program env
 * @PATH: Env PATH
 * Return: Status
*/
int handle_commands(char **env, char *PATH)
{
	while (1)
	{
		char *line = NULL;
		char *it = NULL;
		size_t size = 0;
		split_t res = {0};

		if (isatty(STDIN_FILENO))
			printf("($) ");
		if (getline(&line, &size, stdin) == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			free(line);
			return (0);
		}
		if (strlen(line) > 0)
			line[strlen(line) - 1] = 0;
		it = line;
		while (*it != 0 && isspace(*it))
		{
			++it;
		}
		if (*it == 0)
		{
			free(line);
			continue;
		}
		res = split(line, " ");
		free(line);
		if (exec_builtin(&res, env) < 0)
		{
			_exec(&res, PATH, &res.data[0], env);
		}
		free_split(&res);
	}
}

/**
 * main - Simple Shell, read code
 * @argc: Argument count.
 * @argv: Argument values.
 * @env: Environment values.
 * Return: 1 on success, failure otherwise
*/
int main(int argc, char **argv, char **env)
{
	char *PATH = NULL;
	size_t i = 0;

	(void)argc;
	(void)argv;
	for (; env[i] != 0; ++i)
	{
		if (starts_with(env[i], "PATH="))
		{
			PATH = env[i];
			break;
		}
	}
	return (handle_commands(env, PATH));
}
