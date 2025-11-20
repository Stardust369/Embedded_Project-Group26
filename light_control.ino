#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11); // HC-05: TX=10, RX=11

const int relayPin = 7;
const bool relayActiveLow = true;

bool blinking = false;
unsigned long prevMillis = 0;
int blinkState = 0;

void relayOn() {
  if (relayActiveLow) digitalWrite(relayPin, LOW);
  else digitalWrite(relayPin, HIGH);
}

void relayOff() {
  if (relayActiveLow) digitalWrite(relayPin, HIGH);
  else digitalWrite(relayPin, LOW);
}

void setup() {
  pinMode(relayPin, OUTPUT);

  BT.begin(9600);
  Serial.begin(9600);

  relayOff();
}

void loop() {
  // ---------------------------
  //   READ BLUETOOTH COMMANDS
  // ---------------------------
  if (BT.available()) {
    String cmd = BT.readStringUntil('\n');
    cmd.trim();
    cmd.toUpperCase();

    Serial.println("Received: " + cmd);

    if (cmd == "ON") {
      blinking = false;
      relayOn();
    }
    else if (cmd == "OFF") {
      blinking = false;
      relayOff();
    }
    else if (cmd == "BLINK") {
      blinking = true;
      prevMillis = millis(); // reset timer
    }
  }

  // ---------------------------
  //      NON-BLOCKING BLINK
  // ---------------------------
  if (blinking) {
    unsigned long now = millis();

    if (now - prevMillis >= 300) {  // blink every 300 ms
      prevMillis = now;

      if (blinkState == 0) {
        relayOn();
        blinkState = 1;
      } else {
        relayOff();
        blinkState = 0;
      }
    }
  }
}
