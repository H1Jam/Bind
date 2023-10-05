#include <SoftwareSerial.h>
#include "Bind.hpp"

// Note: Adjust the pins to match your Bluetooth module's configuration.
#ifdef __AVR__
SoftwareSerial swSerial(4, 3);
#else
SoftwareSerial swSerial(D4, D3); // For boards like ESP8266, ESP32, or similar.
#endif
Bind bind;
BindMap bindMap;
BindMapMarker mapMarker1;
BindMapMarker mapMarker2;

int counter = 0;
int wpIndex = 0;
//dummy locations:
float oceanDrive[5][2] = {
  { 26.891425, -80.056879 },
  { 26.891173, -80.056838 },
  { 26.890885, -80.056776 },
  { 26.890652, -80.056711 },
  { 26.890472, -80.056670 }
};

// Add the map on screen (You can only have one map on the screen for now.)
void addMap() {
  bindMap.x = 10;
  bindMap.y = 70;
  bindMap.width = 300;
  bindMap.height = 400;
  bindMap.lat = 26.891425f;
  bindMap.lon = -80.056879f;
  bindMap.mapOrientation = 0.0f;
  bindMap.zoom = 18;
  bindMap.cmdId = BIND_ADD_OR_REFRESH_CMD;
  bind.sync(&bindMap);
}

// Move some dummy markers:
void moveMapAndMarkers() {
  mapMarker1.lat = oceanDrive[wpIndex][0];
  mapMarker1.lon = oceanDrive[wpIndex][1];
  mapMarker1.rotation = 167.0f;
  /* all the possible values for iconId: 
    MARKER_PIN_RED
    MARKER_PIN_GREEN
    MARKER_PIN_BLUE
    MARKER_PIN_YELLOW
    MARKER_CAR_RED
    MARKER_CAR_GREEN
    MARKER_CAR_BLUE
    MARKER_CAR_YELLOW
    MARKER_PLANE_RED 8
    MARKER_PLANE_GREEN
    MARKER_PLANE_BLUE
    MARKER_PLANE_YELLOW 
  */
  mapMarker1.iconId = MARKER_CAR_RED; 
  mapMarker1.scale = 70;
  mapMarker1.cmdId = BIND_ADD_OR_REFRESH_CMD;
  bind.sync(&mapMarker1);

  mapMarker2.lat = oceanDrive[4 - wpIndex][0];
  mapMarker2.lon = oceanDrive[4 - wpIndex][1];
  mapMarker2.rotation = 345.0f;
  mapMarker2.iconId = MARKER_CAR_GREEN;
  mapMarker2.scale = 60;
  mapMarker2.cmdId = BIND_ADD_OR_REFRESH_CMD;
  bind.sync(&mapMarker2);

  bindMap.lat = oceanDrive[wpIndex][0];
  bindMap.lon = oceanDrive[wpIndex][1];
  bindMap.mapOrientation = 0.0f;
  bindMap.zoom = 18;  // or BIND_MAP_USER_ZOOM to let the user control the zoom level.
  bindMap.cmdId = BIND_ADD_OR_REFRESH_CMD;
  bind.sync(&bindMap);
  wpIndex++;
  if (wpIndex > 4) {
    wpIndex = 0;
  }
}

void onConnection(int16_t width, int16_t height) {
  Serial.println("Screen setup started!");
  addMap();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  // Note: Adjust the baud rate to match your Bluetooth module's configuration.
  swSerial.begin(57600);

  /// Initialize the Bind object and specify the communication method (swSerial) and callback function (onConnection).
  bind.init(&swSerial, &onConnection);
  /// Note: It was swSerial here, but it could be any serial port, including hardware and software serial.

}

void loop() {
  bind.sync();
  delay(100);
  counter++;
  if (counter > 10) {
    counter = 0;
    moveMapAndMarkers();
  }
}
