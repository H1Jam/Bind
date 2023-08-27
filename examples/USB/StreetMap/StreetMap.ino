#include "Bind.hpp"

ScreenObjects screenObjects;
ScreenMap screenMap;
ScreenMapMarker screenMapMarker1;
ScreenMapMarker screenMapMarker2;

int counter = 0;
int wpIndex = 0;
bool isReady = false;
float oceanDrive[5][2] = {
  { 26.891425, -80.056879 },
  { 26.891173, -80.056838 },
  { 26.890885, -80.056776 },
  { 26.890652, -80.056711 },
  { 26.890472, -80.056670 }
};

void addMap() {
  screenMap.cmdId = ADD_OR_REFRESH_CMD;
  screenMap.x = 10;
  screenMap.y = 10;
  screenMap.width = 300;
  screenMap.height = 400;
  screenMap.lat = 26.891425f;
  screenMap.lon = -80.056879f;
  screenMap.mapOrientation = 0.0f;
  screenMap.zoom = 18;
  sendScreenStream(&screenMap, &Serial);
}


void setMapMarker() {
  screenMapMarker1.lat = oceanDrive[wpIndex][0];
  screenMapMarker1.lon = oceanDrive[wpIndex][1];
  screenMapMarker1.rotation = 167.0f;
  screenMapMarker1.iconId = MarkerIcons::CarRed;
  screenMapMarker2.scale = 70;
  screenMapMarker1.cmdId = ADD_OR_REFRESH_CMD;
  sendScreenStream(&screenMapMarker1, &Serial);

  screenMapMarker2.lat = oceanDrive[4 - wpIndex][0];
  screenMapMarker2.lon = oceanDrive[4 - wpIndex][1];
  screenMapMarker2.rotation = 345.0f;
  screenMapMarker2.iconId = MarkerIcons::CarGreen;
  screenMapMarker2.scale = 60;
  screenMapMarker2.cmdId = ADD_OR_REFRESH_CMD;
  sendScreenStream(&screenMapMarker2, &Serial);

  screenMap.lat = oceanDrive[wpIndex][0];
  screenMap.lon = oceanDrive[wpIndex][1];
  screenMap.mapOrientation = 0.0f;
  screenMap.zoom = MAP_USER_ZOOM;
  sendScreenStream(&screenMap, &Serial);
  wpIndex++;
  if (wpIndex > 4) {
    wpIndex = 0;
  }
}


void screenSetup(int16_t w, int16_t h) {
  addMap();
  isReady = true;
}

void setup() {
  Serial.begin(115200);
  Serial.println("Started!");
  screenObjects.registerScreenSetup(&screenSetup);
  String devName = "ESP32testB";
}

void loop() {
  while (Serial.available()) {
    screenObjects.updateScreen(Serial.read());
  }
  delay(100);
  if (isReady) {
    counter++;
    if (counter > 10) {
      counter = 0;
      setMapMarker();
    }
  }
}
