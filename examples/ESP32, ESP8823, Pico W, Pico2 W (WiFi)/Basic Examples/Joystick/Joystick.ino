#if defined(ARDUINO_ARCH_ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#include "Bind.h"
#include "BindUtil/BindOverWifi.h"
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
UDPStream bindUdp;

Bind bind;
BindJoystick joystick1;
BindJoystick joystick2;

// Atention: If you are using this Serial port for Bind,
// you should comment all Serial.print(...)/println(...) lines to avoid conflicts.

/**
 * @brief Callback for joystick change.
 *
 * This function is triggered when the joystick's position changes. It receives
 * two parameters, representing X and Y axis values of the joystick.
 *
 * @param x The new X-coordinate of the joystick, -100 to 100.
 * @param y The new Y-coordinate of the joystick, -100 to 100.
 */
void joystick1_onChange(int16_t x, int16_t y) {
  // Implement your custom actions here.
  // For example, you can control a motor or a servo based on the joystick's position.
  // The joystick's X and Y values range from -100 to 100.
  Serial.print("Joystick 1 X: ");
  Serial.print(x);
  Serial.print(" Y: ");
  Serial.println(y);
}

/**
 * @brief Callback for joystick change.
 */
void joystick2_onChange(int16_t x, int16_t y) {
  // Implement your custom actions here.
  Serial.print("Joystick 2 X: ");
  Serial.print(x);
  Serial.print(" Y: ");
  Serial.println(y);
}

void addJoystick1() {
  // Configure and add the joystick
  joystick1.x = 50;
  joystick1.y = 80;
  joystick1.dimSize = 200;  //width of joystick = height of joystick = 200
  joystick1.springed = true;
  joystick1.cmdId = BIND_ADD_OR_REFRESH_CMD;
  joystick1.setCallback(joystick1_onChange);
  bind.sync(joystick1);
}

void addJoystick2(int16_t height) {
  // Configure and add the joystick
  joystick2.x = height - 200;  // placed at the end of screen.
  joystick2.y = 80;
  joystick2.dimSize = 200;  //width of joystick = height of joystick = 200
  joystick2.springed = true;
  joystick2.cmdId = BIND_ADD_OR_REFRESH_CMD;
  joystick2.setCallback(joystick2_onChange);
  bind.sync(joystick2);
}

void onConnection(int16_t width, int16_t height) {
  // Rotate the creen for better exprince and more space.
  BindCanvasSettings canvasSettings;
  canvasSettings.screenOrientation = SCREEN_ORIENTATION_LANDSCAPE;
  canvasSettings.backColor = BLACK; // Or use RGB(R:0-255, G:0-255, B:0-255). For example RGB(100,255,40);
  bind.sync(canvasSettings);

  addJoystick1();
  addJoystick2(height);
}

void setup() {
  Serial.begin(115200);

  // Start WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  bindUdp.begin("YOUR_DEVICE_NAME", bind);
	bind.init(bindUdp, onConnection);
}

void loop() {
  delay(10);
}
