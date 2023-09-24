#include "BluetoothSerial.h"
#include "Bind.hpp"
BluetoothSerial SerialBT;
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
  gauge1.x = 10;
  gauge1.y = 10;
  gauge1.dimSize = 200;
  gauge1.value = 0.0f;
  gauge1.maxValue = 200.0f;
  gauge1.drawArc = 100;
  gauge1.arcGreenMaxVal = 100.0f;
  gauge1.arcYellowMaxVal = 150.0f;
  gauge1.arcRedMaxVal = 180.0f;
  gauge1.setlabel("Speed mph");
  gauge1.cmdId = BIND_ADD_OR_REFRESH_CMD;
  bind.sync(&gauge1);
}

void updateGauge(float value) {
  gauge1.value = value;
  gauge1.cmdId = BIND_DATA_ONLY_CMD;
  bind.sync(&gauge1);
}

// Configure and add the second gauge (BindGaugeCompact)
void addGaugeCompact() {
  gauge2.x = 10;
  gauge2.y = 230;
  gauge2.dimSize = 200;
  gauge2.value = 0.0f;
  gauge2.maxValue = 200.0f;
  gauge2.drawArc = 100;
  gauge2.arcGreenMaxVal = 100.0f;
  gauge2.arcYellowMaxVal = 150.0f;
  gauge2.arcRedMaxVal = 180.0f;
  gauge2.setlabel("Speed Km/h");
  gauge2.cmdId = BIND_ADD_OR_REFRESH_CMD;
  bind.sync(&gauge2);
}

void updateGaugeCompact(float value) {
  gauge2.value = value;
  gauge2.cmdId = BIND_DATA_ONLY_CMD;
  bind.sync(&gauge2);
}

void addGaugeSimple() {
  gauge3.x = 10;
  gauge3.y = 360;
  gauge3.dimSize = 200;
  gauge3.value = 0.0f;
  gauge3.maxValue = 20;
  gauge3.minValue = -20;
  gauge3.style = 0;
  gauge3.isSymmetrical = true;
  gauge3.color = BLUE;
  gauge3.setlabel("Simple Gauge");
  gauge3.cmdId = BIND_ADD_OR_REFRESH_CMD;
  bind.sync(&gauge3);
}

void updateGaugeSimple(float value) {
  screenGaugeSimple.value = value;
  screenGaugeSimple.cmdId = DATA_ONLY_CMD;
  sendScreenStream(&screenGaugeSimple, &SerialBT);
}

void screenSetup(int16_t w, int16_t h) {
  Serial.println("Screen setup started!");
  addGauge(0.0f);
  addGaugeCompact(0.0f);
  addGaugeSimple(0.0f);
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  screenObjects.registerScreenSetup(&screenSetup);
  String devName = "ESP32testB";
  SerialBT.begin(devName);
  Serial.println("The bluetooth device started, now you can pair the phone with bluetooth!");
  Serial.println("devName:");
  Serial.println(devName);
}

void loop() {
  while (SerialBT.available()) {
    screenObjects.updateScreen(SerialBT.read());
  }
  delay(10);
  if (millis() -lastMs  > 100) {
    lastMs = millis();
    g1 += gDelta;
    speed += speedDelta;
    if (g1 >= 20.0f || g1 <= -20.0f) {
      gDelta = -1 * gDelta;
    }

    if (speed >= 200.0f || speed <= -0.0f) {
      speedDelta = -1 * speedDelta;
    }

    if (screenObjects.isReady()) {
      updateGauge(speed);
      updateGaugeCompact(speed);
      updateGaugeSimple(g1);
    }
  }
}
