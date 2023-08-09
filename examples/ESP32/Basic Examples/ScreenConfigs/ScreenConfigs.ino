#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
ScreenObjects screenObjects;
ScreenSettings screenSettings;

void screenAppearance() {
  screenSettings.screenOrientation = SCREEN_ORIENTATION_UNSPECIFIED;
  screenSettings.backColor = UBUNTU;
  screenSettings.actionBarColor = DKGRAY;
  screenSettings.setlabel("Hello Android");
  sendScreenStream(&screenSettings, &SerialBT);
}

void screenSetup()
{
  Serial.println("Screen setup started!");
  screenAppearance();
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
}
