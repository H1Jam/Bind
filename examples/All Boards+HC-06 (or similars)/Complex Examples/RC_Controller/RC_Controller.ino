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
BindJoystick joystickRight;
BindJoystick joystickLeft;
BindGaugeCompact speedGauge;
BindAttitudeIndicator attitudeIndicator;
BindHeadingIndicator headingIndicator;

/**
 * @brief Screen Setup Callback for BindCanvas.
 */
void onConnection(int16_t width, int16_t height) {
  Serial.println("Screen setup started!");
  Serial.print("Screen setup started! ");
  Serial.print(width);
  Serial.print(":");
  Serial.println(height);

  screenConfig();          // Configure the screen settings
  addJoystickLeft();       // Add the left joystick to the BindCanvas
  addJoystickRight(height);      // Add the right joystick to the BindCanvas
  addSpeedGauge(height);         // Add a speed gauge to the BindCanvas
  addAttitudeIndicator(height);  // Add an attitude indicator to the BindCanvas
  addHeadingIndicator(height);   // Add a heading indicator to the BindCanvas

  Serial.println("Screen setup done!");
}

/**
 * @brief Configure the screen settings
 */
void screenConfig() {
  // Rotate the creen for better exprince and more space.
  BindCanvasSettings canvasSettings;
  canvasSettings.screenOrientation = SCREEN_ORIENTATION_LANDSCAPE;
  canvasSettings.backColor = RGB(41, 49, 52);
  bind.sync(canvasSettings);
}

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
void joystickRight_onChange(int16_t x, int16_t y) {
  Serial.print("joystickRight has been changed, x:");
  Serial.print(x);
  Serial.print(" y:");
  Serial.println(y);
  setAttitudeIndicator(x * 0.45f, y * 0.2f);
}

/**
 * @brief Callback for joystick change.
 */
void joystickLeft_onChange(int16_t x, int16_t y) {
  Serial.print("joystickLeft has been changed, x:");
  Serial.print(x);
  Serial.print(" y:");
  Serial.println(y);
  setSpeedGauge(y + 100);
  setHeadingIndicator(x);
}

/**
 * @brief Add the right joystick to the BindCanvas
 */
void addJoystickRight(int16_t screenHeight) {
  joystickRight.x = screenHeight- 200 - 20; // 200 = dimSize(the object width), 20 is fair clearance.
  joystickRight.y = 140;
  joystickRight.cmdId = BIND_ADD_OR_REFRESH_CMD;
  joystickRight.dimSize = 200; // For BindJoystick, dimSize = height = width
  bind.sync(joystickRight);
}

/**
 * @brief Add the left joystick to the BindCanvas
 */
void addJoystickLeft() {
  joystickLeft.x = 20;
  joystickLeft.y = 140;
  joystickLeft.cmdId = BIND_ADD_OR_REFRESH_CMD;
  joystickLeft.dimSize = 200; // For BindJoystick, dimSize = height = width
  bind.sync(joystickLeft);
}

/**
 * @brief Add the speed gauge to the BindCanvas
 */
void addSpeedGauge(int16_t screenHeight) {
  //We want to put the center of SpeedGauge on the center of the screen. Therefore:
  speedGauge.x = screenHeight/2 - 100; // 100 is dimSize/2
  speedGauge.y = 150;
  speedGauge.dimSize = 200; // For BindGaugeCompact, dimSize = height = width
  speedGauge.value = 0;
  speedGauge.maxValue = 200.0f;
  speedGauge.drawArc = 100;
  speedGauge.arcGreenMaxVal = 100.0f;
  speedGauge.arcYellowMaxVal = 150.0f;
  speedGauge.arcRedMaxVal = 180.0f;
  speedGauge.setlabel("Speed Km/h");
  speedGauge.cmdId = BIND_ADD_OR_REFRESH_CMD;
  bind.sync(speedGauge);
}

/**
 * @brief Add the attitude indicator to the BindCanvas
 */
void addAttitudeIndicator(int16_t screenHeight) {
  attitudeIndicator.x = screenHeight/2;
  attitudeIndicator.y = 5;
  attitudeIndicator.cmdId = BIND_ADD_OR_REFRESH_CMD;
  attitudeIndicator.roll = 0;
  attitudeIndicator.pitch = 0;
  attitudeIndicator.dimSize = 120; // For BindAttitudeIndicator, dimSize = height = width
  bind.sync(attitudeIndicator);
}

/**
 * @brief Add the heading indicator to the BindCanvas
 */
void addHeadingIndicator(int16_t screenHeight) {
  headingIndicator.x = screenHeight/2 - 120; // 120 = dimSize or width
  headingIndicator.y = 5;
  headingIndicator.cmdId = BIND_ADD_OR_REFRESH_CMD;
  headingIndicator.heading = 0;
  headingIndicator.dimSize = 120; // For BindHeadingIndicator, dimSize = height = width
  bind.sync(headingIndicator);
}

/**
 * @brief Set the heading value for the Heading Indicator.
 *
 * @param heading The heading angle in degrees.
 */
void setHeadingIndicator(float heading) {
  headingIndicator.cmdId = BIND_DATA_ONLY_CMD;
  headingIndicator.heading = heading;
  bind.sync(headingIndicator);
}

/**
 * @brief Set the roll and pitch values for the Attitude Indicator.
 *
 * @param roll  The roll angle in degrees.
 * @param pitch The pitch angle in degrees.
 */
void setAttitudeIndicator(float roll, float pitch) {
  attitudeIndicator.cmdId = BIND_DATA_ONLY_CMD;
  attitudeIndicator.roll = roll;
  attitudeIndicator.pitch = pitch;
  bind.sync(attitudeIndicator);
}

/**
 * @brief Set the value for the Speed Gauge.
 *
 * @param value The speed value to be displayed on the Speed Gauge.
 */
void setSpeedGauge(float value) {
  speedGauge.value = value;
  speedGauge.cmdId = BIND_DATA_ONLY_CMD;
  bind.sync(speedGauge);
}

void setup() {
  Serial.begin(115200);
  // Note: Adjust the baud rate to match your Bluetooth module's configuration.
  btSerial.begin(57600);

  bind.init(btSerial, onConnection);

  //Set the callbacks
  bind.join(joystickRight, joystickRight_onChange);
  bind.join(joystickLeft, joystickLeft_onChange);

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
  delay(5);
}
