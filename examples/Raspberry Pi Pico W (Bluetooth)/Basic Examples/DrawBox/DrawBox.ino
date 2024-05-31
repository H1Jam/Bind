// Atention: For Raspberry Pi Pico W, this library needs Bluetooth enabled.
// Go to 'Tools->IP/Bluetooth Stack' menu in the IDE and select 'x + Bluetooth'.
#include "Bind.h"
#include <SerialBT.h>

Bind bind;
BindRectangle rectangle1;
BindRectangle rectangle2;

// onConnection Callback for BindCanvas
void onConnection(int16_t width, int16_t height) {
  configureCanvasSettings();
  addRectangle();
  drawAdaptiveRectangle(width);
}

// Function to configure the BindCanvas screen settings
void configureCanvasSettings() {
  // Set the screen orientation (0 for portrait, 1 for landscape)
  BindCanvasSettings canvasSettings;
  canvasSettings.screenOrientation = SCREEN_ORIENTATION_PORTRAIT;
  // Set the background color of the screen (in RGB format)
  canvasSettings.backColor = RGB(240, 240, 240);
  // Synchronize the canvasSettings object with BindCanvas
  bind.sync(canvasSettings);
}

// Function to add a rectangle to the BindCanvas screen
void addRectangle() {
  // Configure and synchronize the rectangle
  rectangle1.x = 10;
  rectangle1.y = 280;
  rectangle1.width = 200;
  rectangle1.height = 200;
  rectangle1.cmdId = BIND_ADD_OR_REFRESH_CMD;
  rectangle1.fillColor = WHITE;                 // Fill color of the rectangle (in RGB format)
  rectangle1.borderColor = RGB(100, 100, 100);  // Border color of the rectangle (in RGB format)
  rectangle1.borderWidth = 1;                   // Border width
  rectangle1.cornersRadius = 5;                 /// Radius of the rectangle's rounded corners.
  bind.sync(rectangle1);
}

void drawAdaptiveRectangle(int16_t screenWidth) {
  rectangle2.x = 10;
  rectangle2.y = 70;
  rectangle2.width = screenWidth - rectangle2.x * 2;
  rectangle2.height = 200;
  rectangle2.cmdId = BIND_ADD_OR_REFRESH_CMD;
  rectangle2.fillColor = WHITE;     // Fill color of the rectangle (in RGB format)
  rectangle2.borderColor = DKGRAY;  // Border color of the rectangle (in RGB format)
  rectangle2.borderWidth = 0;       // Border width
  rectangle2.cornersRadius = 2;     /// Radius of the rectangle's rounded corners.
  bind.sync(rectangle2);
}


void setup() {
  Serial.begin(115200);
  // Initialize the Bind object and specify the communication method (SerialBT) and callback function (onConnection).
  SerialBT.begin();
	bind.init(SerialBT, onConnection);
}

void loop() {
  // Synchronize Bind UI events
  // Synchronize Bind UI Events (Not required on ESP32 when using BindOverBLE or BindOverWifi)
  // Callin bind.sync() regularly is crucial to handle of user inputs and touch events.
  // It's recommended to call bind.sync() a couple of times per second, but the faster, the better!
  bind.sync();

  // Add a small delay to control the loop speed
  delay(10);
}
