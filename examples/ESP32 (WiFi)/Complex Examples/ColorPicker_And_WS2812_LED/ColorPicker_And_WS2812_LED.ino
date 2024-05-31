#include <WiFi.h>
#include "Bind.h"
#include "BindUtil/BindOverWifi.h"
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
UDPStream bindUdp;
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

  // Connect the callback functions with the Bind objects.
  bind.join(colorPicker1, colorPicker1_changed);
}

void loop() {
  // This delay is not an essential part of the code
  // but is included here to simulate the other work you may want to do.
  delay(10);
}
