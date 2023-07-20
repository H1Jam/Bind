#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
ScreenObjects screenObjects;
ScreenSwitch screenSwitch;
const int ledPin = 2;

void screenSwitchChanged1(bool ischecked)
{
  Serial.print("ScreenSwitch has been changed:");
  Serial.println(ischecked);
  digitalWrite(ledPin, ischecked);
}

void addSwitch() {
  screenSwitch.x = 60;
  screenSwitch.y = 160;
  screenSwitch.cmdId = ENABLE_CMD;
  screenSwitch.switchValue = false;
  screenSwitch.fontSize = 30;
  screenSwitch.textColor = YELLOW;
  screenSwitch.setlabel("SwitchFromBind");
  sendScreenStream(&screenSwitch, &SerialBT);
}

void screenSetup()
{
  Serial.println("Screen setup started!");
  addSwitch();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  screenObjects.registerScreenSetup(&screenSetup);
  screenObjects.registerSwitch(&screenSwitch, &screenSwitchChanged1);
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
