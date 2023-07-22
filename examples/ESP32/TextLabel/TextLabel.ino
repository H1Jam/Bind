#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
ScreenObjects screenObjects;
ScreenTextLabel textLabel1;
ScreenTextLabel textLabel2;
int counter = 0;
char buffer[10];

void screenSwitchChanged1(bool ischecked)
{
  Serial.print("ScreenSwitch has been changed:");
  Serial.println(ischecked);
}

void addtTextlabel() {
  textLabel1.x = 20;
  textLabel1.y = 20;
  textLabel1.setlabel("Hello Android!");
  textLabel1.color = WHITE;
  textLabel1.fontSize = 28;
  textLabel1.cmdId = ADD_OR_REFRESH_CMD;
  sendScreenStream(&textLabel1, &SerialBT);

  textLabel2.x = 20;
  textLabel2.y = 50;
  textLabel2.setlabel("Second caption");
  textLabel2.color = YELLOW;
  textLabel2.fontSize = 18;
  textLabel2.cmdId = ADD_OR_REFRESH_CMD;
  sendScreenStream(&textLabel2, &SerialBT);
}

void screenSetup()
{
  Serial.println("Screen setup started!");
  addtTextlabel();
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

