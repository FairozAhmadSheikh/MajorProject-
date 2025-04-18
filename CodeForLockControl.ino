#include <Adafruit_Fingerprint.h>

SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

#define RELAY_PIN       4
#define ACCESS_DELAY    3000 // Keep lock unlocked for 3 seconds 


void setup()
{
  // set the data rate for the sensor serial port
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) 
  {
  } 
  else 
  {
    while (1) { delay(1); }
  }
  
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);   //Switch off relay initially. Relay is LOW level triggered relay so we need to write HIGH.
}