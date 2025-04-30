#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void alarmHandler(int pass) {
    puts("Time is up");
    exit(1);
}

void setup() {
    struct sigaction act;
    act.sa_handler = alarmHandler;
    sigaction(SIGALRM, &act, NULL);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    alarm(60);
}

int main() {
    char buf[100];
    int x;
    setup();
    printf("* beeeeeeeeeeeeeeeeeeeeeeeeeeep *\n> ");
    read(STDIN_FILENO, buf, 0x108);
    if (x == 1337)
        system("cat flag");
    return 0;
}
