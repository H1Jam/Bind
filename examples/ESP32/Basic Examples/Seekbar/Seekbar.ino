#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
Bind bind;
BindSeekBar seekBar1;
BindSeekBar seekBar2;

const int ledPin = 2;

/**
 * @brief Seekbar 1 change callback.
 *
 * This function is automatically triggered when the value of Seekbar 1 changes on the screen.
 * It receives an integer parameter, 'val,' which represents the new value of Seekbar 1.
 * You can then implement the intended actions for this object based on this value.
 * To connect this callback function with the bind object, you MUST use the following call: 
 * bind.join(&[your seekbar object], &[this callbak name]);
 * Please ensure that you include the '&' symbols (these are pointers) in the function parameters.
 *
 *
 * @param val The new value of Seekbar 1.
 */
void seekbar1_changed(int16_t val) {
  Serial.print("Seekbar 1 has been changed:");
  Serial.println(val);
  // Some fun here:
  if (val > 150) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}

void seekbar2_changed(int16_t val) {
  Serial.print("Seekbar 2 has been changed:");
  Serial.println(val);
}

void addSeekBars() {
  // Syncing the first SeekBar:
  // Position on screen
  // Tip: You can utilize the grid view to manually adjust the object's
  // position on the screen. Afterward, replace these numbers with the values
  // displayed in grid view mode, representing the new object's x and y coordinates.
  seekBar1.x = 30;
  seekBar1.y = 100;
  // Width on screen (Hight is relative to Width for this object):
  seekBar1.width = 300;
  // Max value fo the seekbar:
  seekBar1.maxValue = 300;
  // Initial value for the seekbar:
  seekBar1.seekValue = 0;
  // This command either adds the object to the canvas (screen) or refreshes the existing one.
  seekBar1.cmdId = BIND_ADD_OR_REFRESH_CMD;

  bind.sync(&seekBar1);

  //Syncing the second SeekBar:
  seekBar2.x = 100;
  seekBar2.y = 150;
  seekBar2.cmdId = BIND_ADD_OR_REFRESH_CMD;
  seekBar2.seekValue = 0;
  seekBar2.maxValue = 100;
  seekBar2.width = 150;
  
  bind.sync(&seekBar2);
}

/**
 * @brief Screen Setup Callback for BindCanvas.
 *
 * This callback function is automatically invoked by BindCanvas upon establishing a connection.
 * It plays a crucial role in configuring the screen and ensuring that all screen objects are
 * synchronized properly. You will receive two parameters: 'w' for screen width and 'h' for screen height
 * in density-independent pixels (dp). These values allow you to maintain consistent object positioning
 * and size across various devices with different screen dimensions.
 *
 * Note: You do not need to manually call this function; it is automatically triggered by BindCanvas
 * upon connection.
 * Note: For more information about density-independent pixels (dp) visit:
 *                 https://en.wikipedia.org/wiki/Device-independent_pixel
 *
 * @param w The width of the screen in dp (Density-Independent Pixels).
 * @param h The height of the screen in dp (Density-Independent Pixels).
 */
void onConnection(int16_t w, int16_t h) {
  Serial.println("Screen setup started!");
  addSeekBars();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  String devName = "BindOnESP32";
  SerialBT.begin(devName);

  // Tell the bind object about our communication method:
  bind.init(&SerialBT, &onConnection);
  // It was SerialBT here, but it could be any serial port, including hardware and software serial.  

  // To connect the callback function with the bind object, you MUST use the following call:
  bind.join(&seekBar1, &seekbar1_changed);
  // And please ensure that you include the '&' symbols (these are pointers) in the function parameters.
  bind.join(&seekBar2, &seekbar2_changed);

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
