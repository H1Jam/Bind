#include <SoftwareSerial.h>
#include "Bind.hpp"
// Note: Adjust the pins to match your Bluetooth module's configuration.
#ifdef __AVR__
SoftwareSerial swSerial(4, 3);
#else
SoftwareSerial swSerial(D4, D3); // For boards like ESP8266, ESP32, or similar.
#endif
Bind bind;
BindGauge gauge1;
BindGaugeCompact gauge2;
BindGaugeSimple gauge3;

int counter = 0;
float g1 = 0.0f;
float speed = 0.0f;
float gDelta = 1.0f;
float speedDelta = 5.0f;
unsigned long lastMs = 0;

// Configure and add the first gauge (BindGauge)
void addGauge() {
  gauge1.x = 40;
  gauge1.y = 70;
  gauge1.dimSize = 200;
  gauge1.value = 0.0f;
  gauge1.maxValue = 200.0f;
  gauge1.drawArc = 100;
  gauge1.arcGreenMaxVal = 100.0f;
  gauge1.arcYellowMaxVal = 150.0f;
  gauge1.arcRedMaxVal = 180.0f;
  gauge1.setlabel("Speed mph");
  gauge1.cmdId = BIND_ADD_OR_REFRESH_CMD;
  bind.sync(gauge1);
}

void updateGauge(float value) {
  gauge1.value = value;
  gauge1.cmdId = BIND_DATA_ONLY_CMD;
  bind.sync(gauge1);
}

// Configure and add the second gauge (BindGaugeCompact)
void addGaugeCompact() {
  gauge2.x = 40;
  gauge2.y = 270;
  gauge2.dimSize = 200;
  gauge2.value = 0.0f;
  gauge2.maxValue = 200.0f;
  gauge2.drawArc = 100;
  gauge2.arcGreenMaxVal = 100.0f;
  gauge2.arcYellowMaxVal = 150.0f;
  gauge2.arcRedMaxVal = 180.0f;
  gauge2.setlabel("Speed Km/h");
  gauge2.cmdId = BIND_ADD_OR_REFRESH_CMD;
  bind.sync(gauge2);
}

void updateGaugeCompact(float value) {
  gauge2.value = value;
  gauge2.cmdId = BIND_DATA_ONLY_CMD;
  bind.sync(gauge2);
}

void addGaugeSimple() {
  gauge3.x = 40;
  gauge3.y = 370;
  gauge3.dimSize = 200;
  gauge3.value = 0.0f;
  gauge3.maxValue = 20;
  gauge3.minValue = -20;
  gauge3.style = 0;
  gauge3.isSymmetrical = true;
  gauge3.color = BLUE;
  gauge3.setlabel("Simple Gauge");
  gauge3.cmdId = BIND_ADD_OR_REFRESH_CMD;
  bind.sync(gauge3);
}

void updateGaugeSimple(float value) {
  gauge3.value = value;
  gauge3.cmdId = BIND_DATA_ONLY_CMD;
  bind.sync(gauge3);
}

void onConnection(int16_t width, int16_t height) {
  Serial.println("Screen setup started!");
  addGauge();
  addGaugeCompact();
  addGaugeSimple();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  // Note: Adjust the baud rate to match your Bluetooth module's configuration.
  swSerial.begin(57600);

  bind.init(swSerial, onConnection);

  Serial.println("The Bluetooth device started. Pair your phone with Bluetooth!");
  Serial.println("Device Name:");
}

void loop() {
  bind.sync();
  delay(5);

  // Sending some dummy data to the gauges:
  if (millis() - lastMs > 100) {
    lastMs = millis();

    g1 += gDelta;
    speed += speedDelta;

    if (g1 >= 20.0f || g1 <= -20.0f) {
      gDelta = -1 * gDelta;
    }

    if (speed >= 200.0f || speed <= -0.0f) {
      speedDelta = -1 * speedDelta;
    }

    if (bind.isReady()) {
      updateGauge(speed);
      updateGaugeCompact(speed);
      updateGaugeSimple(g1);
    }
  }
}
