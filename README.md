# 🔐 Fingerprint-Based Door Lock System

A secure, embedded access control system built with Arduino and C++ that uses biometric fingerprint authentication to control a door lock. The system captures, enrolls, and verifies fingerprints in real-time, granting or denying access based on stored biometric templates.

---

## 📌 Overview

Traditional key-based or PIN-based door locks are vulnerable to theft and guessing. This project replaces them with a **biometric authentication system** — only registered fingerprints can unlock the door. The system provides real-time feedback via an LCD display and controls a relay module that physically actuates the lock.

---

## 🛠️ Hardware Components

| Component | Description |
|---|---|
| Arduino Uno / Nano | Main microcontroller |
| AS608 Fingerprint Sensor | Optical fingerprint scanner |
| 16×2 I2C LCD Display | User feedback and status messages |
| Relay Module (5V) | Controls the door lock mechanism |
| Door Lock / Solenoid | Physical locking actuator |
| Jumper Wires & Breadboard | Circuit connections |
| Power Supply (5V/12V) | Powers the system |

---
## ⚙️ System Architecture

The system is split into two distinct operational modes, each handled by a separate Arduino sketch:

```
┌─────────────────────────────────────────────────────┐
│                   ENROLLMENT MODE                   │
│             (FingerprintEnroll.ino)                 │
│                                                     │
│  Serial Monitor → Read ID → Capture Image (×2)     │
│       → Convert to Template → Store in Flash        │
└─────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────┐
│                 LOCK CONTROL MODE                   │
│             (CodeForLockControl.ino)                │
│                                                     │
│  Scan Finger → Image → Template → Search DB         │
│    → Match Found: Relay LOW (Unlock, 5s)            │
│    → No Match:   Relay HIGH (Stay Locked)           │
└─────────────────────────────────────────────────────┘
```

---
## 📂 File Structure

```
MajorProject-/
├── FingerprintEnroll.ino     # Enrollment sketch — register new fingerprints
└── CodeForLockControl.ino    # Main lock sketch — scan and control access
```

---

## 🚀 How It Works

### Phase 1 — Fingerprint Enrollment (`FingerprintEnroll.ino`)

1. Open Serial Monitor at **9600 baud**.
2. Enter an ID number (1–127) to assign to the fingerprint.
3. Place finger on the sensor — image is captured and converted to a template.
4. Remove and re-place the same finger for confirmation.
5. The two templates are compared, merged into a model, and stored in the sensor's flash memory.
6. To clear all stored fingerprints, enter `-1`.

**Sensor parameters printed on startup:**
- Status register, System ID, Storage capacity (up to 127 templates)
- Security level, Device address, Packet length, Baud rate

### Phase 2 — Lock Control (`CodeForLockControl.ino`)

1. LCD displays **"Place finger... start scan"** in a continuous loop.
2. On finger placement, the sensor captures an image and converts it to a template.
3. The template is searched against the stored database.
4. **Access Granted:** Relay pin goes `LOW` → door unlocks for **5 seconds**, then re-locks.
5. **Access Denied:** LCD shows "Access Denied", relay stays `HIGH` (locked).
6. All errors (scan error, communication error, processing error) are handled gracefully with user-friendly LCD messages.

---
## 🔌 Circuit Connections

| Fingerprint Sensor | Arduino |
|---|---|
| VCC | 5V |
| GND | GND |
| TX | Pin 2 (SoftwareSerial RX) |
| RX | Pin 3 (SoftwareSerial TX) |

| LCD (I2C) | Arduino |
|---|---|
| VCC | 5V |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

| Relay Module | Arduino |
|---|---|
| IN | Pin 4 |
| VCC | 5V |
| GND | GND |

> **Note:** The relay is active-LOW. `digitalWrite(Relay, LOW)` unlocks; `HIGH` locks.

---

## 📦 Dependencies

Install the following libraries via Arduino Library Manager:

- [`Adafruit_Fingerprint`](https://github.com/adafruit/Adafruit-Fingerprint-Sensor-Library) — Fingerprint sensor communication
- [`LiquidCrystal_I2C`](https://github.com/johnrickman/LiquidCrystal_I2C) — I2C LCD control
- `Wire` — Built-in Arduino I2C library
- `SoftwareSerial` — Built-in Arduino serial library

---

## 🧠 Key Technical Concepts

- **SoftwareSerial at 57600 baud** — high-speed serial communication with the fingerprint sensor over digital pins, freeing the hardware UART for debugging.
- **Two-pass enrollment** — the sensor captures two images of the same finger, converts each to a Tz template, then merges them into a final model for higher accuracy matching.
- **Relay active-LOW logic** — the relay defaults to HIGH (locked) on power-up, ensuring a fail-secure state if power is lost mid-operation.
- **Non-blocking scan loop** — the main loop runs with a `delay(50)` throttle rather than full speed, balancing responsiveness with power efficiency.
- **Comprehensive error handling** — every sensor return code (`FINGERPRINT_OK`, `FINGERPRINT_NOFINGER`, `FINGERPRINT_PACKETRECIEVEERR`, `FINGERPRINT_NOTFOUND`, etc.) is explicitly handled with appropriate user feedback.

---





