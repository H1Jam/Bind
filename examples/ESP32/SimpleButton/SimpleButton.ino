#include "BluetoothSerial.h"
#include "UIduino.hpp"

BluetoothSerial SerialBT;
ScreenObjects screenObjects;
ScreenButton screenButton1;

void buttonClicked1()
{
  Serial.println("button1 has been clicked!");
}

void screenSetup()
{
  Serial.println("Screen setup started!");
  screenButton1.x = 60;
  screenButton1.y = 220;
  screenButton1.color = BLACK;
  screenButton1.backColor = YELLOW;
  screenButton1.cmdId = ENABLE_CMD;
  screenButton1.setlabel("Button1");
  screenButton1.fontSize = 23;
  sendScreenStream(&screenButton1, &SerialBT);
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
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
