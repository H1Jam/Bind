//Atention: For Raspberry Pi Pico W, this library needs Bluetooth enabled.  
//Use the 'Tools->IP/Bluetooth Stack' menu in the IDE to enable it (x + Bluetooth).

#if defined(ESP32)
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
#elif defined(ARDUINO_ARCH_RP2040)
#include <SerialBT.h>
#endif

#include "Bind.hpp"

Bind bind;
BindJoystick joystick1;
BindJoystick joystick2;

/**
 * @brief Callback for joystick change.
 *
 * This function is triggered when the joystick's position changes. It receives
 * two parameters, 'x' and 'y,' representing the new X and Y coordinates of the joystick.
 * You can implement custom actions based on these coordinates.
 *
 * @param x The new X-coordinate of the joystick.
 * @param y The new Y-coordinate of the joystick.
 */
void joystick1_onChange(int16_t x, int16_t y) {
  Serial.print("joystick1 has been changed, x:");
  Serial.print(x);
  Serial.print(" y:");
  Serial.println(y);
}

/**
 * @brief Callback for joystick change.
 */
void joystick2_onChange(int16_t x, int16_t y) {
  Serial.print("joystick2 has been changed, x:");
  Serial.print(x);
  Serial.print(" y:");
  Serial.println(y);
}

void addJoystick1() {
  // Configure and add the joystick
  joystick1.x = 50;
  joystick1.y = 80;
  joystick1.dimSize = 200;  //width = height = 200
  joystick1.springed = true;
  joystick1.cmdId = BIND_ADD_OR_REFRESH_CMD;
  bind.sync(joystick1);
}

void addJoystick2(int16_t height) {
  // Configure and add the joystick
  joystick2.x = height - 200;  // placed at the end of screen.
  joystick2.y = 80;
  joystick2.dimSize = 200;  //width = height = 200
  joystick2.springed = true;
  joystick2.cmdId = BIND_ADD_OR_REFRESH_CMD;
  bind.sync(joystick2);
}

void onConnection(int16_t width, int16_t height) {
  Serial.println("Screen setup started! ");

  // Rotate the creen for better exprince and more space.
  BindCanvasSettings canvasSettings;
  canvasSettings.screenOrientation = SCREEN_ORIENTATION_LANDSCAPE;
  canvasSettings.backColor = BLACK; // Or use RGB(R:0-255, G:0-255, B0-255). For example RGB(100,255,40);
  bind.sync(canvasSettings);

  addJoystick1();
  addJoystick2(height);
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  
#if defined(ESP32)
  String devName = "BindOnESP32";
  SerialBT.begin(devName);
  Serial.println("The Bluetooth device started. Pair your phone with Bluetooth!");
  Serial.println("Device Name:");
  Serial.println(devName);
#elif defined(ARDUINO_ARCH_RP2040)
  SerialBT.begin();
#endif

  bind.init(SerialBT, onConnection);

  //Set the callbacks
  bind.join(joystick1, joystick1_onChange);
  bind.join(joystick2, joystick2_onChange);

}

void loop() {
  /**
 * Synchronize Bind UI Events
 *
 * To ensure proper handling of user inputs and touch events, it's crucial to call
 * this function regularly within your Arduino loop. Failing to do so may result
 * in missed events, such as button clicks or user interactions with your UI elements.
 * By calling `bind.sync()`, you maintain seamless communication between your Arduino
 * code and the Bind Framework.
 * It's recommended to call sync() a couple of times per second, but the faster, the better!
 * Aim for a rate above 20Hz for ideal performance.
  */
  bind.sync();
  delay(10);
}
