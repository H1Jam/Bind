//We only use SoftwareSerial for AVR Arduinos or ESP8266 library.
#if defined(__AVR__) || defined(ESP8266)
#include <SoftwareSerial.h>
#endif

#include "Bind.h"

// Note: Adjust the pins to match your Bluetooth module's configuration.
// We may use SoftwareSerial for AVR Arduinos or ESP8266.
#ifdef __AVR__
SoftwareSerial btSerial(4, 3); // For AVR Arduinos like Pro Mini or Mega: RX: pin 4, TX: pin 3
#elif defined(ESP8266)
SoftwareSerial btSerial(D1, D2); // For ESP8266: RX: pin D1, TX: pin D2
#elif defined(ESP32) 
#define btSerial Serial2 // For ESP32 we use Serial2.
#elif defined(ARDUINO_ARCH_RP2040)
#define btSerial Serial1 // For RP2040(Raspberry Pi Pico): Use serial1 RX: pin 2, TX: pin 1
#else
SoftwareSerial btSerial(4, 3); // Modify this line, if your board is neither above.
#endif

Bind bind;
BindCanvasSettings canvasSettings;

void setScreenConfig() {
  // Configure screen settings

  // Screen orientation is unspecified, allowing the system to decide.
  //canvasSettings.screenOrientation = SCREEN_ORIENTATION_UNSPECIFIED;

  // Portrait mode: screen height > width.
  //canvasSettings.screenOrientation = SCREEN_ORIENTATION_PORTRAIT;

  // Landscape mode: screen width > height.
  canvasSettings.screenOrientation = SCREEN_ORIENTATION_LANDSCAPE;
  canvasSettings.backColor = BLACK; 
  // Or use RGB(R:0-255, G:0-255, B0-255). 
  //For example:
  //canvasSettings.backColor = RGB(100,255,40);
  bind.sync(canvasSettings);
}

void onConnection(int16_t width, int16_t height) {
  Serial.print("Screen setup started!");
  Serial.print(width);
  Serial.print("x");
  Serial.println(height);

  setScreenConfig();

  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  // Note: Adjust the baud rate to match your Bluetooth module's configuration.
  btSerial.begin(57600);

  bind.init(btSerial, onConnection);

}

void loop() {
  bind.sync();
  delay(2);
}
