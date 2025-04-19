#include <Adafruit_Fingerprint.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
SoftwareSerial mySerial(2, 3); //Serial Communications
 
 
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
 
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
 
#define Relay 4
 
void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  
  finger.begin(57600);
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, HIGH);
  delay(5);
  
  if (finger.verifyPassword()) {
    
    lcd.setCursor(0,0);
    lcd.print("  Finger Print ");
    Serial.println("  Finger Print ");
    lcd.setCursor(0, 1);
    lcd.print("Sensor Connected");
    Serial.println("Sensor Connected");
    delay (3000);
    
  } else {
    lcd.setCursor(0,0);
    lcd.print("Unable to found   ");
    Serial.println("Unable to found   ");
    lcd.setCursor(0,1);
    lcd.print("Sensor");
    Serial.println("Sensor");
    delay(2000);
    
      lcd.setCursor(0, 0);
    lcd.print("Please Check    ");
    Serial.println("Please Check    ");
    lcd.setCursor(0,1);
    lcd.print("  Sensor Wiring ");
    Serial.println("  Sensor Wiring ");
    while (1) { 
    delay(1); }
  }
 
  
}
 
void loop()  
{
  lcd.setCursor(0,0);
  lcd.print("Place finger...");
  Serial.println("Place finger...");
  lcd.setCursor(0,1);
  lcd.print("   start scan    ");
  Serial.println("   start scan    ");
  getFingerprintID();
  delay(50);            //don't ned to run this at full speed.
}
 
uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  if(p == FINGERPRINT_NOFINGER){
    return p;
  }
  else if(p != FINGERPRINT_OK){
    lcd.setCursor(0,0);
    lcd.print("Scan Error      ");
    Serial.println("Scan Error      ");
    lcd.setCursor(0,1);
    
    delay(2000);
    return p;  
  }
  
  p = finger.image2Tz();
  if(p != FINGERPRINT_OK){
    lcd.setCursor(0,0);
    lcd.print("Processing Error");
    Serial.println("Processing Error");
    lcd.setCursor(0,1);
    lcd.print(" Try Again ");
    Serial.println(" Try Again ");
    return p;
  }
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Door Unlocked");
  Serial.println("  Door Unlocked");
  lcd.setCursor(0, 1);
  lcd.print("    Welcome");
  Serial.println("    Welcome");
 
    digitalWrite(Relay,LOW);
    delay(5000);
    
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    lcd.setCursor(0,0);
    lcd.print("Comm Error      ");
    Serial.println("Comm Error      ");
    lcd.setCursor(0,1);
    lcd.print("                ");
    Serial.println("                ");
    delay(2000);
    return p;
 
    
  } else if (p == FINGERPRINT_NOTFOUND) {
    lcd.setCursor(0,0);
    lcd.print("Access Denied   ");
    Serial.println("Access Denied   ");
    lcd.setCursor(0,1);
    lcd.print("                ");
    delay(2000);
    return p;
  } else {
    lcd.setCursor(0,0);
    lcd.print("Error in matching");
    Serial.println("Error in matching");
    lcd.setCursor(0,1);
    lcd.print("Not Valid Finger");
    Serial.println("Not Valid Finger");
    delay(2000);
    return p;
  }
  digitalWrite(Relay,HIGH);
  return finger.fingerID;
}