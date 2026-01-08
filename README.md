![C](https://img.shields.io/badge/-006CAF.svg?style=for-the-badge&logo=c&logoColor=white)
[![Holberton](https://img.shields.io/badge/Holberton-E31C3F.svg?style=for-the-badge)](https://www.holbertonschool.fr/)

## Simple Shell - Holberton School

### Requirements

- Allowed editors: vi, vim, emacs
- Ubuntu 20.04 LTS or newer
- All files should end with a new line
- Betty style code
- No memory leaks
- No more than 5 functions per file

### Description

*Simple Shell* is a simple **UNIX** command-line interpreter written in **C**.  
It reads and executes commands typed by the user or piped from standard input.  
The shell supports commands found in the `PATH` and absolute paths.  
It also implements built-in commands such as `exit` and `env`.

### Compilation

The code is tested and compiled on **Ubuntu 20.04 LTS** using:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

#### Memory leak checking with Valgrind

```bash
valgrind --leak-check=full --show-leak-kinds=all ./hsh
```

All tests pass with no memory leaks and no errors on Valgrind.

Example valgrind result:
```
==368== Memcheck, a memory error detector
==368== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==368== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==368== Command: ./hsh
==368== 
==368== 
==368== HEAP SUMMARY:
==368==     in use at exit: 0 bytes in 0 blocks
==368==   total heap usage: 3 allocs, 3 frees, 2,168 bytes allocated
==368== 
==368== All heap blocks were freed -- no leaks are possible
==368== 
==368== For lists of detected and suppressed errors, rerun with: -s
==368== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

#### File Structure 

| File               | Description                                                            |
|--------------------|------------------------------------------------------------------------|
| shell.c            | Entry point of the shell, contains the main loop and command execution |
| main.h             | Header file with prototypes and libraries                              |
| shell_utils.c      | Helper functions : handle_builtin and print_env                        |
| man_1_simple_shell | Manual page for the shell                                              |

#### Flowchart

### Authors

- [Anthony Goutieras](https://github.com/AGoutieras)  
- [Gabriel De Vasselot](https://github.com/g-devlt)
