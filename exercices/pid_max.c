#include "tests.h"

int main(void)
{
    char buffer[16];
    int fd, r, pid_max;

    fd = open("/proc/sys/kernel/pid_max", O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return (1);
    }
    
    r = read(fd, buffer, sizeof(buffer) - 1);
    if (r == -1)
    {
        perror("read");
        close(fd);
        return (1);
    }

    buffer[r] = '\0';
    pid_max = atoi(buffer);
    printf("PID max : %d\n", pid_max);

    close(fd);
    return (0);
}