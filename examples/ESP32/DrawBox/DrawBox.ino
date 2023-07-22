#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
ScreenObjects screenObjects;
ScreenRectangle screenRectangle1;
ScreenRectangle screenRectangle2;
ScreenRectangle screenRectangle3;

void addBoxes() {
  screenRectangle1.x = 10;
  screenRectangle1.y = 10;
  screenRectangle1.cmdId = ADD_OR_REFRESH_CMD;
  screenRectangle1.width = 150;
  screenRectangle1.height = 100;
  screenRectangle1.cornersRadius = 131;
  sendScreenStream(&screenRectangle1, &SerialBT);
  
  screenRectangle2.x = 160;
  screenRectangle2.y = 10;
  screenRectangle2.cmdId = ADD_OR_REFRESH_CMD;
  screenRectangle2.width = 150;
  screenRectangle2.height = 100;
  screenRectangle2.cornersRadius = 131;
  sendScreenStream(&screenRectangle2, &SerialBT);
  
}

void screenSetup()
{
  Serial.println("Screen setup started!");
  addBoxes();
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
}

