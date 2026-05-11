#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <ThingSpeak.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/* WIFI */
#define WIFI_SSID "Your_WiFi_SSID"
#define WIFI_PASSWORD "Your_WiFi_Password"

/* FIREBASE */
#define API_KEY "Your_Firebase_API_Key"
#define FIREBASE_DATABASE_URL "Your_Firebase_Database_URL"
#define FIREBASE_EMAIL "Your_Firebase_Email"
#define FIREBASE_PASSWORD "Your_Firebase_Password"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

/* THINGSPEAK */
#define THINGSPEAK_WRITE_API_KEY "Your_ThingSpeak_API_Key"
#define CHANNEL_ID 0   // Replace with your Channel ID
WiFiClient client;

/* LCD */
LiquidCrystal_I2C lcd(0x27, 16, 2);

/* PIR */
#define PIR_PIN D5

/* QUEUE DATA */
int latestToken = 0;
int nowServing = 0;
int avgServiceTime = 5;

/* PIR STATE LOCK */
bool motionActive = false;

// Display token and wait time on LCD
void displayLCD(int token, int waitTime) {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Your Token:");
  lcd.print(token);

  lcd.setCursor(0, 1);
  lcd.print("Wait:");
  lcd.print(waitTime);
  lcd.print(" min");
}

// Update ThingSpeak with latest queue data
void updateThingSpeak(int latestToken, int nowServing, int avgServiceTime) {

  ThingSpeak.setField(1, latestToken);
  ThingSpeak.setField(2, nowServing);
  ThingSpeak.setField(3, avgServiceTime);

  int response =
    ThingSpeak.writeFields(CHANNEL_ID,
                           THINGSPEAK_WRITE_API_KEY);

  if (response == 200) {
    Serial.println("ThingSpeak Updated");
  }
  else {
    Serial.print("ThingSpeak Failed. HTTP Response: ");
    Serial.println(response);
  }
}

void setup() {

  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);

  Wire.begin(D2, D1);

  lcd.init();
  lcd.backlight();
  lcd.print("Booting...");

  // Connect WiFi
  lcd.clear();
  lcd.print("WiFi Connecting");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  unsigned long startTime = millis();

  while (WiFi.status() != WL_CONNECTED &&
         millis() - startTime < 20000) {

    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {

    lcd.clear();
    lcd.print("WiFi OK");

    Serial.println("\nWiFi connected");

    // Firebase setup
    config.api_key = API_KEY;
    config.database_url = FIREBASE_DATABASE_URL;

    auth.user.email = FIREBASE_EMAIL;
    auth.user.password = FIREBASE_PASSWORD;

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    // ThingSpeak setup
    ThingSpeak.begin(client);

  }
  else {

    lcd.clear();
    lcd.print("WiFi Fail");

    Serial.println("\nWiFi connection failed");
  }

  // Get latest token from Firebase
  if (Firebase.getInt(fbdo,
      "/bankQueue/latestToken")) {

    latestToken = fbdo.intData();

    lcd.clear();
    lcd.print("Firebase OK");
  }
  else {

    lcd.clear();
    lcd.print("FB Fail");

    Serial.println(fbdo.errorReason());
  }

  // PIR warm-up
  lcd.clear();
  lcd.print("Calibrating PIR");

  delay(30000);   // 30 sec warm-up

  lcd.clear();
  lcd.print("Waiting...");
}

void loop() {

  int pir = digitalRead(PIR_PIN);

  if (pir == HIGH && motionActive == false) {

    motionActive = true;

    // Get average service time from Firebase
    if (Firebase.getInt(fbdo,
        "/bankQueue/avgServiceTime")) {

      avgServiceTime = fbdo.intData();
    }

    // Increment token
    latestToken++;

    // Update Firebase
    Firebase.setInt(fbdo,
                    "/bankQueue/latestToken",
                    latestToken);

    // Update ThingSpeak
    updateThingSpeak(latestToken,
                     nowServing,
                     avgServiceTime);

    // Calculate wait time
    int waitTime =
      (latestToken - nowServing)
      * avgServiceTime;

    if (waitTime < 0)
      waitTime = 0;

    // Update LCD
    displayLCD(latestToken, waitTime);

    Serial.println("Token updated");
  }

  if (pir == LOW &&
      motionActive == true) {

    motionActive = false;

    Serial.println("Ready for next motion");
  }

  delay(50);
}
