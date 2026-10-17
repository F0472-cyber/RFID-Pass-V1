
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const byte RFID_SS_PIN = 10;
const byte RFID_RST_PIN = 9;

MFRC522 rfid(RFID_SS_PIN, RFID_RST_PIN);

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte RELAY_PIN = 7;

const byte RELAY_ON = LOW;
const byte RELAY_OFF = HIGH;

const unsigned long ACCESS_DURATION = 500;

const char BADGE_AUTORISE[] = "C53B5C01";
const char BADGE_REFUSE[] = "13C63B0E";

void afficherLCD(const char* ligne1, const char* ligne2) {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(ligne1);

  lcd.setCursor(0, 1);
  lcd.print(ligne2);
}

String lireUID() {
  String uid = "";

  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) {
      uid += "0";
    }

    uid += String(rfid.uid.uidByte[i], HEX);
  }

  uid.toUpperCase();

  return uid;
}

void ouvrirAcces() {
  Serial.println("RELAIS : ACTIVATION");

  afficherLCD("ACCES AUTORISE", "Ouverture...");

  digitalWrite(RELAY_PIN, RELAY_ON);

  delay(ACCESS_DURATION);

  digitalWrite(RELAY_PIN, RELAY_OFF);

  Serial.println("RELAIS : DESACTIVE");
}

void setup() {
  Serial.begin(9600);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, RELAY_OFF);

  SPI.begin();
  rfid.PCD_Init();

  Wire.begin();
  lcd.init();
  lcd.backlight();

  afficherLCD("RFID PASS V1", "Demarrage...");

  Serial.println("================================");
  Serial.println("          RFID PASS V1");
  Serial.println("================================");
  Serial.println("Lecteur RFID initialise");
  Serial.println("Ecran LCD initialise");
  Serial.println("Relais initialise");
  Serial.println("En attente d'un badge...");

  delay(1500);

  afficherLCD("RFID PASS V1", "Presentez badge");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  String uid = lireUID();

  Serial.println();
  Serial.println("----- BADGE DETECTE -----");
  Serial.print("UID : ");
  Serial.println(uid);

  if (uid == BADGE_AUTORISE) {
    Serial.println("RESULTAT : ACCES AUTORISE");
    ouvrirAcces();
  }
  else if (uid == BADGE_REFUSE) {
    Serial.println("RESULTAT : ACCES REFUSE");
    afficherLCD("ACCES REFUSE", "Badge bleu");
  }
  else {
    Serial.println("RESULTAT : BADGE INCONNU");
    Serial.println("Acces refuse par defaut");
    afficherLCD("BADGE INCONNU", "ACCES REFUSE");
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  delay(2000);

  afficherLCD("RFID PASS V1", "Presentez badge");

  Serial.println("En attente d'un badge...");
}
