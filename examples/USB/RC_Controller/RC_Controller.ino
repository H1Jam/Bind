#include "Bind.hpp"

ScreenObjects screenObjects;
ScreenJoystick joystickRight;
ScreenJoystick joystickLeft;
ScreenGaugeCompact screenGaugeCompact;
ScreenAttitudeIndicator screenAttitudeIndicator;
ScreenHeadingIndicator screenHeadingIndicator;
ScreenSettings screenSettings;

int counter = 0;
float g1 = 0.0f;
float speed = 0.0f;
float gDelta = 1.0f;
float speedDelta = 5.0f;
unsigned long lastMs = 0;

void screenConfig() {
  screenSettings.screenOrientation = SCREEN_ORIENTATION_LANDSCAPE;
  screenSettings.backColor = RGB(41, 49, 52);
  screenSettings.setlabel("RC Controller");
  sendScreenStream(&screenSettings, &Serial);
}


void joystickRight_Callback(int16_t x, int16_t y)
{
  setAttitudeIndicator(x*0.45f, y*0.2f);
}

void joystickLeft_Callback(int16_t x, int16_t y)
{
  addGaugeCompact(y+100);
  setHeadingIndicator(x);
}

void addJoystickRight() {
  joystickRight.x = 400;
  joystickRight.y = 70;
  joystickRight.cmdId = ADD_OR_REFRESH_CMD;
  joystickRight.dimSize = 200;
  sendScreenStream(&joystickRight, &Serial);
}

void addJoystickLeft() {
  joystickLeft.x = 50;
  joystickLeft.y = 70;
  joystickLeft.cmdId = ADD_OR_REFRESH_CMD;
  joystickLeft.dimSize = 200;
  sendScreenStream(&joystickLeft, &Serial);
}

void addGaugeCompact(float value) {
  screenGaugeCompact.x = 225;
  screenGaugeCompact.y = 20;
  screenGaugeCompact.dimSize = 200;
  screenGaugeCompact.value = value;
  screenGaugeCompact.maxValue = 200.0f;
  screenGaugeCompact.drawArc = 100;
  screenGaugeCompact.arcGreenMaxVal = 100.0f;
  screenGaugeCompact.arcYellowMaxVal = 150.0f;
  screenGaugeCompact.arcRedMaxVal = 180.0f;
  screenGaugeCompact.setlabel("Speed Km/h");
  screenGaugeCompact.cmdId = ADD_OR_REFRESH_CMD;
  sendScreenStream(&screenGaugeCompact, &Serial);
}

void setAttitudeIndicator(float roll, float pitch) {
  screenAttitudeIndicator.x = 420;
  screenAttitudeIndicator.y = 5;
  screenAttitudeIndicator.cmdId = ADD_OR_REFRESH_CMD;
  screenAttitudeIndicator.roll = roll;
  screenAttitudeIndicator.pitch = pitch;
  screenAttitudeIndicator.dimSize = 80;
  sendScreenStream(&screenAttitudeIndicator, &Serial);
}

void setHeadingIndicator(float heading) {
  screenHeadingIndicator.x = 150;
  screenHeadingIndicator.y = 5;
  screenHeadingIndicator.cmdId = ADD_OR_REFRESH_CMD;
  screenHeadingIndicator.heading = heading;
  screenHeadingIndicator.dimSize = 80;
  sendScreenStream(&screenHeadingIndicator, &Serial);
}

void screenSetup(int16_t w, int16_t h) {
  screenConfig();
  addGaugeCompact(0);
  addJoystickLeft();
  addJoystickRight();
  setAttitudeIndicator(0.0f, 0.0f);
  setHeadingIndicator(0.0f);
}

void setup() {
  Serial.begin(115200);
  screenObjects.registerScreenSetup(&screenSetup);
  screenObjects.registerJoystick(&joystickRight, &joystickRight_Callback);
  screenObjects.registerJoystick(&joystickLeft, &joystickLeft_Callback);
  //String devName = "ESP32testB";
  //SerialBT.begin(devName);
  //SerialBT.begin(115200);
}

void loop() {
  while (Serial.available()) {
    screenObjects.updateScreen(Serial.read());
  }
  delay(2);
}
