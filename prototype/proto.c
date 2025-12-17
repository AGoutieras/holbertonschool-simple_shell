#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int starts_with(const char *s, const char* prefix)
{
    return strncmp(prefix, s, strlen(prefix)) == 0;
}

char *find(const char* filename, )
{

}

typedef struct list_t 
{
    char *data;
    size_t len;
    list_t *next;
} list_t;

typedef struct split_t
{
    char **data;
    size_t len;
} split_t;

split_t split(const char* string, char *sep)
{
    list_t *head = NULL;
    list_t *current = NULL;
    char *token;
    size_t size;
    size_t i;

    token = strtok(string, sep);
    while(token)
    {
        list_t* new;
        size_t tok_len = strlen(token);
        char *tok_cpy = malloc(tok_len + 1);
        
        strcpy(tok_cpy, token);
        
        new = (list_t *)malloc(sizeof(list_t));
        new->data = tok_cpy;
        new->len = tok_len;
        if(current)
            current->next = new;
        else
            head = new;
        current = new;
        ++size;
    }

    char **buf = (char **)malloc(sizeof(char *) * size);
    for (i = 0; (i < size) && head; ++i)
    {
        buf[i] = head->data;
        if(!head->next)
        {
            free(head);
            head = NULL;
        }
        else
            free(head->prev);
    }

    split_t res = {};
    res->data = buf;
    res->len = size;

    return res;
}

void free_split(split_t* res)
{
    size_t i = 0;

    for (; i < res->len; ++i)
    {
        free(res->data[i]);
    }
    free(res->data);
    free(res);
}

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