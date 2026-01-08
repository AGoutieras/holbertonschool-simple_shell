#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

char **line_to_av(char *line);
char **get_command(char **line, size_t *len, ssize_t *nread);
void execute_command(char **av, char *shell_name, int *last_status);
char *get_full_path(char *command);
void print_env(void);
int handle_builtin(char **av, int *last_status, char *line);

#endif
