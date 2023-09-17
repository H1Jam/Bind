#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
Bind bind;
ScreenSeekBar screenSeekBar1;
ScreenSeekBar screenSeekBar2;
const int ledPin = 2;

void screenSeekbar1Changed(int16_t val)
{
  Serial.print("Seekbar has been changed:");
  Serial.println(val);
}



void addSeekBars(){
  //Syncing the first SeekBar:
  screenSeekBar1.x = 30;
  screenSeekBar1.y = 100;
  screenSeekBar1.cmdId = ADD_OR_REFRESH_CMD;
  screenSeekBar1.seekValue = 0;
  screenSeekBar1.maxValue = 300;
  screenSeekBar1.width = 300;
  bind.sync(&screenSeekBar1);

  //Syncing the second SeekBar:
  screenSeekBar2.x = 100;
  screenSeekBar2.y = 150;
  screenSeekBar2.cmdId = ADD_OR_REFRESH_CMD;
  screenSeekBar2.seekValue = 0;
  screenSeekBar2.maxValue = 100;
  screenSeekBar2.width = 150;
  bind.sync(&screenSeekBar2);
}

/**
 * @brief The screen setup callback for a BindCanvas.
 *
 * You don't need to call this function manually, Bind calls this function
 * automatically when the BindCanva (eg. the Android App) connectes to 
 * the MCU board. You should sync the screen objects and send them here.
 * It takes two integer parameters, 'w' for width and 'h' for height 
 *
 * @param w The width of the screen in dp (Density-independent Pixels).
 * @param h The height of the screen in dp (Density-independent Pixels).
 */
void screenSetup(int16_t w, int16_t h)
{
  Serial.println("Screen setup started!");
  addSeekBars();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  bind.bindScreenSetup(&screenSetup);
  bind.bindSeekBar(&screenSeekBar1, &screenSeekbar1Changed);
  bind.bindSeekBar(&screenSeekBar2, &screenSeekbar1Changed);
  String devName = "BindOnESP32";
  SerialBT.begin(devName);
  bind.setBindDevice(&SerialBT);
  Serial.println("The bluetooth device started, now you can pair the phone with bluetooth!");
  Serial.println("devName:");
  Serial.println(devName);
}

void loop() {
  bind.updateScreen(&SerialBT);
  delay(10);
}

