#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * list_t - Doubly linked list.
 * @data: The string to store.
 * @len: The length of the string
 * @next: The next node.
 * @prev: The previous node.
*/
typedef struct list_t
{
	char *data;
	size_t len;
	struct list_t *next;
	struct list_t *prev;
} list_t;

/**
 * split_t - Result of split operation
 * @data: The array of strings, null terminated
 * @len: The length of the array.
 *
*/
typedef struct split_t
{
	char **data;
	size_t len;
} split_t;

split_t split(char *string, char *sep);
void free_split(split_t *res);

#endif
