// This example uses USB cable or External Bluetooth (HC06, HM10 or similar) for communication.
// If using the USB cable, you can connect your Arduino Board to 
// your phone/tablet using a USB OTG cable.
// If using an external Bluetooth module, you can connect your Arduino Board to
// the Bluetooth module using the Serial pins (RX, TX). Check your Arduino Board
// documentation for the correct pins.
// Also, remember to configure your Bluetooth module buad rate. 
// We assume 115200 bps as baud rate in this example.
#include "Bind.h"
#include <Adafruit_NeoPixel.h>

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
  pixels.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  // Initialize the Bind object and specify the communication method (Serial) and callback function (onConnection).
  bind.init(Serial, onConnection);
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
