// This example uses USB cable or External Bluetooth (HC06, HM10 or similar) for communication.
// If using the USB cable, you can connect your Arduino Board to 
// your phone/tablet using a USB OTG cable.
// If using an external Bluetooth module, you can connect your Arduino Board to
// the Bluetooth module using the Serial pins (RX, TX). Check your Arduino Board
// documentation for the correct pins.
// Also, remember to configure your Bluetooth module buad rate. 
// We assume 115200 bps as baud rate in this example.
#include "Bind.h"

Bind bind;
BindColorPicker colorPicker1;

/**
 * @brief colorPicker1's Callback
 */
void colorPicker1_changed(uint8_t red, uint8_t green, uint8_t blue) {
}

void addColorPicker() {
  colorPicker1.x = 50;                          /// The x-coordinate position of the color picker on the screen.
  colorPicker1.y = 100;                          /// The y-coordinate position of the color picker on the screen.
  colorPicker1.dimSize = 200;                    /// The dimensions (size) of the color picker.
  colorPicker1.red = 160;                        /// The initial value for the red component of the selected color (0-255).
  colorPicker1.green = 190;                      /// The initial value for the green component of the selected color (0-255).
  colorPicker1.blue = 220;                       /// The initial value for the blue component of the selected color (0-255).
  colorPicker1.cmdId = BIND_ADD_OR_REFRESH_CMD;  /// Command identifier to add or refresh the color picker.
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
  // Initialize the Bind object and specify the communication method (Serial) and callback function (onConnection).
	bind.init(Serial, onConnection);

  // Connect the callback functions with the Bind objects.
  bind.join(colorPicker1, colorPicker1_changed);
}

void loop() {
  // Synchronize Bind UI Events (Not required on ESP32 when using BindOverBLE or BindOverWifi)
  // Callin bind.sync() regularly is crucial to handle of user inputs and touch events.
  // It's recommended to call bind.sync() a couple of times per second, but the faster, the better!
  bind.sync();
  // This delay is not an essential part of the code
  // but is included here to simulate the other work you may want to do.
  delay(10);
}
