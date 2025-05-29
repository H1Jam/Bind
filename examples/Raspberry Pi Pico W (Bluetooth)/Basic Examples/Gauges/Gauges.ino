// Atention: For Raspberry Pi Pico W, this library needs Bluetooth enabled.
// Go to 'Tools->IP/Bluetooth Stack' menu in the IDE and select 'x + Bluetooth'.
#include "Bind.h"
#include <SerialBT.h>
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
  gauge1.setLabel("Speed mph");
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
  gauge2.setLabel("Speed Km/h");
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
  gauge3.setLabel("Simple Gauge");
  gauge3.cmdId = BIND_ADD_OR_REFRESH_CMD;
  bind.sync(gauge3);
}

void updateGaugeSimple(float value) {
  gauge3.value = value;
  gauge3.cmdId = BIND_DATA_ONLY_CMD;
  bind.sync(gauge3);
}

void onConnection(int16_t width, int16_t height) {
  addGauge();
  addGaugeCompact();
  addGaugeSimple();
}

void setup() {
  Serial.begin(115200);

  SerialBT.begin();
	bind.init(SerialBT, onConnection);
}

void loop() {
  // Synchronize Bind UI Events (Not required on ESP32 when using BindOverBLE or BindOverWifi)
  // Callin bind.sync() regularly is crucial to handle of user inputs and touch events.
  // It's recommended to call bind.sync() a couple of times per second, but the faster, the better!
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
