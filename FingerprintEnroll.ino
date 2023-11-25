#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

#define RX_PIN 2
#define TX_PIN 3
#define SOLENOID_PIN 4

SoftwareSerial mySerial(RX_PIN, TX_PIN);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup() {
  Serial.begin(9600);
  mySerial.begin(57600);

  pinMode(SOLENOID_PIN, OUTPUT);
  digitalWrite(SOLENOID_PIN, LOW);

  if (!finger.begin()) {
    Serial.println("Couldn't find fingerprint sensor :(");
    while (1);
  }

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }
}

void loop() {
  Serial.println("Place your finger on the sensor.");

  if (finger.getImage() == FINGERPRINT_OK) {
    Serial.println("Image taken");
    delay(500);

    int id = -1;

    while (id == -1) {
      id = finger.getImageFingerID();
      delay(50);
    }

    Serial.print("Finger ID found: "); Serial.println(id);

    if (finger.createModel() == FINGERPRINT_OK) {
      Serial.println("Remove your finger");
      delay(2000);
      Serial.println("Place the same finger again");

      while (finger.getImage() != FINGERPRINT_OK);

      if (finger.createModel() == FINGERPRINT_OK) {
        Serial.println("Fingerprint enrolled successfully!");

        // Activate the solenoid lock
        digitalWrite(SOLENOID_PIN, HIGH);
        delay(5000); // Keep the solenoid active for 5 seconds (you can adjust as needed)
        digitalWrite(SOLENOID_PIN, LOW);

      } else {
        Serial.println("Failed to enroll fingerprint, please try again.");
      }
    } else {
      Serial.println("Failed to create model, please try again.");
    }
  }

  delay(1000); // Wait for a second before the next attempt
}
