#include "tests.h"

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

int main(void)
{
    char line [] = "ls -l /tmp";
    char **av;
    int i;

    av = line_to_av(line);

    for (i = 0; av[i] != NULL; i++)
        printf("av[%d] = %s\n", i, av[i]);

    free(av);
    return (0);
}