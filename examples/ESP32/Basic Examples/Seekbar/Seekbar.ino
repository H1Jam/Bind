#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
Bind bind;
ScreenSeekBar screenSeekBar1;
const int ledPin = 2;

void screenSeekbar1Changed(int16_t val)
{
  Serial.print("Seekbar has been changed:");
  Serial.println(val);
}

void addSeekBar(){
  screenSeekBar1.x = 40;
  screenSeekBar1.y = 160;
  screenSeekBar1.cmdId = ADD_OR_REFRESH_CMD;
  screenSeekBar1.seekValue = 0;
  screenSeekBar1.maxValue = 300;
  screenSeekBar1.width = 290;
  sendScreenStream(&screenSeekBar1, &SerialBT);
}

void screenSetup(int16_t w, int16_t h)
{
  Serial.println("Screen setup started!");
  addSeekBar();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  bind.bindScreenSetup(&screenSetup);
  bind.bindSeekBar(&screenSeekBar1, &screenSeekbar1Changed);
  String devName = "BindOnESP32";
  SerialBT.begin(devName);
  Serial.println("The bluetooth device started, now you can pair the phone with bluetooth!");
  Serial.println("devName:");
  Serial.println(devName);
}

void loop() {
  bind.updateScreen(&SerialBT);
  delay(10);
}

