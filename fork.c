#include <stdio.h>
#include <unistd.h>
int main() {
    fork();
    printf("PID: %d, PPID: %d\n", getpid(), getppid());
    sleep(60);
    return 0;
}
