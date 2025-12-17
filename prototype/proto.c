#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int _exec(const char *filepath, char **argv)
{
    struct stat st;
    if(stat(filepath, &st) == -1)
    {
        printf("File '%s' not found.", filepath);
        return 0;
    }

    pid_t child = fork();
    if(child == -1)
    {
        printf("Couldn't fork process.");
        return 0;
    }

    if(child == 0)
    {
        int err;

        err = execve(filepath, argv, NULL);
        if(err == -1)
        {
            printf("Couldn't execute program.");
            return 0;
        }
    }

    wait(NULL);
    return 1;
}

int main(int argc, char **argv)
{
    _exec("/bin/ls", (char *[]){"bin/ls", "-la"});

    /* Enter prompt mode*/
    while(1)
    {
        char *line = NULL;
        size_t size = 0;

        printf(">> ");
        getline(&line, &size, stdin);
        printf(">>> %s\n", line); /*TODO: Replace with command call*/

    }

    return 0;
}