// This example uses USB cable or External Bluetooth (HC06, HM10 or similar) for communication.
// If using the USB cable, you can connect your Arduino Board to 
// your phone/tablet using a USB OTG cable.
// If using an external Bluetooth module, you can connect your Arduino Board to
// the Bluetooth module using the Serial pins (RX, TX). Check your Arduino Board
// documentation for the correct pins.
// Also, remember to configure your Bluetooth module buad rate. 
// We assume 115200 bps as baud rate in this example.
#include "Bind.h"

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

	bind.init(Serial, onConnection);
}

void loop() {
  // Synchronize Bind UI Events (Not required on ESP32 when using BindOverBLE or BindOverWifi)
  // Callin bind.sync() regularly is crucial to handle of user inputs and touch events.
  // It's recommended to call bind.sync() a couple of times per second, but the faster, the better!
  bind.sync();
  delay(2);
}
