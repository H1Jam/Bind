#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
ScreenObjects screenObjects;
ScreenButton screenButton1;
const int ledPin = 2;
bool ledIsON = false;

void buttonClicked1()
{
  Serial.println("button1 has been clicked!");
  ledIsON = !ledIsON;
  digitalWrite(ledPin, ledIsON);
}

void screenSetup()
{
  Serial.println("Screen setup started!");
  screenButton1.x = 60; // location on android screen
  screenButton1.y = 220; // location on android screen
  screenButton1.color = BLACK; // Text color
  screenButton1.backColor = YELLOW; // button color
  screenButton1.setlabel("Button1"); // button label
  screenButton1.fontSize = 23; // button label font size
  screenButton1.cmdId = ENABLE_CMD;
  sendScreenStream(&screenButton1, &SerialBT);
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  screenObjects.registerScreenSetup(&screenSetup);
  screenButton1.setCallback(&buttonClicked1);
  screenObjects.registerButton(&screenButton1);
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
  delay(1);
}
