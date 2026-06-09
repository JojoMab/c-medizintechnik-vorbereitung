#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static void normalize_decimal_separator(char text[]) {
    for (size_t i = 0; text[i] != '\0'; i++) {
        if (text[i] == ',') {
            text[i] = '.';
        }
    }
}

static int read_double(const char *prompt, double *out_value) {
    char line[128];
    char *end = NULL;

    printf("%s", prompt);

    if (fgets(line, sizeof(line), stdin) == NULL) {
        return 0;
    }

    normalize_decimal_separator(line);
    double value = strtod(line, &end);

    if (line == end) {
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        end++;
    }

    if (*end != '\0') {
        return 0;
    }

    *out_value = value;
    return 1;
}

static int read_int(const char *prompt, int *out_value) {
    char line[128];
    char *end = NULL;

    printf("%s", prompt);

    if (fgets(line, sizeof(line), stdin) == NULL) {
        return 0;
    }

    long value = strtol(line, &end, 10);

    if (line == end) {
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        end++;
    }

    if (*end != '\0') {
        return 0;
    }

    *out_value = (int)value;
    return 1;
}

int main(void) {
    double temperature_c = 0.0;
    int heart_rate_bpm = 0;
    double oxygen_percent = 0.0;
    int warning_count = 0;

    printf("Patient Vital Check\n");
    printf("===================\n");
    printf("Learning simulation only. This is not medical software.\n\n");

    if (!read_double("Enter temperature in C: ", &temperature_c)) {
        printf("Invalid temperature input.\n");
        return 1;
    }

    if (!read_int("Enter heart rate in bpm: ", &heart_rate_bpm)) {
        printf("Invalid heart rate input.\n");
        return 1;
    }

    if (!read_double("Enter oxygen saturation in %: ", &oxygen_percent)) {
        printf("Invalid oxygen saturation input.\n");
        return 1;
    }

    if (temperature_c < 25.0 || temperature_c > 45.0) {
        printf("Temperature outside expected simulation range.\n");
        return 1;
    }

    if (heart_rate_bpm < 20 || heart_rate_bpm > 250) {
        printf("Heart rate outside expected simulation range.\n");
        return 1;
    }

    if (oxygen_percent < 0.0 || oxygen_percent > 100.0) {
        printf("Oxygen saturation must be between 0 and 100 percent.\n");
        return 1;
    }

    printf("\nResult:\n");

    // Körpertemperaturauswertung
    if (temperature_c < 36.0) {
        printf("Temperature: Low\n");
        warning_count++;
    } else if (temperature_c <= 37.5) {
        printf("Temperature: Normal\n");
    } else {
        printf("Temperature: Fever\n");
        warning_count++;
    }

    // Auswertung der Herzschlagrate
    if (heart_rate_bpm < 60) {
        printf("Heart rate: Low\n");
        warning_count++;
    } else if (heart_rate_bpm <= 100) {
        printf("Heart rate: Normal\n");
    } else {
        printf("Heart rate: High\n");
        warning_count++;
    }

    // Auswertung der Sauerstoffsättigung des Blutes
    if (oxygen_percent < 90.0) {
        printf("Oxygen saturation: Critical\n");
        warning_count++;
    } else if (oxygen_percent < 95.0) {
        printf("Oxygen saturation: Low\n");
        warning_count++;
    } else {
        printf("Oxygen saturation: Normal\n");
    }

    printf("\n");

    // Bewertung des Patientenzustands
    if (warning_count == 0) {
        printf("Overall status: Stable\n");
    } else {
        printf("Overall status: Check patient\n");
    }

    return 0;
}
