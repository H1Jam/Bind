// Atention: For Raspberry Pi Pico W, this library needs Bluetooth enabled.
// Use the 'Tools->IP/Bluetooth Stack' menu in the IDE to enable it (x +
// Bluetooth).

#include <SerialBT.h>
#include "Bind.hpp"

Bind bind;
BindCanvasSettings canvasSettings;

void setScreenConfig() {
  // Configure screen settings

  // Screen orientation is unspecified, allowing the system to decide.
  // canvasSettings.screenOrientation = SCREEN_ORIENTATION_UNSPECIFIED;

  // Portrait mode: screen height > width.
  // canvasSettings.screenOrientation = SCREEN_ORIENTATION_PORTRAIT;

  // Landscape mode: screen width > height.
  canvasSettings.screenOrientation = SCREEN_ORIENTATION_LANDSCAPE;
  canvasSettings.backColor = BLACK;
  // Or use RGB(R:0-255, G:0-255, B0-255).
  // For example:
  // canvasSettings.backColor = RGB(100,255,40);
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
  SerialBT.begin();
  bind.init(SerialBT, onConnection);
}

void loop() {
  bind.sync();
  delay(2);
}
