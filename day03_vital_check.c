#include <stdio.h>
#include <stdlib.h>  // Codex: Wird für strtod und strtol gebraucht, um Text sicher in Zahlen umzuwandeln.
#include <ctype.h>   // Codex: Wird für isspace gebraucht, um Leerzeichen nach der Eingabe zu erkennen.

// Codex: Ab hier beginnt die von Codex ergänzte Eingabe-Hilfe.
// Codex: Diese Funktion erlaubt bei Kommazahlen sowohl 37.2 als auch 37,2.
static void normalize_decimal_separator(char text[]) { // Codex: Die Funktion bekommt einen Text, der verändert werden darf.
    for (int i = 0; text[i] != '\0'; i++) {            // Codex: Geht jedes Zeichen durch, bis das String-Ende erreicht ist.
        if (text[i] == ',') {                          // Codex: Prüft, ob das aktuelle Zeichen ein Komma ist.
            text[i] = '.';                             // Codex: Ersetzt das Komma durch einen Punkt, weil C Dezimalpunkte erwartet.
        }
    }
}

// Codex: Diese Funktion liest eine Kommazahl ein und erkennt ungültige Eingaben wie "abc" oder "37abc".
static int read_double(const char *prompt, double *out_value) { // Codex: prompt ist der Fragetext, out_value speichert das Ergebnis.
    char line[100];                                             // Codex: Hier wird die komplette Eingabezeile zwischengespeichert.
    char *end = NULL;                                           // Codex: end zeigt später auf das erste Zeichen nach der gelesenen Zahl.

    printf("%s", prompt);                                       // Codex: Gibt den Fragetext aus.

    if (fgets(line, sizeof(line), stdin) == NULL) {              // Codex: Liest eine ganze Zeile von der Tastatur.
        return 0;                                               // Codex: Gibt 0 zurück, wenn das Lesen fehlgeschlagen ist.
    }

    normalize_decimal_separator(line);                          // Codex: Wandelt ein deutsches Komma in einen Dezimalpunkt um.
    *out_value = strtod(line, &end);                             // Codex: Wandelt den Text in eine double-Zahl um.

    if (line == end) {                                          // Codex: Wenn nichts gelesen wurde, war die Eingabe keine Zahl.
        return 0;                                               // Codex: Meldet ungültige Eingabe.
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {       // Codex: Überspringt Leerzeichen oder Zeilenumbruch nach der Zahl.
        end++;                                                  // Codex: Geht zum nächsten Zeichen weiter.
    }

    return *end == '\0';                                        // Codex: Gibt 1 zurück, wenn nach der Zahl kein falscher Text mehr steht.
}

// Codex: Diese Funktion liest eine ganze Zahl ein und erkennt ungültige Eingaben wie "abc" oder "82bpm".
static int read_int(const char *prompt, int *out_value) { // Codex: prompt ist der Fragetext, out_value speichert das Ergebnis.
    char line[100];                                      // Codex: Hier wird die komplette Eingabezeile zwischengespeichert.
    char *end = NULL;                                    // Codex: end zeigt später auf das erste Zeichen nach der gelesenen Zahl.
    long value = 0;                                      // Codex: strtol liefert eine long-Zahl, die danach in int umgewandelt wird.

    printf("%s", prompt);                                // Codex: Gibt den Fragetext aus.

    if (fgets(line, sizeof(line), stdin) == NULL) {       // Codex: Liest eine ganze Zeile von der Tastatur.
        return 0;                                        // Codex: Gibt 0 zurück, wenn das Lesen fehlgeschlagen ist.
    }

    value = strtol(line, &end, 10);                       // Codex: Wandelt den Text als Dezimalzahl in eine long-Zahl um.

    if (line == end) {                                   // Codex: Wenn nichts gelesen wurde, war die Eingabe keine Zahl.
        return 0;                                        // Codex: Meldet ungültige Eingabe.
    }

    while (*end != '\0' && isspace((unsigned char)*end)) { // Codex: Überspringt Leerzeichen oder Zeilenumbruch nach der Zahl.
        end++;                                            // Codex: Geht zum nächsten Zeichen weiter.
    }

    if (*end != '\0') {                                  // Codex: Prüft, ob nach der Zahl noch unerlaubter Text steht.
        return 0;                                        // Codex: Meldet ungültige Eingabe.
    }

    *out_value = (int)value;                             // Codex: Speichert die gelesene Zahl in der Variable aus main.
    return 1;                                            // Codex: Meldet erfolgreiche Eingabe.
}
// Codex: Hier endet die von Codex ergänzte Eingabe-Hilfe.

int main(void) {
    double temperature_c = 0.0;
    int heart_rate_bpm = 0;
    double oxygen_percent = 0.0;
    int warning_count = 0;

    printf("Patient Vital Check\n");
    printf("===================\n");
    printf("Learning simulation only. This is not medical software.\n\n");

    if (!read_double("Enter temperature in C, for example 37.2 or 37,2: ", &temperature_c)) { // Codex: Liest Temperatur mit Punkt- oder Kommaeingabe.
        printf("Invalid temperature input.\n");                                               // Codex: Meldet eine ungültige Temperatur-Eingabe.
        return 1;                                                                             // Codex: Beendet das Programm mit Fehlercode.
    }

    if (!read_int("Enter heart rate in bpm, for example 82: ", &heart_rate_bpm)) { // Codex: Liest die Herzfrequenz als ganze Zahl.
        printf("Invalid heart rate input.\n");                                     // Codex: Meldet eine ungültige Herzfrequenz-Eingabe.
        return 1;                                                                  // Codex: Beendet das Programm mit Fehlercode.
    }

    if (!read_double("Enter oxygen saturation in percent, for example 98.5 or 98,5: ", &oxygen_percent)) { // Codex: Liest Sauerstoffsättigung mit Punkt- oder Kommaeingabe.
        printf("Invalid oxygen saturation input.\n");                                                      // Codex: Meldet eine ungültige Sauerstoff-Eingabe.
        return 1;                                                                                          // Codex: Beendet das Programm mit Fehlercode.
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
