#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;

Bind bind;
BindGaugeCompact speedGauge;

const int analogInPin = 15;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;
int outputValue = 0;
int counter = 0;

/**
 * @brief Screen Setup Callback for BindCanvas.
 */
void onConnection(int16_t width, int16_t height) {
  Serial.println("Screen setup started!");
  Serial.print("Screen setup started! ");
  Serial.print(width);
  Serial.print(":");
  Serial.println(height);
  screenConfig();  // Configure the screen settings
  addSpeedGauge(height);  // Add a speed gauge to the BindCanvas
  Serial.println("Screen setup done!");
}

/**
 * @brief Configure the screen settings
 */
void screenConfig() {
  // Rotate the creen for better exprince and more space.
  BindCanvasSettings canvasSettings;
  canvasSettings.screenOrientation = SCREEN_ORIENTATION_PORTRAIT;
  canvasSettings.backColor = RGB(41, 49, 52);
  bind.sync(canvasSettings);
}

/**
 * @brief Add the speed gauge to the BindCanvas
 */
void addSpeedGauge(int16_t screenHeight) {
  //We want to put the center of SpeedGauge on the center of the screen. Therefore:
  speedGauge.x = 10;  // 100 is dimSize/2
  speedGauge.y = 80;
  speedGauge.dimSize = 200;  // For BindGaugeCompact, dimSize = height = width
  speedGauge.value = 0;
  speedGauge.maxValue = 200.0f;
  speedGauge.drawArc = 1;
  speedGauge.arcGreenMaxVal = 100.0f;
  speedGauge.arcYellowMaxVal = 150.0f;
  speedGauge.arcRedMaxVal = 180.0f;
  speedGauge.setlabel("Speed Km/h");
  speedGauge.cmdId = BIND_ADD_OR_REFRESH_CMD;
  bind.sync(speedGauge);
}

/**
 * @brief Set the value for the Speed Gauge.
 *
 * @param value The speed value to be displayed on the Speed Gauge.
 */
void setSpeedGauge(float value) {
  speedGauge.value = value;
  speedGauge.cmdId = BIND_DATA_ONLY_CMD;
  if (bind.isReady()){
    bind.sync(speedGauge);
  }
}

void setup() {
  Serial.begin(115200);
  analogReadResolution(10);

  String devName = "BindOnESP32";
  SerialBT.begin(devName);

  bind.init(SerialBT, onConnection);

  Serial.println("The bluetooth device started, now you can pair the phone with bluetooth!");
  Serial.println("devName:");
  Serial.println(devName);
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
  syncPotentiometer();
  delay(10);
}

void syncPotentiometer() {
  counter++;
  if (counter > 10) {
    counter =0;
    sensorValue = analogRead(analogInPin);
    outputValue = map(sensorValue, 0, 1023, 0, 180);
    setSpeedGauge(outputValue);
  }
}
