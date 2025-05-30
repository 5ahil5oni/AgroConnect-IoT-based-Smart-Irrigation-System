#define BLYNK_TEMPLATE_ID "TMPL3ahVrwjX8"
#define BLYNK_TEMPLATE_NAME "Soil Irrigation"
#define BLYNK_AUTH_TOKEN "0MAEitWIyfQKjxLB0MZ380NDjdk5zZfN"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <DHT.h>
#include <BlynkSimpleEsp8266.h>
#include <LiquidCrystal_I2C.h>
//#include <BlynkTimer.h> // Added BlynkTimer library
LiquidCrystal_I2C lcd(0x27, 16, 2);
char auth[] = BLYNK_AUTH_TOKEN; // Enter your Blynk authentication token
char ssid[] = "Agroconnect"; // Enter your WiFi SSID
char pass[] = "12345678"; // Enter your WiFi password
#define DHTPIN 2 // What digital pin we're connected to
// Uncomment whatever type you're using!
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21 // DHT 21, AM2301
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
//#define trig 13
//#define echo 12
const int trig = D5;
const int echo = D6;
int MaxLevel = 12;
int Level1 = (MaxLevel * 75) / 100;
int Level2 = (MaxLevel * 65) / 100;
int Level3 = (MaxLevel * 55) / 100;
int Level4 = (MaxLevel * 45) / 100;
int Level5 = (MaxLevel * 35) / 100;
void setup() {
Serial.begin(9600);
dht.begin();
lcd.init(); // Initialize the LCD with correct column and row count
lcd.backlight();
pinMode(trig, OUTPUT);
pinMode(echo, INPUT);
pinMode(16,OUTPUT);
digitalWrite(16,LOW);
Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
Serial.print("LCD 1");
lcd.setCursor(3, 0); //Set cursor to first column of first row
lcd.print("IoT Based");
Serial.print("LCD 2");
delay(2000);
lcd.clear();
lcd.setCursor(3, 0);
lcd.print("Flood level");
lcd.setCursor(3, 1);
lcd.print("Monitoring");
delay(2000);
lcd.clear();
// Call the functions
timer.setInterval(1000L, ultrasonic);
timer.setInterval(5000L, sendSensor);
timer.setInterval(2000L, rain);
}
void loop() {
Blynk.run();
timer.run(); // Run the BlynkTimer
delay(1000);
}
void ultrasonic() {
digitalWrite(trig, LOW);
delayMicroseconds(4);
digitalWrite(trig, HIGH);
delayMicroseconds(10);
digitalWrite(trig, LOW);
long t = pulseIn(echo, HIGH);
int distance = t * (0.034 / 2);
//Serial.println(distance);
int blynkDistance = (distance - MaxLevel) * -1;
if (distance <= MaxLevel) {
Serial.print("Distance: ");
Serial.print(blynkDistance);
Serial.println(" cm");
} else {
Blynk.virtualWrite(V0, 0);
}
lcd.setCursor(0, 0);
lcd.print("Lev:");
if (Level1 <= distance) {
lcd.setCursor(4, 0); // Corrected column position
lcd.print("VLow ");
Blynk.virtualWrite(V0, 0);
digitalWrite(16,LOW);
} else if (Level2 <= distance && Level1 > distance) {
lcd.setCursor(4, 0); // Corrected column position
lcd.print("Low ");
lcd.print(" ");
Blynk.virtualWrite(V0, blynkDistance);
digitalWrite(16,LOW);
} else if (Level3 <= distance && Level2 > distance) {
lcd.setCursor(4, 0); // Corrected column position
lcd.print("Medium ");
lcd.print(" ");
Blynk.virtualWrite(V0, blynkDistance);
digitalWrite(16,LOW);
} else if (Level4 <= distance && Level3 > distance) {
lcd.setCursor(4, 0); // Corrected column position
lcd.print("High ");
lcd.print(" ");
Blynk.virtualWrite(V0, blynkDistance);
digitalWrite(16,LOW);
} else if (Level5 >= distance) {
lcd.setCursor(4, 0); // Corrected column position
lcd.print("Full ");
lcd.print(" ");
Blynk.virtualWrite(V0, blynkDistance);
digitalWrite(16,HIGH);
}
}
void sendSensor()
{
int h = dht.readHumidity();
float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
Serial.print(t);
Serial.println(" degree");
Serial.print(h);
Serial.println(" %");
lcd.setCursor(0, 1);
lcd.print("T:");
lcd.print(t);
lcd.print(char(223));
lcd.print("C ");
lcd.print("H:");
lcd.print(h);
lcd.print("%");
if (isnan(h) || isnan(t)) {
Serial.println("Failed to read from DHT sensor!");
return;
}
// You can send any value at any time.
// Please don't send more that 10 values per second.
Blynk.virtualWrite(V2, h);
Blynk.virtualWrite(V1, t);
}
void rain(){
int rain = analogRead(A0);
int sm1 = map(rain,1024,0,0,80);
int sm = map(sm1,0,80,0,100);
Serial.print("SM:");
Serial.print(sm);
Serial.println("%");
Serial.println(rain);
Blynk.virtualWrite(V3, sm);
if(rain>900){
lcd.setCursor(10, 0);
lcd.print(" Dry ");
Blynk.logEvent("dry");
}
else if( rain < 900 && rain >500) {
// Blynk.virtualWrite(V3, sm);
lcd.setCursor(10, 0);
lcd.print(" Good ");
}
else if(rain<500){
//Blynk.virtualWrite(V3, sm);
lcd.setCursor(10, 0);
lcd.print(" wet ");
}
}

