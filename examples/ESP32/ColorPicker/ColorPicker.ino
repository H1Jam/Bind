#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
ScreenObjects screenObjects;
ScreenColorPicker screenColorPicker1;
const int ledPin = 2;

void screenColorPicker1Changed(uint8_t red, uint8_t green, uint8_t blue)
{
  Serial.print("ColorPicker has been changed:");
  Serial.print(red);Serial.print("\t"); Serial.print(green);Serial.print("\t"); Serial.println(blue);
}

void addColorPicker() {
  screenColorPicker1.x = 200;
  screenColorPicker1.y = 300;
  screenColorPicker1.cmdId = ADD_OR_REFRESH_CMD;
  screenColorPicker1.dimSize = 150;
  screenColorPicker1.red = 160;
  screenColorPicker1.green = 190;
  screenColorPicker1.blue = 220;
  sendScreenStream(&screenColorPicker1, &SerialBT);
}

void screenSetup()
{
  Serial.println("Screen setup started!");
  addColorPicker();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  screenObjects.registerScreenSetup(&screenSetup);
  screenObjects.registerColorPicker(&screenColorPicker1, &screenColorPicker1Changed);
  String devName = "ESP32testB";
  SerialBT.begin(devName);
  Serial.println("The bluetooth device started, now you can pair the phone with bluetooth!");
  Serial.println("devName:");
  Serial.println(devName);
}

void loop() {
  while (SerialBT.available()) {
  screenObjects.updateScreen(SerialBT.read());
  delay(1);
  }
}
