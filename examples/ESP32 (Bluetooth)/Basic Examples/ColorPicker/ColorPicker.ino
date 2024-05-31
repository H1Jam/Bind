#include "Bind.h"
#include "BindUtil/BindOverBLE.h"
BleStream bleStream;

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
  // Initialize the Bind object and specify the communication method (bleStream) and callback function (onConnection).
  bleStream.begin("YOUR_DEVICE_NAME", bind);
	bind.init(bleStream, onConnection);

  // Connect the callback functions with the Bind objects.
  bind.join(colorPicker1, colorPicker1_changed);
}

void loop() {
  // This delay is not an essential part of the code
  // but is included here to simulate the other work you may want to do.
  delay(10);
}
