#include "tests.h"

int main(void)
{
    int i;
    pid_t pid;
    char *av[] = {"ls", "-l", "/tmp", NULL};
    char *envp[] = {NULL};

    for (i = 0; i < 5; i++)
    {
        pid = fork();

        if (pid == 0)
        {
            execve("/bin/ls", av, envp);

            perror("execve");
                exit(1);
        }

        else
        {
            wait(NULL);
        }
    }
}