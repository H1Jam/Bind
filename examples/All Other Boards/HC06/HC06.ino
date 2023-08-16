#include <SoftwareSerial.h>
#include "Bind.hpp"

SoftwareSerial swSer(D4, D3);

ScreenObjects screenObjects;
ScreenGauge screenGauge;
ScreenGaugeSimple screenGaugeSimple;
ScreenGaugeCompact screenGaugeCompact;
int counter = 0;
float g1 = 0.0f;
float speed = 0.0f;
float gDelta = 1.0f;
float speedDelta = 5.0f;
unsigned long lastMs = 0;

void addGauge(float value) {
  screenGauge.x = 10;
  screenGauge.y = 10;
  screenGauge.dimSize = 200;
  screenGauge.value = value;
  screenGauge.maxValue = 200.0f;
  screenGauge.drawArc = 100;
  screenGauge.arcGreenMaxVal = 100.0f;
  screenGauge.arcYellowMaxVal = 150.0f;
  screenGauge.arcRedMaxVal = 180.0f;
  screenGauge.setlabel("Speed mph");
  screenGauge.cmdId = ADD_OR_REFRESH_CMD;
  sendScreenStream(&screenGauge, &swSer);
}

void updateGauge(float value) {
  screenGauge.value = value;
  screenGauge.cmdId = DATE_ONLY_CMD;
  sendScreenStream(&screenGauge, &swSer);
}

void addGaugeCompact(float value) {
  screenGaugeCompact.x = 10;
  screenGaugeCompact.y = 230;
  screenGaugeCompact.dimSize = 200;
  screenGaugeCompact.value = value;
  screenGaugeCompact.maxValue = 200.0f;
  screenGaugeCompact.drawArc = 100;
  screenGaugeCompact.arcGreenMaxVal = 100.0f;
  screenGaugeCompact.arcYellowMaxVal = 150.0f;
  screenGaugeCompact.arcRedMaxVal = 180.0f;
  screenGaugeCompact.setlabel("Speed Km/h");
  screenGaugeCompact.cmdId = ADD_OR_REFRESH_CMD;
  sendScreenStream(&screenGaugeCompact, &swSer);
}

void updateGaugeCompact(float value) {
  screenGaugeCompact.value = value;
  screenGaugeCompact.cmdId = DATE_ONLY_CMD;
  sendScreenStream(&screenGaugeCompact, &swSer);
}

void addGaugeSimple(float value) {
  screenGaugeSimple.x = 10;
  screenGaugeSimple.y = 360;
  screenGaugeSimple.dimSize = 200;
  screenGaugeSimple.value = value;
  screenGaugeSimple.maxValue = 20;
  screenGaugeSimple.minValue = -20;
  screenGaugeSimple.style = 0;
  screenGaugeSimple.isSymmetrical = true;
  screenGaugeSimple.color = BLUE;
  screenGaugeSimple.setlabel("Simple Gauge");
  screenGaugeSimple.cmdId = ADD_OR_REFRESH_CMD;
  sendScreenStream(&screenGaugeSimple, &swSer);
}

void updateGaugeSimple(float value) {
  screenGaugeSimple.value = value;
  screenGaugeSimple.cmdId = DATE_ONLY_CMD;
  sendScreenStream(&screenGaugeSimple, &swSer);
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
  //SerialBT.begin(devName);
  swSer.begin(115200);
  Serial.println("The bluetooth device started, now you can pair the phone with bluetooth!");
  Serial.println("devName:");
  Serial.println(devName);
}

void loop() {
  while (swSer.available()) {
    screenObjects.updateScreen(swSer.read());
  }
  delay(10);
  if (millis() -lastMs  > 250) {
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
