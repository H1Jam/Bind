#include <SoftwareSerial.h>
#include "Bind.hpp"
#include <Adafruit_NeoPixel.h>

// Note: Adjust the pins to match your Bluetooth module's configuration.
#ifdef __AVR__
SoftwareSerial swSerial(4, 3);
#else
SoftwareSerial swSerial(D4, D3); // For boards like ESP8266, ESP32, or similar.
#endif
Bind bind;
BindColorPicker colorPicker1;

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 12  // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 8  // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

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
  pixels.clear();
  for (int i = 0; i < NUMPIXELS; i++) {  // For each pixel...
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(red, green, blue));
  }
  pixels.show();
}

void addColorPicker() {
  colorPicker1.x = 50;                           /// The x-coordinate position of the color picker on the screen.
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
  pixels.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  // Initialize the Bind object and specify the communication method (swSerial) and callback function (onConnection).
  bind.init(swSerial, onConnection);
  // Note: It was swSerial here, but it could be any serial port, including hardware and software serial.

  // Connect the callback functions with the Bind objects.
  bind.join(colorPicker1, colorPicker1_changed);

  // Note: Adjust the baud rate to match your Bluetooth module's configuration.
  swSerial.begin(57600);
}

void loop() {
  // Regularly synchronize Bind UI events to receive button press events.
  bind.sync();

  // This delay is not an essential part of the code
  // but is included here to simulate the other work you may want to do.
  delay(10);
}
