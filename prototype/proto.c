#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
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