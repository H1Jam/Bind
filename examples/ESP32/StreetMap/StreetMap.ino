#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
ScreenObjects screenObjects;
ScreenMap screenMap;
ScreenMapMarker screenMapMarker1;
ScreenMapMarker screenMapMarker2;

int counter = 0;
float dummyData = 0.0f;

void sendDummyChartdata() {
  dummyData = random(-30, 30);
  addChartdata(dummyData, &screenChart, &SerialBT);
}

void addMap()
{
  screenMap.cmdId = ADD_OR_REFRESH_CMD;
  screenMap.x = 10;
  screenMap.y = 10;
  screenMap.width = 300;
  screenMap.height = 200;
  screenMap.lat = 43.730825f;
  screenMap.lon = -79.440881f;
  screenMap.mapOrientation = 0.0f;
  screenMap.zoom = 16;
  sendScreenStream(&screenMap, &SerialBT);
}


void addMapMarker()
{
  screenMapMarker1.lat = 26.891425f;
  screenMapMarker1.lon = -80.056879f;
  screenMapMarker1.rotation = 167.0f;
  screenMapMarker1.iconId = MarkerIcons.CarRed;
  screenMapMarker1.cmdId = ADD_OR_REFRESH_CMD;
  sendScreenStream(&screenMapMarker1, &SerialBT);
  screenMapMarker2.lat = 26.890472f;
  screenMapMarker2.lon = -80.056670f;
  screenMapMarker2.rotation = 345.0f;
  screenMapMarker2.iconId = MarkerIcons.CarGreen;;
  screenMapMarker2.cmdId = ADD_OR_REFRESH_CMD;
  sendScreenStream(&screenMapMarker2, &SerialBT);
}


void screenSetup() {
  Serial.println("Screen setup started!");
  addMap();
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
  delay(100);
  counter++;
  if (counter > 50) {
    counter = 0;
    addMapMarker
  }
}
