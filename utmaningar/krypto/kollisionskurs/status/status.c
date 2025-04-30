#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define SPEED_TO_SUN_KM_PER_MINUTE 215625 // 1 AU in 8 hours (approx. 150 million km)
#define DISTANCE_TO_SUN_KM 150000000
#define DYSON_SPHERE_DISTANCE_KM 150000000 // Same as 1 AU

void usage() {
    printf("Usage: status <kort|full>\n");
    exit(1);
}

void calculate_status(time_t run_time) {
    double minutes_passed = (double)run_time / 60.0;

    double distance_traveled = minutes_passed * SPEED_TO_SUN_KM_PER_MINUTE;

    if (distance_traveled >= DYSON_SPHERE_DISTANCE_KM) {
        printf("Status:\n");
        printf("- Omloppsbana runt solen uppnådd.\n");
        printf("- Avstånd till solen: %.0f km\n", (double)DYSON_SPHERE_DISTANCE_KM);
        printf("- Tid för att nå omloppsbana: %.2f minuter\n", (double)DYSON_SPHERE_DISTANCE_KM / (double)SPEED_TO_SUN_KM_PER_MINUTE);
    } else {
        printf("Status:\n");
        printf("- Tid som passerat: %.2f minuter\n", minutes_passed);
        printf("- Avstånd till solen: %.0f km\n", distance_traveled);
        printf("- Hastighet: %d km/minut\n", SPEED_TO_SUN_KM_PER_MINUTE);
    }
}

void calculate_report(time_t run_time) {
    double minutes_passed = (double)run_time / 60.0;

    double distance_traveled = minutes_passed * SPEED_TO_SUN_KM_PER_MINUTE;
    double fuel_level = 100.0 - (distance_traveled / DISTANCE_TO_SUN_KM) * 100.0;

    // Simulated solar energy level (in arbitrary units)
    double solar_energy = (distance_traveled / DISTANCE_TO_SUN_KM) * 100.0;

    if (distance_traveled > DYSON_SPHERE_DISTANCE_KM) {
        fuel_level -= (minutes_passed - (DYSON_SPHERE_DISTANCE_KM / SPEED_TO_SUN_KM_PER_MINUTE)) * 0.1;
        if (fuel_level < 0) fuel_level = 0;
    }

    printf("Rapport:\n");
    printf("- Bränslenivå: %.2f%%\n", fuel_level > 0 ? fuel_level : 0.0);
    printf("- Solens energinivå: %.2f enheter\n", solar_energy);
    printf("- Temperaturen i omgivningen: %.2f °C\n", 27.0 + (solar_energy * 0.05));
    printf("- Status för huvudsystem: OK\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        usage();
    }

    static time_t run_time = 0;
    if (run_time == 0) {
        FILE *file;
        int uptime = 0;

        if((file = fopen("/proc/uptime", "r")) != NULL) 
        {   
            if(fscanf(file, "%d", &uptime) == 1)
                run_time = (time_t)uptime;
            fclose(file);
        }
    }

    if (strcmp(argv[1], "kort") == 0) {
        calculate_status(run_time);
    } else if (strcmp(argv[1], "full") == 0) {
        calculate_status(run_time);
        calculate_report(run_time);
    } else {
        usage();
    }

    return 0;
}
