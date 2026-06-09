# C Medizintechnik Vorbereitung

Kleine C-Übungen zur Vorbereitung auf ein Medizintechnikstudium. Die Programme simulieren einfache Vitalwert-Ausgaben und Grenzwertprüfungen auf der Konsole.

> Hinweis: Alle Beispiele sind reine Lernsimulationen und keine medizinische Software.

## Inhalt

| Datei | Thema |
|---|---|
| `day01_medtech_monitor.c` | erste Konsolenausgabe mit `printf` |
| `day02_vital_values.c` | Variablen, Datentypen und Format-Platzhalter |
| `day03_vital_check.c` | Eingaben, Komma-Umwandlung, Gültigkeitserkennung, Bedingungen und Warnzähler |

## Voraussetzungen

- macOS, Linux oder Windows mit C-Compiler
- empfohlen: `gcc`
- optional: `make`

Compiler prüfen:

```bash
gcc --version
```

Falls `gcc` auf macOS fehlt:

```bash
xcode-select --install
```

## Ausführen mit Makefile

Alle Programme kompilieren:

```bash
make
```

Einzelne Programme starten:

```bash
make run-day01
make run-day02
make run-day03
```

Build-Dateien löschen:

```bash
make clean
```

## Ohne Makefile kompilieren

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -g day01_medtech_monitor.c -o day01_medtech_monitor
./day01_medtech_monitor
```

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -g day02_vital_values.c -o day02_vital_values
./day02_vital_values
```

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -g day03_vital_check.c -o day03_vital_check
./day03_vital_check
```

## Beispiel für `day03_vital_check`

Eingabe mit Dezimalpunkt:

```text
37.2
82
98.5
```

Alternativ funktioniert bei Dezimalzahlen auch ein Komma:

```text
37,2
82
98,5
```

Erwartete Ausgabe:

```text
Temperature: Normal
Heart rate: Normal
Oxygen saturation: Normal

Overall status: Stable
```

## Lernziele

- C-Programme mit `main` strukturieren
- `printf` und Format-Platzhalter verwenden
- Zahlen und Zeichenketten ausgeben
- Eingaben verarbeiten
- Werte mit `if`/`else` klassifizieren
- einfache Fehlerbehandlung schreiben
- mit `-Wall -Wextra -Wpedantic` sauber kompilieren
