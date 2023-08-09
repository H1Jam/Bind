#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
ScreenObjects screenObjects;
ScreenJoystick joystickRight;
ScreenJoystick joystickLeft;

void joystickRight_Callback(int16_t x, int16_t y)
{
  Serial.print("joystickRight has been changed, x:");
  Serial.print(x);
  Serial.print(" y:");
  Serial.println(y);
}

void joystickLeft_Callback(int16_t x, int16_t y)
{
  Serial.print("joystickLeft has been changed, x:");
  Serial.print(x);
  Serial.print(" y:");
  Serial.println(y);
}

void addJoystickRight() {
  joystickRight.x = 50;
  joystickRight.y = 80;
  joystickRight.cmdId = ADD_OR_REFRESH_CMD;
  joystickRight.dimSize = 200;
  sendScreenStream(&joystickRight, &SerialBT);
}

void addJoystickLeft() {
  joystickLeft.x = 50;
  joystickLeft.y = 80;
  joystickLeft.cmdId = ADD_OR_REFRESH_CMD;
  joystickLeft.dimSize = 200;
  sendScreenStream(&joystickLeft, &SerialBT);
}

void screenSetup()
{
  Serial.println("Screen setup started!");
  addJoystick1();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  screenObjects.registerScreenSetup(&screenSetup);
  screenObjects.registerJoystick(&joystickRight, &joystickRight_Callback);
  screenObjects.registerJoystick(&joystickLeft, &joystickLeft_Callback);
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
