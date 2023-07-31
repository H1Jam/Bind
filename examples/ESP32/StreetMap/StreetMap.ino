#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
ScreenObjects screenObjects;
ScreenMap screenMap;
ScreenMapMarker screenMapMarker1;
ScreenMapMarker screenMapMarker2;

int counter = 0;
int wpIndex = 0;
float oceanDrive[5][2] = {{26.891425, -80.056879},{26.891173, -80.056838},{26.890885, -80.056776},{26.890652, -80.056711},{26.890472, -80.056670}};

void addMap()
{
  screenMap.cmdId = ADD_OR_REFRESH_CMD;
  screenMap.x = 10;
  screenMap.y = 10;
  screenMap.width = 300;
  screenMap.height = 200;
  screenMap.lat = 26.891425f;
  screenMap.lon = -80.056879f;
  screenMap.mapOrientation = 0.0f;
  screenMap.zoom = 18;
  sendScreenStream(&screenMap, &SerialBT);
}


void setMapMarker()
{
  screenMapMarker1.lat = oceanDrive[wpIndex][0];
  screenMapMarker1.lon = oceanDrive[wpIndex][1];
  screenMapMarker1.rotation = 167.0f;
  screenMapMarker1.iconId = MarkerIcons::CarRed;
  screenMapMarker1.cmdId = ADD_OR_REFRESH_CMD;
  sendScreenStream(&screenMapMarker1, &SerialBT);

  screenMapMarker2.lat = oceanDrive[4-wpIndex][0];
  screenMapMarker2.lon = oceanDrive[4-wpIndex][1];
  screenMapMarker2.rotation = 345.0f;
  screenMapMarker2.iconId = MarkerIcons::CarGreen;
  screenMapMarker2.cmdId = ADD_OR_REFRESH_CMD;
  sendScreenStream(&screenMapMarker2, &SerialBT);

  screenMap.lat = oceanDrive[wpIndex][0];
  screenMap.lon = oceanDrive[wpIndex][1];
  screenMap.mapOrientation = 0.0f;
  screenMap.zoom = 18;
  sendScreenStream(&screenMap, &SerialBT);
  wpIndex++;
  if (wpIndex>4){
    wpIndex=0;
  }
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
  if (counter > 10) {
    counter = 0;
    setMapMarker();
  }
}
