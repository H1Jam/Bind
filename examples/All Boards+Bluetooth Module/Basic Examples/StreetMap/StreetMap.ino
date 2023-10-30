//We only use SoftwareSerial for AVR Arduinos or ESP8266 library.
#if defined(__AVR__) || defined(ESP8266)
#include <SoftwareSerial.h>
#endif

#include "Bind.hpp"

// Note: Adjust the pins to match your Bluetooth module's configuration.
// We may use SoftwareSerial for AVR Arduinos or ESP8266.
#ifdef __AVR__
SoftwareSerial btSerial(4, 3); // For AVR Arduinos like Pro Mini or Mega: RX: pin 4, TX: pin 3
#elif defined(ESP8266)
SoftwareSerial btSerial(D1, D2); // For ESP8266: RX: pin D1, TX: pin D2
#elif defined(ESP32) 
#define btSerial Serial2 // For ESP32 we use Serial2.
#elif defined(ARDUINO_ARCH_RP2040)
#define btSerial Serial1 // For RP2040(Raspberry Pi Pico): Use serial1 RX: pin 2, TX: pin 3
#else
SoftwareSerial btSerial(4, 3); // Modify this line, if your board is neither above.
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
  bind.sync(bindMap);
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
  bind.sync(mapMarker1);

  mapMarker2.lat = oceanDrive[4 - wpIndex][0];
  mapMarker2.lon = oceanDrive[4 - wpIndex][1];
  mapMarker2.rotation = 345.0f;
  mapMarker2.iconId = MARKER_CAR_GREEN;
  mapMarker2.scale = 60;
  mapMarker2.cmdId = BIND_ADD_OR_REFRESH_CMD;
  bind.sync(mapMarker2);

  bindMap.lat = oceanDrive[wpIndex][0];
  bindMap.lon = oceanDrive[wpIndex][1];
  bindMap.mapOrientation = 0.0f;
  bindMap.zoom = 18;  // or BIND_MAP_USER_ZOOM to let the user control the zoom level.
  bindMap.cmdId = BIND_ADD_OR_REFRESH_CMD;
  bind.sync(bindMap);
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
  btSerial.begin(57600);

  /// Initialize the Bind object and specify the communication method (btSerial) and callback function (onConnection).
  bind.init(btSerial, onConnection);
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
