#include <SoftwareSerial.h>
#include "Bind.hpp"

// Note: Adjust the pins to match your Bluetooth module's configuration.
#ifdef __AVR__
SoftwareSerial swSerial(4, 3);
#else
SoftwareSerial swSerial(D4, D3); // For boards like ESP8266, ESP32, or similar.
#endif
ScreenObjects screenObjects;
ScreenTerminal screenTerminal;

int counter = 0;
int counter2 = 0;
char buffer[15];

void addScreenTerminal() {
  screenTerminal.x = 10;
  screenTerminal.y = 10;
  screenTerminal.cmdId = ADD_OR_REFRESH_CMD;
  screenTerminal.width = 300;
  screenTerminal.height = 200;
  screenTerminal.textSize = 10;
  screenTerminal.backColor = UBUNTU;
  sendScreenStream(&screenTerminal, &swSerial);
}

void updateScreenTerminalData(const char *cstr) {
  ScreenTerminalPrint(cstr, GREEN, true, true, true, false, &screenTerminal, &swSerial);
}

void updateScreenTerminalDataBigger(const char *cstr) {
  ScreenTerminalPrint(cstr, WHITE, true, true, true, false, &screenTerminal, &swSerial);
}

void screenSetup() {
  Serial.println("Screen setup started!");
  addScreenTerminal();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  screenObjects.registerScreenSetup(&screenSetup);
  // Note: Adjust the baud rate to match your Bluetooth module's configuration.
  swSerial.begin(57600);
}

void loop() {
  while (swSerial.available()) {
    screenObjects.updateScreen(swSerial.read());
  }
  delay(10);
  counter++;
  if (counter > 100) {
    counter = 0;
    snprintf(buffer, 15, "Time: %d", millis());
    updateScreenTerminalData(buffer);
    counter2++;
    if (counter2 >= 5) {
      updateScreenTerminalDataBigger("Print with diffrent color!");
      counter2 = 0;
    }
  }
}
