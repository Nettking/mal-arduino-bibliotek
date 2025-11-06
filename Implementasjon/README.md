# Implementasjon

Denne mappen samler eksempler og bibliotekskode som viser hvordan du kan bygge videre på mal-arduino-biblioteket. Strukturen speiler hvordan du typisk organiserer prosjekter når du jobber med flere sensorer eller vil teste funksjonalitet i isolasjon.

## Mapper

- `examples/` – Ferdige Arduino-skisser som demonstrerer hvordan biblioteket kan brukes i praksis. Hver undermappe inneholder en skisse med egen `*.ino`-fil og eventuell tilhørende kode.
- `libraries/` – Gjenbrukbare komponenter og hjelpebibliotek som kan importeres i skissene. Her kan du legge kode som er for omfattende til å ligge direkte i en eksempelmappe.

## Tips til videre arbeid

1. Start med å lese README-en i rotmappen for å forstå grensesnittet mellom skissene og sensorkoden.
2. Opprett en ny mappe i `examples/` når du vil lage en konkret demonstrasjon, for eksempel `examples/min-sensor/`.
3. Legg delte hjelpefunksjoner i `libraries/` slik at de kan brukes på tvers av eksempler uten duplisering.
4. Dokumenter hver nye komponent med en kort README eller kommentarer, slik at andre lett ser hva som må til for å ta den i bruk.

Med denne strukturen kan du eksperimentere raskt, samtidig som du beholder oversikt over gjenbrukbar kode.
