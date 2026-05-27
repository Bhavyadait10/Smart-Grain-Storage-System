#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <WiFi.h>
#include <HTTPClient.h>

// --- 1. NETWORK CONFIGURATION ---
const char* ssid = "Your_WiFi_SSID";
const char* password = "Your_WiFi_Password";
String GOOGLE_SCRIPT_ID = "Your_Google_Script_ID";

// --- 2. THRESHOLDS ---
const float MAX_TEMP = 30.0;     
const float MIN_TEMP = 27.0;     
const int MOISTURE_THRESHOLD = 2500; 

// --- 3. PIN DEFINITIONS ---
#define DHT_PIN 12               
#define MOIST_PIN 34             
#define GAS_PIN 35               
#define VIB_PIN 15               
#define FAN_PIN 27               
#define LED_PIN 26               

// --- 4. OBJECTS ---
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define DHTTYPE DHT22
DHT dht(DHT_PIN, DHTTYPE);

// --- 5. VARIABLES ---
float temp = 0.0;
int moist = 0, gas = 0, vibrationState = HIGH;
unsigned long lastSendTime = 0;

// FAST INTERVAL: Now 3 seconds as requested
const long sendInterval = 3000; 

// LED Timer Variables
unsigned long ledOnTime = 0;
bool ledIsOn = false;

void setup() {
  Serial.begin(115200);
  
  // Initialize Peripherals
  lcd.init(); 
  lcd.backlight();
  pinMode(FAN_PIN, OUTPUT); 
  pinMode(LED_PIN, OUTPUT); 
  pinMode(VIB_PIN, INPUT);
  
  // Start with everything OFF (No initial blinking)
  digitalWrite(FAN_PIN, LOW); 
  digitalWrite(LED_PIN, LOW);
  
  dht.begin();
  
  // WiFi Connection
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connecting");
  WiFi.begin(ssid, password);
  
  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 20) {
    delay(500);
    Serial.print(".");
    retry++;
  }

  lcd.clear();
  if(WiFi.status() == WL_CONNECTED) {
    lcd.print("WiFi Online!");
  } else {
    lcd.print("WiFi Offline");
  }
  delay(1000);
  lcd.clear();
}

void loop() {
  // --- A. DATA ACQUISITION ---
  float t = dht.readTemperature();
  if (!isnan(t)) temp = t;
  
  moist = analogRead(MOIST_PIN);
  gas = analogRead(GAS_PIN);
  vibrationState = digitalRead(VIB_PIN);

  // --- B. FAN CONTROL ---
  if (temp >= MAX_TEMP) digitalWrite(FAN_PIN, HIGH);
  else if (temp <= MIN_TEMP) digitalWrite(FAN_PIN, LOW);

  // --- C. VIBRATION ALERT (One-Shot logic remains) ---
  // The LED only turns on IF vibration is detected, not for every data sync.
  if (vibrationState == LOW && !ledIsOn) {
    digitalWrite(LED_PIN, HIGH);
    ledIsOn = true;
    ledOnTime = millis();
  }
  if (ledIsOn && (millis() - ledOnTime >= 5000)) {
    digitalWrite(LED_PIN, LOW);
    ledIsOn = false;
  }

  // --- D. DISPLAY UPDATE ---
  updateDisplay();

  // --- E. CLOUD SYNC (Silent - No Blinking) ---
  if (millis() - lastSendTime > sendInterval) {
    sendDataToGoogle();
    lastSendTime = millis();
  }
  
  // Small delay for system stability
  delay(100); 
}

void updateDisplay() {
  lcd.setCursor(0, 0);
  String fStatus = digitalRead(FAN_PIN) ? "ON " : "OFF";
  lcd.print("T:" + String(temp, 1) + "C Fan:" + fStatus);
  
  lcd.setCursor(0, 1);
  String mStatus = (moist < MOISTURE_THRESHOLD) ? "WET" : "DRY";
  String vStatus = (vibrationState == LOW) ? "YES" : "NO ";
  lcd.print("M:" + mStatus + " Vib:" + vStatus + "    ");
}

void sendDataToGoogle() {
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    
    // Constructing the URL string
    String url = "https://script.google.com/macros/s/" + GOOGLE_SCRIPT_ID + "/exec?";
    url += "temp=" + String(temp);
    url += "&m1=" + String(moist);
    url += "&gas=" + String(gas);
    url += "&vib=" + String(vibrationState == LOW ? 1 : 0);
    url += "&fan=" + String(digitalRead(FAN_PIN));

    // We only print to Serial, no light blink triggered here.
    Serial.println("Fast Syncing...");
    
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    http.begin(url);
    
    int httpCode = http.GET();
    if (httpCode <= 0) {
      Serial.println("Sync Error: " + http.errorToString(httpCode));
    }
    
    http.end();
  }
}
