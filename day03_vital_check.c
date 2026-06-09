#include <stdio.h>   // Stellt printf und fgets für Ein- und Ausgabe bereit.
#include <stdlib.h>  // Stellt strtod und strtol für sichere Zahlenumwandlung bereit.
#include <ctype.h>   // Stellt isspace bereit, um Leerzeichen am Eingabeende zu prüfen.

// Von Codex ergänzt: Hilfsfunktion, damit Nutzer 37,2 oder 37.2 eingeben können.
static void normalize_decimal_separator(char text[]) {       // Nimmt eine veränderbare Zeichenkette entgegen.
    for (size_t i = 0; text[i] != '\0'; i++) {               // Läuft Zeichen für Zeichen bis zum String-Ende.
        if (text[i] == ',') {                                // Prüft, ob das aktuelle Zeichen ein Komma ist.
            text[i] = '.';                                   // Ersetzt das Komma durch einen Punkt für C-Zahlen.
        }
    }
}

// Von Codex ergänzt: Liest eine Kommazahl robust ein und erkennt ungültige Eingaben.
static int read_double(const char *prompt, double *out_value) { // Bekommt einen Fragetext und einen Speicherort für das Ergebnis.
    char line[128];                                            // Reserviert Platz für die komplette Eingabezeile.
    char *end = NULL;                                          // Merkt sich später, wo die Umwandlung aufgehört hat.

    printf("%s", prompt);                                      // Gibt den Fragetext aus, z. B. "Enter temperature in C: ".

    if (fgets(line, sizeof(line), stdin) == NULL) {             // Liest eine ganze Zeile aus der Tastatur.
        return 0;                                              // Gibt Fehler zurück, falls keine Eingabe gelesen werden konnte.
    }

    normalize_decimal_separator(line);                         // Erlaubt deutsches Dezimalkomma durch Umwandlung in Punkt.
    double value = strtod(line, &end);                          // Wandelt den Text in eine double-Zahl um.

    if (line == end) {                                         // Prüft, ob gar keine Zahl erkannt wurde.
        return 0;                                              // Meldet ungültige Eingabe.
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {      // Überspringt erlaubte Leerzeichen nach der Zahl.
        end++;                                                 // Geht zum nächsten Zeichen.
    }

    if (*end != '\0') {                                        // Prüft, ob nach der Zahl noch unerlaubter Text steht.
        return 0;                                              // Meldet Fehler, z. B. bei "37abc".
    }

    *out_value = value;                                        // Schreibt die erkannte Zahl in die Variable aus main.
    return 1;                                                  // Meldet Erfolg.
}

// Von Codex ergänzt: Liest eine ganze Zahl robust ein und erkennt ungültige Eingaben.
static int read_int(const char *prompt, int *out_value) {       // Bekommt einen Fragetext und einen Speicherort für das Ergebnis.
    char line[128];                                            // Reserviert Platz für die komplette Eingabezeile.
    char *end = NULL;                                          // Merkt sich später, wo die Umwandlung aufgehört hat.

    printf("%s", prompt);                                      // Gibt den Fragetext aus, z. B. "Enter heart rate in bpm: ".

    if (fgets(line, sizeof(line), stdin) == NULL) {             // Liest eine ganze Zeile aus der Tastatur.
        return 0;                                              // Gibt Fehler zurück, falls keine Eingabe gelesen werden konnte.
    }

    long value = strtol(line, &end, 10);                        // Wandelt den Text als Dezimalzahl in eine long-Zahl um.

    if (line == end) {                                         // Prüft, ob gar keine Zahl erkannt wurde.
        return 0;                                              // Meldet ungültige Eingabe.
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {      // Überspringt erlaubte Leerzeichen nach der Zahl.
        end++;                                                 // Geht zum nächsten Zeichen.
    }

    if (*end != '\0') {                                        // Prüft, ob nach der Zahl noch unerlaubter Text steht.
        return 0;                                              // Meldet Fehler, z. B. bei "82bpm".
    }

    *out_value = (int)value;                                   // Schreibt die erkannte Zahl als int in die Variable aus main.
    return 1;                                                  // Meldet Erfolg.
}

int main(void) {
    double temperature_c = 0.0;
    int heart_rate_bpm = 0;
    double oxygen_percent = 0.0;
    int warning_count = 0;

    printf("Patient Vital Check\n");
    printf("===================\n");
    printf("Learning simulation only. This is not medical software.\n\n"); // Macht klar, dass es nur eine Lernsimulation ist.

    if (!read_double("Enter temperature in C: ", &temperature_c)) { // Fragt Temperatur ab und prüft, ob sie gültig ist.
        printf("Invalid temperature input.\n");                     // Gibt eine verständliche Fehlermeldung aus.
        return 1;                                                   // Beendet das Programm mit Fehlercode.
    }

    if (!read_int("Enter heart rate in bpm: ", &heart_rate_bpm)) { // Fragt Herzfrequenz ab und prüft, ob sie gültig ist.
        printf("Invalid heart rate input.\n");                     // Gibt eine verständliche Fehlermeldung aus.
        return 1;                                                  // Beendet das Programm mit Fehlercode.
    }

    if (!read_double("Enter oxygen saturation in %: ", &oxygen_percent)) { // Fragt Sauerstoffsättigung ab und prüft die Eingabe.
        printf("Invalid oxygen saturation input.\n");                      // Gibt eine verständliche Fehlermeldung aus.
        return 1;                                                          // Beendet das Programm mit Fehlercode.
    }

    if (temperature_c < 25.0 || temperature_c > 45.0) {      // Prüft, ob die Temperatur für diese Simulation unrealistisch ist.
        printf("Temperature outside expected simulation range.\n"); // Erklärt, warum das Programm stoppt.
        return 1;                                            // Beendet das Programm mit Fehlercode.
    }

    if (heart_rate_bpm < 20 || heart_rate_bpm > 250) {       // Prüft, ob die Herzfrequenz für diese Simulation unrealistisch ist.
        printf("Heart rate outside expected simulation range.\n"); // Erklärt, warum das Programm stoppt.
        return 1;                                            // Beendet das Programm mit Fehlercode.
    }

    if (oxygen_percent < 0.0 || oxygen_percent > 100.0) {    // Prüft, ob die Sauerstoffsättigung als Prozentwert gültig ist.
        printf("Oxygen saturation must be between 0 and 100 percent.\n"); // Erklärt den gültigen Bereich.
        return 1;                                            // Beendet das Programm mit Fehlercode.
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
