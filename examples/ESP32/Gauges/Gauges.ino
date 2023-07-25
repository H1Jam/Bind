#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
ScreenObjects screenObjects;
ScreenGauge screenGauge;
ScreenGaugeSimple screenGaugeSimple;
ScreenGaugeCompact screenGaugeCompact;
int counter = 0;
float g1 = 0.0f;
float speed = 0.0f;
float gDelta = 1.0f;
float speedDelta = 5.0f;

void addGauge(float value) {
  screenGauge.x = 120;
  screenGauge.y = 500;
  screenGauge.dimSize = 120;
  screenGauge.value = value;
  screenGauge.maxValue = 200.0f;
  screenGauge.drawArc = 100;
  screenGauge.arcGreenMaxVal = 100.0f;
  screenGauge.arcYellowMaxVal = 150.0f;
  screenGauge.arcRedMaxVal = 180.0f;
  screenGauge.setlabel("Speed mph");
  screenGauge.cmdId = ADD_OR_REFRESH_CMD;
  sendScreenStream(&screenGauge, &SerialBT);
}

void updateGauge(float value) {
  screenGauge.value = value;
  screenGauge.cmdId = ADD_OR_REFRESH_CMD;
  sendScreenStream(&screenGauge, &SerialBT);
}

void addGaugeCompact(float value) {
  screenGaugeCompact.x = 20;
  screenGaugeCompact.y = 270;
  screenGaugeCompact.dimSize = 120;
  screenGaugeCompact.value = value;
  screenGaugeCompact.maxValue = 200.0f;
  screenGaugeCompact.drawArc = 100;
  screenGaugeCompact.arcGreenMaxVal = 100.0f;
  screenGaugeCompact.arcYellowMaxVal = 150.0f;
  screenGaugeCompact.arcRedMaxVal = 180.0f;
  screenGaugeCompact.setlabel("Speed Km/h");
  screenGaugeCompact.cmdId = ADD_OR_REFRESH_CMD;
  sendScreenStream(&screenGaugeCompact, &SerialBT);
}

void updateGaugeCompact(float value) {
  screenGaugeCompact.value = value;
  screenGaugeCompact.cmdId = ADD_OR_REFRESH_CMD;
  sendScreenStream(&screenGaugeCompact, &SerialBT);
}

void addGaugeSimple(float value) {
  screenGaugeSimple.x = 129;
  screenGaugeSimple.y = 150;
  screenGaugeSimple.dimSize = 153;
  screenGaugeSimple.value = value;
  screenGaugeSimple.maxValue = 20;
  screenGaugeSimple.minValue = -20;
  screenGaugeSimple.style = 0;
  screenGaugeSimple.isSymmetrical = true;
  screenGaugeSimple.color = BLUE;
  screenGaugeSimple.setlabel("Simple Gauge");
  screenGaugeSimple.cmdId = ADD_OR_REFRESH_CMD;
  sendScreenStream(&screenGaugeSimple, &SerialBT);
}

void updateGaugeSimple(float value) {
  screenGaugeSimple.value = value;
  screenGaugeSimple.cmdId = ADD_OR_REFRESH_CMD;
  sendScreenStream(&screenGaugeSimple, &SerialBT);
}

void screenSetup() {
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
  counter++;
  if (counter > 20) {
    counter = 0;
    g1 += gDelta;
    speed += speedDelta;
    if (g1 > 20.0f || g1 < -20.0f) {
      gDelta = -1 * gDelta;
    }

    if (speed > 200.0f || speed < -0.0f) {
      speedDelta = -1 * speedDelta;
    }

    if (screenObjects.isReady()) {
      updateGauge(speed);
      updateGaugeCompact(speed);
      updateGaugeSimple(g1);
    }
  }
}
