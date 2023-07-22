#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
ScreenObjects screenObjects;
ScreenJoystick joystick1;

void joystick1_Callback(int16_t x, int16_t y)
{
  Serial.print("joystick1 has been changed, x:");
  Serial.print(x);
  Serial.print(" y:");
  Serial.println(y);
}

void addJoystick() {
  joystick1.x = 50;
  joystick1.y = 80;
  joystick1.cmdId = ADD_OR_REFRESH_CMD;
  joystick1.dimSize = 200;
  sendScreenStream(&joystick1, &SerialBT);
}

void screenSetup()
{
  Serial.println("Screen setup started!");
  addJoystick();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  screenObjects.registerScreenSetup(&screenSetup);
  screenObjects.registerJoystick(&joystick1, &joystick1_Callback);
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
  delay(2);
}

