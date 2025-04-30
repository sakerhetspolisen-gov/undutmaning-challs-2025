#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdbool.h>

#define TARGET_FILE "/home/ctf/jail/proc/uptime"

int main() {
    FILE *file;
    int seconds_elapsed = 0;

    while (1) {
        // Öppna filen för skrivning
        file = fopen(TARGET_FILE, "w");
        if (file == NULL) {
            perror("Fel vid öppning av fil");
            return EXIT_FAILURE;
        }

        // Skriv antalet sekunder till filen
        fprintf(file, "%d\n", seconds_elapsed);

        // Stäng filen
        fclose(file);

        // Vänta en sekund
        sleep(1);

        // Öka antalet sekunder
        seconds_elapsed++;
    }

    return 0;
}
