#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
ScreenObjects screenObjects;
ScreenAttitudeIndicator screenAttitudeIndicator;
ScreenHeadingIndicator screenHeadingIndicator;
int counter = 0;
float rollC = 0;
float pitchC = 0;
float headingC = 0;

void setAttitudeIndicator(float roll, float pitch) {
  screenAttitudeIndicator.x = 10;
  screenAttitudeIndicator.y = 10;
  screenAttitudeIndicator.cmdId = ADD_OR_REFRESH_CMD;
  screenAttitudeIndicator.roll = roll;
  screenAttitudeIndicator.pitch = pitch;
  screenAttitudeIndicator.dimSize = 150;
  sendScreenStream(&screenAttitudeIndicator, &SerialBT);
}

void setHeadingIndicator(float heading) {
  screenHeadingIndicator.x = 190;
  screenHeadingIndicator.y = 10;
  screenHeadingIndicator.cmdId = ADD_OR_REFRESH_CMD;
  screenHeadingIndicator.heading = heading;
  screenHeadingIndicator.dimSize = 150;
  sendScreenStream(&screenHeadingIndicator, &SerialBT);
}

void screenSetup() {
  Serial.println("Screen setup started!");
  setAttitudeIndicator(0.0f, 0.0f);
  setHeadingIndicator(0.0f);
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
  if (counter > 20) {
    counter = 0;
    rollC++;
    pitchC++;
    headingC += 5;
    if (rollC > 45) {
      rollC = -45.0f;
    }

    if (pitchC > 45) {
      pitchC = -45.0f;
    }

    if (headingC > 360) {
      headingC = 0.0f;
    }
    setAttitudeIndicator(rollC, pitchC);
    setHeadingIndicator(headingC);
  }
}
