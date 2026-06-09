#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Erlaubt bei Kommazahlen sowohl 37.2 als auch 37,2.
static void normalize_decimal_separator(char text[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == ',') {
            text[i] = '.';
        }
    }
}

// Liest eine Kommazahl ein und erkennt ungültige Eingaben wie "abc" oder "37abc".
static int read_double(const char *prompt, double *out_value) {
    char line[100];
    char *end = NULL;

    printf("%s", prompt);

    if (fgets(line, sizeof(line), stdin) == NULL) {
        return 0;
    }

    normalize_decimal_separator(line);
    *out_value = strtod(line, &end);

    if (line == end) {
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        end++;
    }

    return *end == '\0';
}

// Liest eine ganze Zahl ein und erkennt ungültige Eingaben wie "abc" oder "82bpm".
static int read_int(const char *prompt, int *out_value) {
    char line[100];
    char *end = NULL;
    long value = 0;

    printf("%s", prompt);

    if (fgets(line, sizeof(line), stdin) == NULL) {
        return 0;
    }

    value = strtol(line, &end, 10);

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

    if (!read_double("Enter temperature in C, for example 37.2 or 37,2: ", &temperature_c)) {
        printf("Invalid temperature input.\n");
        return 1;
    }

    if (!read_int("Enter heart rate in bpm, for example 82: ", &heart_rate_bpm)) {
        printf("Invalid heart rate input.\n");
        return 1;
    }

    if (!read_double("Enter oxygen saturation in percent, for example 98.5 or 98,5: ", &oxygen_percent)) {
        printf("Invalid oxygen saturation input.\n");
        return 1;
    }

    printf("\nResult:\n");

    // Körpertemperatur auswerten.
    if (temperature_c < 36.0) {
        printf("Temperature: Low\n");
        warning_count++;
    } else if (temperature_c <= 37.5) {
        printf("Temperature: Normal\n");
    } else {
        printf("Temperature: Fever\n");
        warning_count++;
    }

    // Herzfrequenz auswerten.
    if (heart_rate_bpm < 60) {
        printf("Heart rate: Low\n");
        warning_count++;
    } else if (heart_rate_bpm <= 100) {
        printf("Heart rate: Normal\n");
    } else {
        printf("Heart rate: High\n");
        warning_count++;
    }

    // Sauerstoffsättigung auswerten.
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

    // Gesamtstatus anhand der Anzahl auffälliger Werte ausgeben.
    if (warning_count == 0) {
        printf("Overall status: Stable\n");
    } else {
        printf("Overall status: Check patient\n");
    }

    return 0;
}
