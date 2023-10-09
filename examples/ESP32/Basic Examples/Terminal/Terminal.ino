#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
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
  sendScreenStream(screenTerminal, SerialBT);
}

void updateScreenTerminalData(const char *cstr) {
  ScreenTerminalPrint(cstr, GREEN, true, true, true, false, screenTerminal, SerialBT);
}

void updateScreenTerminalDataBigger(const char *cstr) {
  ScreenTerminalPrint(cstr, WHITE, true, true, true, false, screenTerminal, SerialBT);
}

void screenSetup() {
  Serial.println("Screen setup started!");
  addScreenTerminal();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  screenObjects.registerScreenSetup(screenSetup);
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
