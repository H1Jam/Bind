#if defined(ARDUINO_ARCH_ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#include "Bind.h"
#include "BindUtil/BindOverWifi.h"
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
UDPStream bindUdp;

Bind bind;
BindColorPicker colorPicker1;

unsigned long lastMs = 0;
/**
 * @brief colorPicker1's Callback,
 * 
 * Note: This function is automatically triggered when the color is changed by the user on the screen.
 * Note: Depending on your design, you can use the callback function or access the colorPicker1 object to get the current color values.
 *  We have used the callback function here to demonstrate the usage.
 *  You can use the colorPicker1 to get the current color values in the main loop() as well.
 */
void colorPicker1_changed(uint8_t red, uint8_t green, uint8_t blue) {
  // Atention: If you are using this Serial port for Bind,
  // you should comment the following lines in order to avoid conflicts.
  Serial.print("Color changed to: ");
  Serial.print("R: ");
  Serial.print(red);
  Serial.print(" G: ");
  Serial.print(green);
  Serial.print(" B: ");
  Serial.println(blue);
  // Implement your custom actions here based on the color values
}

void addColorPicker() {
  colorPicker1.x = 50;                          /// The x-coordinate position of the color picker on the screen.
  colorPicker1.y = 100;                          /// The y-coordinate position of the color picker on the screen.
  colorPicker1.dimSize = 200;                    /// The dimensions (size) of the color picker.
  colorPicker1.red = 160;                        /// The initial value for the red component of the selected color (0-255).
  colorPicker1.green = 190;                      /// The initial value for the green component of the selected color (0-255).
  colorPicker1.blue = 220;                       /// The initial value for the blue component of the selected color (0-255).
  colorPicker1.cmdId = BIND_ADD_OR_REFRESH_CMD;  /// Command identifier to add or refresh the color picker.
  colorPicker1.setCallback(colorPicker1_changed);/// Set the callback function for the color picker object.
  bind.sync(colorPicker1);
}

/**
 * @brief Connection Callback for BindCanvas.
 */
void onConnection(int16_t w, int16_t h) {
  addColorPicker();
}

void setup() {
  Serial.begin(115200);
  // Initialize the Bind object and specify the communication method (bindUdp) and callback function (onConnection).
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
  // but is included here to simulate the other work you may want to do.
  delay(10);
  // An example of how to get the current color values in the main loop.
  // Atention: If you are using this Serial port for Bind,
  // you should comment the following lines in order to avoid conflicts.
  if (millis() - lastMs > 1000) {
    lastMs = millis();
    Serial.print("Current Color: ");
    Serial.print("R: ");
    Serial.print(colorPicker1.red);
    Serial.print(" G: ");
    Serial.print(colorPicker1.green);
    Serial.print(" B: ");
    Serial.println(colorPicker1.blue);
  }
}
