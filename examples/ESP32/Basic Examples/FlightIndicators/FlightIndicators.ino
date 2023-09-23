#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
Bind bind;
BindAttitudeIndicator attitudeIndicator;

ScreenAttitudeIndicator screenAttitudeIndicator;
ScreenHeadingIndicator screenHeadingIndicator;


int counter = 0;
float rollC = 0;
float pitchC = 0;

float rollDelta = 2;
float pitchDelta = 1;

float headingC = 0;

void onConnection(int16_t w, int16_t h) {
  Serial.println("Screen setup started!");
  addAttitudeIndicator();
  Serial.println("Screen setup done!");
}

void addAttitudeIndicator() {
  attitudeIndicator.x = 30;
  attitudeIndicator.y = 70;
  attitudeIndicator.cmdId = BIND_ADD_OR_REFRESH_CMD;
  attitudeIndicator.dimSize = 200;

  // Specify the initial roll and pitch values.
  attitudeIndicator.roll = 0.0f;
  attitudeIndicator.pitch = 0.0f;

  // Synchronize the attitudeIndicator object with BindCanvas.
  bind.sync(&attitudeIndicator);
}
void setAttitudeIndicator(float roll, float pitch) {
  screenAttitudeIndicator.cmdId = BIND_DATA_ONLY_CMD;
  screenAttitudeIndicator.roll = roll;
  screenAttitudeIndicator.pitch = pitch;
  screenAttitudeIndicator.dimSize = 150;
  sendScreenStream(&screenAttitudeIndicator, &SerialBT);
}

void addHeadingIndicator() {
  headingIndicator.x = 30;
  headingIndicator.y = 70;
  headingIndicator.cmdId = BIND_ADD_OR_REFRESH_CMD;
  headingIndicator.dimSize = 200;

  // Specify the initial heading value.
  headingIndicator.heading = 0.0f;

  // Synchronize the headingIndicator object with BindCanvas.
  bind.sync(&headingIndicator);
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
  bind.sync();
  delay(10);
  counter++;
  if (counter > 20) {
    counter = 0;
    rollC += rollDelta;
    pitchC += pitchDelta;
    headingC += 5;

    if (rollC > 20 || rollC < -20) {
      rollDelta = -1 * rollDelta;
    }

    if (pitchC > 20 || pitchC < -20) {
      pitchDelta = -1 * pitchDelta;
    }

    if (headingC > 360) {
      headingC = 0.0f;
    }
    setAttitudeIndicator(rollC, pitchC);
    setHeadingIndicator(headingC);
  }
}
