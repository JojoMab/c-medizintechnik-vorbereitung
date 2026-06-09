#include <stdio.h>

int main(void) {
    double temperature_c = 37.5;
    int heart_rate_bpm = 82;
    double oxygen_percent = 98.5;

    char temperature_unit = 'C';
    char heart_rate_unit[] = "bpm";

    printf("Vital Values\n");
    printf("============\n\n");

    printf("Temperature: %.1f %c\n", temperature_c, temperature_unit);
    printf("Heart rate: %d %s\n", heart_rate_bpm, heart_rate_unit);
    printf("Oxygen saturation: %.1f %%\n", oxygen_percent);

    return 0;
}
