#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
ScreenObjects screenObjects;
ScreenTerminal screenTerminal;

int counter = 0;
char buffer[10];

void addScreenTerminal() {
  screenTerminal.x = 10;
  screenTerminal.y = 100;
  screenTerminal.cmdId = ADD_OR_REFRESH_CMD;
  screenTerminal.width = 200;
  screenTerminal.height = 200;
  screenTerminal.textSize = 8;
  //screenTerminal.backColor = BLACK;
  sendScreenStream(&screenTerminal, &SerialBT);
}

void updateScreenTerminalData(const char *cstr) {
  ScreenTerminalPrint(cstr, GREEN, true, true, true, false, &screenTerminal, &SerialBT);
}

void screenSetup()
{
  Serial.println("Screen setup started!");
  addScreenTerminal();
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
  if(counter>100){
    counter=0;
    snprintf(buffer, 10, "%d", millis());
    textLabel2.setlabel(buffer);
    textLabel2.cmdId = ADD_OR_REFRESH_CMD;
    sendScreenStream(&textLabel2, &SerialBT);
  }
}

