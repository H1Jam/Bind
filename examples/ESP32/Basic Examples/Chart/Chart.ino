#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
ScreenObjects screenObjects;
ScreenChart screenChart;

int counter = 0;
float dummyData = 0.0f;

void sendDummyChartdata() {
  dummyData = random(-30, 30);
  addChartdata(dummyData, &screenChart, &SerialBT);
}

void addChart() {
  screenChart.x = 10;
  screenChart.y = 10;
  screenChart.cmdId = ADD_OR_REFRESH_CMD;
  screenChart.width = 250;
  screenChart.height = 140;
  screenChart.maxY = 10;
  screenChart.minY = -10;
  screenChart.maxX = 20;
  screenChart.autoSize = true;
  screenChart.color = YELLOW;
  sendScreenStream(&screenChart, &SerialBT);
}

void screenSetup(int16_t w, int16_t h) {
  Serial.println("Screen setup started!");
  Serial.print(w);
  Serial.print(" ");
  Serial.println(h);
  addChart();
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
  if (counter > 50) {
    counter = 0;
    sendDummyChartdata();
  }
}
