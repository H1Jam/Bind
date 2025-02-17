// Atention: For Raspberry Pi Pico W, this library needs Bluetooth enabled.
// Go to 'Tools->IP/Bluetooth Stack' menu in the IDE and select 'x + Bluetooth'.
#include "Bind.h"
#include <SerialBT.h>

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
  screenConfig();          // Configure the screen settings
  addJoystickLeft();       // Add the left joystick to the BindCanvas
  addJoystickRight(height);      // Add the right joystick to the BindCanvas
  addSpeedGauge(height);         // Add a speed gauge to the BindCanvas
  addAttitudeIndicator(height);  // Add an attitude indicator to the BindCanvas
  addHeadingIndicator(height);   // Add a heading indicator to the BindCanvas
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
  setAttitudeIndicator(x * 0.45f, y * 0.2f);
}

/**
 * @brief Callback for joystick change.
 */
void joystickLeft_onChange(int16_t x, int16_t y) {
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
  joystickRight.setCallback(joystickRight_onChange);
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
  joystickLeft.setCallback(joystickLeft_onChange);
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

  SerialBT.begin();
  bind.init(SerialBT, onConnection);
}

void loop() {
  // Synchronize Bind UI Events (Not required on ESP32 when using BindOverBLE or BindOverWifi)
  // Callin bind.sync() regularly is crucial to handle of user inputs and touch events.
  // It's recommended to call bind.sync() a couple of times per second, but the faster, the better!
  bind.sync();
  delay(5);
}
