#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
ScreenObjects screenObjects;
ScreenSwitch screenSwitch;
int result =0;
const int ledPin = 2;
bool ledIsON = false;

void buttonClicked1()
{
  Serial.println("button1 has been clicked!");
  ledIsON = !ledIsON;
  digitalWrite(ledPin, ledIsON);
}

void addSwitch() {
  screenSwitch.x = 60;
  screenSwitch.y = 160;
  screenSwitch.cmdId = ENABLE_CMD;
  screenSwitch.switchValue = false;
  screenSwitch.fontSize = 30;
  screenSwitch.textColor = MAGENTA;
  screenSwitch.setlabel( "SwitchFromBind");
  sendScreenStream(&screenSwitch, &SerialBT);
}

void screenSetup()
{
  Serial.println("Screen setup started!");
  addSwitch()
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  screenObjects.registerScreenSetup(&screenSetup);
  screenObjects.registerSwitch(&screenSwitch);
  String devName = "ESP32testB";
  SerialBT.begin(devName);
  Serial.println("The bluetooth device started, now you can pair the phone with bluetooth!");
  Serial.println("devName:");
  Serial.println(devName);
}

void loop() {
  while (SerialBT.available()) {
  result = screenObjects.updateScreen(SerialBT.read());
  
  }
  delay(1);
}
