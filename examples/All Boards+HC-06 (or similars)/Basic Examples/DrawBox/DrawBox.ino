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
BindRectangle rectangle1;
BindRectangle rectangle2;

// onConnection Callback for BindCanvas
void onConnection(int16_t width, int16_t height) {
  Serial.println("Screen setup started!");
  configureCanvasSettings();
  addRectangle();
  drawAdaptiveRectangle(width);
  Serial.println("Screen setup done!");
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
  // Initialize the Bind object and specify the communication method (btSerial) and callback function (onConnection).
  bind.init(btSerial, onConnection);
  // Note: Adjust the baud rate to match your Bluetooth module's configuration.
  btSerial.begin(57600);
}

void loop() {
  // Synchronize Bind UI events
  bind.sync();

  // Add a small delay to control the loop speed
  delay(10);
}
