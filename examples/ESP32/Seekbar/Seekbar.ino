#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
ScreenObjects screenObjects;
ScreenSeekBar screenSeekBar1;
const int ledPin = 2;

void screenSeekbar1Changed(int16_t val)
{
  Serial.print("Seekbar has been changed:");
  Serial.println(val);
}

void addSeekBar(){
  screenSeekBar1.x = 40;
  screenSeekBar1.y = 340;
  screenSeekBar1.cmdId = ENABLE_CMD;
  screenSeekBar1.seekValue = 0;
  screenSeekBar1.maxValue = 300;
  screenSeekBar1.width = 290;
  sendScreenStream(&screenSeekBar1, &SerialBT);
}

void screenSetup()
{
  Serial.println("Screen setup started!");
  addSeekBar();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  screenObjects.registerScreenSetup(&screenSetup);
  screenObjects.registerSeekBar(&screenSeekBar1, &screenSeekbar1Changed);
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
