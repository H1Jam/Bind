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
BindColorPicker colorPicker1;

/**
 * @brief colorPicker1's Callback
 */
void colorPicker1_changed(uint8_t red, uint8_t green, uint8_t blue) {
  Serial.print("ColorPicker has been changed: r:");
  Serial.print(red);
  Serial.print("\tg:");
  Serial.print(green);
  Serial.print("\tb:");
  Serial.println(blue);
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
  Serial.println("Screen setup started!");
  addColorPicker();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  // Initialize the Bind object and specify the communication method (SerialBT) and callback function (onConnection).
  bind.init(SerialBT, onConnection);
  // Note: It was SerialBT here, but it could be any serial port, including hardware and software serial.

  // Connect the callback functions with the Bind objects.
  bind.join(colorPicker1, colorPicker1_changed);

  
#if defined(ESP32)
  String devName = "BindOnESP32";
  SerialBT.begin(devName);
  Serial.println("The Bluetooth device started. Pair your phone with Bluetooth!");
  Serial.println("Device Name:");
  Serial.println(devName);
#elif defined(ARDUINO_ARCH_RP2040)
  SerialBT.begin();
#endif
}

void loop() {
  // Regularly synchronize Bind UI events to receive button press events.
  bind.sync();

  // This delay is not an essential part of the code
  // but is included here to simulate the other work you may want to do.
  delay(10);
}
