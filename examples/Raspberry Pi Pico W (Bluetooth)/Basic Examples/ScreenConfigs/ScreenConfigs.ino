// Atention: For Raspberry Pi Pico W, this library needs Bluetooth enabled.
// Go to 'Tools->IP/Bluetooth Stack' menu in the IDE and select 'x + Bluetooth'.
#include "Bind.h"
#include <SerialBT.h>

Bind bind;

void setScreenConfig() {
  // Configure screen settings
  BindCanvasSettings canvasSettings;
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
  setScreenConfig();
}

void setup() {
  Serial.begin(115200);

  SerialBT.begin();
	bind.init(SerialBT, onConnection);
}

void loop() {
  // Synchronize Bind UI Events (Not required on ESP32 when using BindOverBLE or BindOverWifi)
  // Callin bind.sync() regularly is crucial to handle of user inputs and touch events.
  // It's recommended to call bind.sync() a couple of times per second, but the faster, the better!
  bind.sync();
  delay(2);
}
