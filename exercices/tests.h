#ifndef TESTS_H
#define TESTS_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

char **line_to_av(char *line);

#endif