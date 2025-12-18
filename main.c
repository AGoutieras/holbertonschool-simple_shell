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
char *find(char *filename, char *PATH)
{
	split_t res;
	size_t i = 0;
	struct stat st;
	char *nPATH;

	PATH = PATH + 5; /*Skips 'PATH='*/
	nPATH = malloc(strlen(PATH));
	strcpy(nPATH, PATH);
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
		if (stat(str, &st) != -1)
		{
			free(nPATH);
			free_split(&res);
			return (str);
		}
		free(str);
	}
	free(nPATH);
	free_split(&res);
	return (filename);
}

/**
 * _exec - Executes a program
 * @filepath: The absolute path to the executable
 * @argv: The arguments to pass to the program
 * Return: 1 on success, 0 otherwise
*/
int _exec(const char *filepath, char **argv, char **env)
{
	struct stat st;
	pid_t child;

	if (!filepath || stat(filepath, &st) == -1)
	{
		printf("%s: no such file or directory\n", filepath);
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

		err = execve(filepath, argv, env);
		if (err == -1)
		{
			printf("%s: couldn't execute program.\n", filepath);
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

	while (1)
	{
		char *line = NULL;
		size_t size = 0;
		split_t res = {0};
		char *found = NULL;
		size_t linelen = 0;

		printf("($) ");
		getline(&line, &size, stdin);
		linelen = strlen(line) - 1;
		if(linelen <= 0) continue;
		line[linelen] = 0;
		res = split(line, " ");
		if (strcmp(res.data[0], "exit") == 0)
		{
			free_split(&res);
			return (0);
		}
		found = find(res.data[0], PATH);
		_exec(found, &res.data[0], env);
		free_split(&res);
	}

	return (0);
}
