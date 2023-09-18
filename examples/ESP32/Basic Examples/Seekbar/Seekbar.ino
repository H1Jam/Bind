#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
Bind bind;
BindSeekBar screenSeekBar1;
BindSeekBar screenSeekBar2;

const int ledPin = 2;

/**
 * @brief Seekbar 1 change callback.
 *
 * This function is automatically triggered when the value of Seekbar 1 changes on the screen.
 * It receives an integer parameter, 'val,' which represents the new value of Seekbar 1.
 * You can then implement the intended actions for this object based on this value.
 * To connect this callback function with the bind object, you MUST use the following call: 
 * bind.bindSeekBar(&[your seekbar object], &[this callbak name]);
 * Please ensure that you include the '&' symbols (these are pointers) in the function parameters.
 *
 *
 * @param val The new value of Seekbar 1.
 */
void screenSeekbar1_changed(int16_t val) {
  Serial.print("Seekbar 1 has been changed:");
  Serial.println(val);
  // Some fun here:
  if (val > 150) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}

void screenSeekbar2_changed(int16_t val) {
  Serial.print("Seekbar 2 has been changed:");
  Serial.println(val);
}

void addSeekBars() {
  // Syncing the first SeekBar:
  // Position on screen
  // Tip: You can utilize the grid view to manually adjust the object's
  // position on the screen. Afterward, replace these numbers with the values
  // displayed in grid view mode, representing the new object's x and y coordinates.
  screenSeekBar1.x = 30;
  screenSeekBar1.y = 100;
  // Width on screen (Hight is relative to Width for this object):
  screenSeekBar1.width = 300;
  // Max value fo the seekbar:
  screenSeekBar1.maxValue = 300;
  // Initial value for the seekbar:
  screenSeekBar1.seekValue = 0;
  // This command either adds the object to the canvas (screen) or refreshes the existing one.
  screenSeekBar1.cmdId = BIND_ADD_OR_REFRESH_CMD;

  bind.sync(&screenSeekBar1);

  //Syncing the second SeekBar:
  screenSeekBar2.x = 100;
  screenSeekBar2.y = 150;
  screenSeekBar2.cmdId = BIND_ADD_OR_REFRESH_CMD;
  screenSeekBar2.seekValue = 0;
  screenSeekBar2.maxValue = 100;
  screenSeekBar2.width = 150;
  bind.sync(&screenSeekBar2);
}

/**
 * @brief The screen setup callback.
 *
 * Bind automatically invokes this function upon connecting to BindCanvas.
 * You should sync all the screen objects here. 
 * You'll receive two integers as the parameters: 'w' for width and 'h' for height.
 * These values allow you to ensure that the objects' positioning and size remain
 * consistent across various devices with varying screen sizes."
 * 
 * Note: You don't need to call this function manually!
 *
 * @param w The width of the screen in dp (Density-independent Pixels).
 * @param h The height of the screen in dp (Density-independent Pixels).
*/
void screenSetup(int16_t w, int16_t h) {
  Serial.println("Screen setup started!");
  addSeekBars();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  String devName = "BindOnESP32";
  SerialBT.begin(devName);
  
  bind.bindScreenSetup(&screenSetup);
  // To connect the callback function with the bind object, you MUST use the following call:
  bind.bindSeekBar(&screenSeekBar1, &screenSeekbar1_changed);
  // And please ensure that you include the '&' symbols (these are pointers) in the function parameters.
  bind.bindSeekBar(&screenSeekBar2, &screenSeekbar2_changed);
  // Tell the bind object about our communication method:
  bind.setBindDevice(&SerialBT);
  // It was SerialBT here, but it could be any serial port, including hardware and software serial.

  Serial.println("The bluetooth device started, now you can pair the phone with bluetooth!");
  Serial.println("devName:");
  Serial.println(devName);
}

void loop() {
  // Important Note: To ensure smooth operation and prevent data loss or lag,
  // regularly run the following line of code. It's recommended to execute it
  // a couple of times per second, but the faster, the better!
  // Aim for a rate above 20Hz for ideal performance.
  bind.sync();

  // This delay is not an essential part of the code
  // but is included here to simulate a brief pause..
  delay(10);
}
