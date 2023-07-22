#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
ScreenObjects screenObjects;
ScreenKnob screenknob1;
const int ledPin = 2;

void screenDialKnobChanged(int16_t val)
{
  Serial.print("DialKnob has been changed:");
  Serial.println(val);
}

void addKnob()
{
  screenknob1.x = 20;
  screenknob1.y = 40;
  screenknob1.cmdId = ADD_OR_REFRESH_CMD;
  screenknob1.dimSize = 150;
  screenknob1.minValue = -500;
  screenknob1.maxValue = 500;
  screenknob1.value = 200;
  screenknob1.setlabel("Brightness");
  sendScreenStream(&screenknob1, &SerialBT);
}

void screenSetup()
{
  Serial.println("Screen setup started!");
  addKnob();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  screenObjects.registerScreenSetup(&screenSetup);
  screenObjects.registerDialKnob(&screenknob1, &screenDialKnobChanged);
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

