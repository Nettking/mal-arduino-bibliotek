#include <Arduino.h>
#include <KeypadInput.h>
#include <string.h>

// Oppsett for tastatur (4x4 numerisk)
const byte ANTALL_RADER = 4;
const byte ANTALL_KOLONNER = 4;
const char KEYMAP[ANTALL_RADER * ANTALL_KOLONNER] = {
  '1','2','3','A',
  '4','5','6','B',
  '7','8','9','C',
  '*','0','#','D'
};
const byte RAD_PINNER[ANTALL_RADER] = {2, 3, 4, 5};
const byte KOLONNE_PINNER[ANTALL_KOLONNER] = {6, 7, 8, A1};

KeypadInput tastatur(RAD_PINNER, KOLONNE_PINNER, ANTALL_RADER, ANTALL_KOLONNER, KEYMAP);

template <size_t PIN_LENGDE>
class PinTilgangskontroll {
  public:
    PinTilgangskontroll(KeypadInput& keypad, const char (&riktigPin)[PIN_LENGDE])
      : _tastatur(keypad) {
      static_assert(PIN_LENGDE > 1, "PIN-koden må inneholde minst ett tegn");
      memcpy(_riktigPin, riktigPin, PIN_LENGDE);
      nullstillInndata();
    }

    void begin() {
      _tastatur.begin();
    }

    void oppdater() {
      _tastatur.read();
      const char tast = _tastatur.getKey();
      if (tast) {
        behandleTast(tast);
      }
    }

  private:
    KeypadInput& _tastatur;
    char _riktigPin[PIN_LENGDE];
    char _inndata[PIN_LENGDE];
    byte _indeks = 0;

    void nullstillInndata() {
      _indeks = 0;
      memset(_inndata, 0, sizeof(_inndata));
    }

    void behandleTast(char tast) {
      if (tast == '*') {
        tilbakestill();
      } else if (tast == '#') {
        bekreftPin();
      } else {
        leggTilSiffer(tast);
      }
    }

    void tilbakestill() {
      nullstillInndata();
      Serial.println("PIN tilbakestilt.");
    }

    void bekreftPin() {
      if (strcmp(_inndata, _riktigPin) == 0) {
        Serial.println("Tilgang gitt – riktig PIN!");
      } else {
        Serial.println("Feil PIN. Prøv igjen.");
      }
      nullstillInndata();
    }

    void leggTilSiffer(char tast) {
      if (_indeks < PIN_LENGDE - 1) {
        _inndata[_indeks++] = tast;
        Serial.print("Tast registrert (");
        Serial.print(_indeks);
        Serial.println(" sifre lagret)");
      } else {
        Serial.println("PIN er full. Trykk # for å bekrefte eller * for å slette.");
      }
    }
};

// Enkel PIN-kode for demo
const char RIKTIG_PIN[] = "1234";
PinTilgangskontroll<sizeof(RIKTIG_PIN)> tilgangskontroll(tastatur, RIKTIG_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.println("Taste inn PIN-kode. Bruk * for å slette, # for å bekrefte.");

  tilgangskontroll.begin();
}

void loop() {
  tilgangskontroll.oppdater();
  delay(100);
}
