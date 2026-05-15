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

