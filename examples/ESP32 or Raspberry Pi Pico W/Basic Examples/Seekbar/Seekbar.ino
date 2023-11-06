//Atention: For Raspberry Pi Pico W, this library needs Bluetooth enabled.  
//Use the 'Tools->IP/Bluetooth Stack' menu in the IDE to enable it (x + Bluetooth).

#if defined(ESP32)
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
#elif defined(ARDUINO_ARCH_RP2040)
#include <SerialBT.h>
#endif

#include "Bind.hpp"

Bind bind;
BindSeekBar seekBar1;
BindSeekBar seekBar2;

// If the board doesn't have built-in LED, assign an external LED here (if wish to use it):
#ifndef LED_BUILTIN
#define LED_BUILTIN 10
#endif  

/**
 * @brief Callback for Seekbar 1 Value Change
 *
 * This function is automatically triggered when Seekbar 1's value changes on the screen.
 * It receives an integer parameter, 'val,' representing the new value of Seekbar 1.
 * You can define specific actions based on this value to respond to Seekbar changes.
 * To link this callback function with the Bind object, use the following syntax (in the Setup()):
 * `bind.join(your_seekbar_object, seekbar1_changed);`
 * Make sure to include the '&' symbols as they indicate pointers to the function and object.
 * @note Ensure you call "bind.sync();" in the main loop in order to get the callback and chage events.
 *
 * @param val The new value of Seekbar 1.
 */
void seekbar1_changed(int16_t val) {
  Serial.print("Seekbar 1 value has changed to: ");
  Serial.println(val);

  // Implement your custom actions here:
  if (val > 150) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}

/**
 * @brief Callback for Seekbar 2 Value Change
 */
void seekbar2_changed(int16_t val) {
  Serial.print("Seekbar 2 has been changed:");
  Serial.println(val);
}

/**
 * @brief Adds SeekBars to the BindCanvas
 *
 * This function adds (or refreshes, if already exist) SeekBars on the BindCanvas screen. It synchronizes
 * the SeekBars' properties with their respective BindCanvas to display them correctly.
 * You can customize the SeekBars' position, width, maximum value, initial value, and more.
 * @note Ensure you call "bind.sync();" in the main loop in order to get the callback and chage events.
 */
void addSeekBars() {
  // Syncing the first SeekBar:
  // Set the SeekBar's position on the screen.
  // Tip: You can use the grid view mode inBindCanvas app to determine the x and y coordinates
  // and replace these numbers with the grid values for precise positioning.
  seekBar1.x = 30;
  seekBar1.y = 100;
  /// Set the width of the SeekBar on the screen (height is relative to width for this object).
  seekBar1.width = 300;
  /// Set the maximum value for the SeekBar.
  seekBar1.maxValue = 300;
  /// Set the initial value for the SeekBar.
  seekBar1.seekValue = 0;
  /// Specify the command to either add the object
  to the BindCanvas(screen) or refresh the existing one.
  seekBar1.cmdId = BIND_ADD_OR_REFRESH_CMD;
  /// Synchronize the seekBar1 object with BindCanvas.
  bind.sync(seekBar1);

  /// Syncing the second SeekBar:
  seekBar2.x = 100;
  seekBar2.y = 150;
  seekBar2.cmdId = BIND_ADD_OR_REFRESH_CMD;
  seekBar2.seekValue = 0;
  seekBar2.maxValue = 100;
  seekBar2.width = 150;
  /// Synchronize the seekBar2 object with BindCanvas.
  bind.sync(seekBar2);
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
 * @param width The width of the screen in dp (Density-Independent Pixels).
 * @param height The height of the screen in dp (Density-Independent Pixels).
 */
void onConnection(int16_t width, int16_t height) {
  Serial.println("Screen setup started!");
  addSeekBars();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  
#if defined(ESP32)
  String devName = "BindOnESP32";
  SerialBT.begin(devName);
  Serial.println("The Bluetooth device started. Pair your phone with Bluetooth!");
  Serial.println("Device Name:");
  Serial.println(devName);
#elif defined(ARDUINO_ARCH_RP2040)
  SerialBT.begin();
#endif

  /// Initialize the Bind object and specify the communication method (SerialBT) and callback function (onConnection).
  bind.init(SerialBT, onConnection);
  /// Note: It was SerialBT here, but it could be any serial port, including hardware and software serial.

  /// Connect the callback functions with the Bind objects.
  bind.join(seekBar1, seekbar1_changed);
  bind.join(seekBar2, seekbar2_changed);
  /// @note please ensure that you include the '&' symbols in the function parameters, these are pointers.


}

void loop() {
  /**
 * Synchronize Bind UI Events
 *
 * To ensure proper handling of user inputs and touch events, it's crucial to call
 * this function regularly within your Arduino loop. Failing to do so may result
 * in missed events, such as button clicks or user interactions with your UI elements.
 * By calling `bind.sync()`, you maintain seamless communication between your Arduino
 * code and the Bind Framework.
 * It's recommended to call sync() a couple of times per second, but the faster, the better!
 * Aim for a rate above 20Hz for ideal performance.
  */

  // Regularly synchronize Bind UI events
  bind.sync();

  // This delay is not an essential part of the code
  // but is included here to simulate a brief pause..
  delay(10);
}
