#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
ScreenObjects screenObjects;
ScreenAttitudeIndicator screenAttitudeIndicator;
ScreenHeadingIndicator screenHeadingIndicator;
int counter = 0;

void addAttitudeIndicator() {
  screenAttitudeIndicator.x = 10;
  screenAttitudeIndicator.y = 10;
  screenAttitudeIndicator.cmdId = ADD_OR_REFRESH_CMD;
  screenAttitudeIndicator.roll = 0;
  screenAttitudeIndicator.pitch = 0;
  screenAttitudeIndicator.dimSize = 100;
  sendScreenStream(&screenAttitudeIndicator, &SerialBT);
}

void addHeadingIndicator() {
  screenHeadingIndicator.x = 120;
  screenHeadingIndicator.y = 10;
  screenHeadingIndicator.cmdId = ADD_OR_REFRESH_CMD;
  screenHeadingIndicator.heading =  gVal;
  screenHeadingIndicator.dimSize = 100;
  sendScreenStream(&screenHeadingIndicator, &SerialBT);
}

void screenSetup()
{
  Serial.println("Screen setup started!");
  addAttitudeIndicator();
  addHeadingIndicator();
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

