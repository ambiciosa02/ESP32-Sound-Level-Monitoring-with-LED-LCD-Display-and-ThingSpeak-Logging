#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Définir les broches
int ledPin = 15;  // LED normale
int soundPin = 34; // Capteur de son

// Connexion Wi-Fi
const char* ssid = "..........";
const char* password = ".........";

// ThingSpeak API
String server = "http://api.thingspeak.com/update";
String apiKey = "RVLB8LR1EE38CA70";

// Initialiser l'écran LCD (adresse 0x27 pour I2C)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Timer pour l'envoi de données
unsigned long lastTime = 0;
unsigned long timerDelay = 15000;

void setup() {
  // Initialisation de la broche LED
  pinMode(ledPin, OUTPUT);

  // Initialisation de l'écran LCD
  lcd.begin(16, 2); 
  lcd.print("Init WiFi...");

  // Connexion Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  lcd.clear();
  lcd.print("WiFi Connecte!");
  delay(2000);
  lcd.clear();

  Serial.begin(115200);
}

void loop() {
  // Lire la valeur du bruit
  int soundValue = analogRead(soundPin);
  Serial.print("Valeur bruit : ");
  Serial.println(soundValue);

  // Affichage du niveau sonore sur LCD
  lcd.setCursor(0, 0);
  lcd.print("Bruit: ");
  lcd.print(soundValue);

  // Activation de la LED si le niveau de bruit dépasse 20
  if (soundValue > 20) {
    digitalWrite(ledPin, HIGH);  // Allumer la LED
    lcd.setCursor(0, 1);
    lcd.print("Bruit Eleve!");
  } else {
    digitalWrite(ledPin, LOW);  // Éteindre la LED
    lcd.setCursor(0, 1);
    lcd.print("Niveau OK    ");
  }

  // Envoi des données vers ThingSpeak
  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      String url = server + "?api_key=" + apiKey + "&field1=" + String(soundValue);
      http.begin(url);
      int httpResponseCode = http.GET();

      if (httpResponseCode > 0) {
        Serial.print("Envoyé ! Code réponse : ");
        Serial.println(httpResponseCode);
      } else {
        Serial.print("Erreur d'envoi : ");
        Serial.println(httpResponseCode);
      }
      http.end();
    }
    lastTime = millis();
  }

  delay(1000);
}
