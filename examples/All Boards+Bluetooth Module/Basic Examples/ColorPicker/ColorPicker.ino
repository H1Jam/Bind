//We only use SoftwareSerial for AVR Arduinos or ESP8266 library.
#if defined(__AVR__) || defined(ESP8266)
#include <SoftwareSerial.h>
#endif

#include "Bind.hpp"

// Note: Adjust the pins to match your Bluetooth module's configuration.
// We may use SoftwareSerial for AVR Arduinos or ESP8266.
#ifdef __AVR__
SoftwareSerial btSerial(4, 3);  // For AVR Arduinos like Pro Mini or Mega: RX: pin 4, TX: pin 3
#elif defined(ESP8266)
SoftwareSerial btSerial(D1, D2);  // For ESP8266: RX: pin D1, TX: pin D2
#elif defined(ESP32)
#define btSerial Serial2  // For ESP32 we use Serial2.
#elif defined(ARDUINO_ARCH_RP2040)
#define btSerial Serial1  // For RP2040(Raspberry Pi Pico): Use serial1 RX: pin 2, TX: pin 3
#else
SoftwareSerial btSerial(4, 3);  // Modify this line, if your board is neither above.
#endif

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
  // Initialize the Bind object and specify the communication method (btSerial) and callback function (onConnection).
  bind.init(btSerial, onConnection);
  // Note: It was btSerial here, but it could be any serial port, including hardware and software serial.

  // Connect the callback functions with the Bind objects.
  bind.join(colorPicker1, colorPicker1_changed);

  // Note: Adjust the baud rate to match your Bluetooth module's configuration.
  btSerial.begin(57600);
}

void loop() {
  // Regularly synchronize Bind UI events to receive button press events.
  bind.sync();

  // This delay is not an essential part of the code
  // but is included here to simulate the other work you may want to do.
  delay(10);
}
