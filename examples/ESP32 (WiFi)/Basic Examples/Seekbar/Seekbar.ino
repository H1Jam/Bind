#include <WiFi.h>
#include "Bind.h"
#include "BindUtil/BindOverWifi.h"
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
UDPStream bindUdp;

Bind bind;
BindSeekBar seekBar1;
BindSeekBar seekBar2;

// if the LED_BUILTIN is not defined by the board, define it as pin 2
#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif

const int ledPin = LED_BUILTIN; // change this to the pin where your LED is connected.
unsigned long lastMs = 0;

/**
 * @brief Callback for Seekbar 1 Value Change
 *
 * This function is automatically triggered when Seekbar 1's value changes on the screen.
 * It receives an integer parameter, 'val,' representing the new value of Seekbar 1.
 * You can define specific actions based on this value to respond to Seekbar changes.
 * To link this callback function with the Bind object, use the following syntax (in the Setup()):
 * `bind.join(your_seekbar_object, seekbar1_changed);`
 * Make sure to include the '&' symbols as they indicate pointers to the function and object.
 *
 * @param val The new value of Seekbar 1.
 */
void seekbar1_changed(int16_t val) {

  // Implement your custom actions here:
  if (val > 150) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}

/**
 * @brief Callback for Seekbar 2 Value Change
 */
void seekbar2_changed(int16_t val) {
}

/**
 * @brief Adds SeekBars to the BindCanvas
 *
 * This function adds (or refreshes, if already exist) SeekBars on the BindCanvas screen. It synchronizes
 * the SeekBars' properties with their respective BindCanvas to display them correctly.
 * You can customize the SeekBars' position, width, maximum value, initial value, and more.
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
  /// Specify the command to either add the object to the BindCanvas(screen) or refresh the existing one.
  seekBar1.cmdId = BIND_ADD_OR_REFRESH_CMD;
  /// Set the callback function for the SeekBar 1 object.
  seekBar1.setCallback(seekbar1_changed);
  /// Synchronize the seekBar1 object with BindCanvas.
  bind.sync(seekBar1);

  /// Syncing the second SeekBar:
  seekBar2.x = 100;
  seekBar2.y = 150;
  seekBar2.cmdId = BIND_ADD_OR_REFRESH_CMD;
  seekBar2.seekValue = 0;
  seekBar2.maxValue = 100;
  seekBar2.width = 150;
  seekBar2.setCallback(seekbar2_changed);
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
  addSeekBars();
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  /// Initialize the Bind object and specify the communication method (bindUdp) and callback function (onConnection).
  // Start WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  bindUdp.begin("YOUR_DEVICE_NAME", bind);
	bind.init(bindUdp, onConnection);
}

void loop() {

  // This delay is not an essential part of the code
  // but is included here to simulate a brief pause..
  delay(10);
  // uncomment the following lines to print the SeekBar values,
  // if you don't use Serial for Bind.
  // if (millis() - lastMs > 1000) {
  //   lastMs = millis();
  //   Print the current values of the SeekBars
  //   Serial.print("SeekBar 1 value: ");
  //   Serial.print(seekBar1.seekValue);
  //   Serial.print("\tSeekBar 2 value: ");
  //   Serial.println(seekBar2.seekValue);
  // }
}
