#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
ScreenObjects screenObjects;
ScreenJoystick joystickRight;
ScreenJoystick joystickLeft;
ScreenGaugeCompact screenGaugeCompact;
ScreenSettings screenSettings;

void screenConfig() {
  screenSettings.screenOrientation = SCREEN_ORIENTATION_LANDSCAPE;
  screenSettings.backColor = RGB(31, 39, 42);
  screenSettings.actionBarColor = RGB(23, 30, 33);;
  screenSettings.setlabel("RC Controller");
  sendScreenStream(&screenSettings, &SerialBT);
}

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
  addGaugeCompact(y+100);
}

void addJoystickRight() {
  joystickRight.x = 400;
  joystickRight.y = 70;
  joystickRight.cmdId = ADD_OR_REFRESH_CMD;
  joystickRight.dimSize = 200;
  sendScreenStream(&joystickRight, &SerialBT);
}

void addJoystickLeft() {
  joystickLeft.x = 50;
  joystickLeft.y = 70;
  joystickLeft.cmdId = ADD_OR_REFRESH_CMD;
  joystickLeft.dimSize = 200;
  sendScreenStream(&joystickLeft, &SerialBT);
}

void addGaugeCompact(float value) {
  screenGaugeCompact.x = 225;
  screenGaugeCompact.y = 50;
  screenGaugeCompact.dimSize = 200;
  screenGaugeCompact.value = value;
  screenGaugeCompact.maxValue = 200.0f;
  screenGaugeCompact.drawArc = 100;
  screenGaugeCompact.arcGreenMaxVal = 100.0f;
  screenGaugeCompact.arcYellowMaxVal = 150.0f;
  screenGaugeCompact.arcRedMaxVal = 180.0f;
  screenGaugeCompact.setlabel("Speed Km/h");
  screenGaugeCompact.cmdId = ADD_OR_REFRESH_CMD;
  sendScreenStream(&screenGaugeCompact, &SerialBT);
}

void screenSetup()
{
  Serial.println("Screen setup started!");
  screenConfig();
  addJoystickLeft();
  addJoystickRight();
  addGaugeCompact(0);
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

