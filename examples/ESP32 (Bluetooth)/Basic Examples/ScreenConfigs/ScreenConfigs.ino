#include "Bind.h"
#include "BindUtil/BindOverBLE.h"
BleStream bleStream;

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

  bleStream.begin("YOUR_DEVICE_NAME", bind);
	bind.init(bleStream, onConnection);
}

void loop() {
  delay(2);
}
