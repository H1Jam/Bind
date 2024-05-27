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
#define btSerial Serial1 // For RP2040(Raspberry Pi Pico): Use serial2 RX: pin 2, TX: pin 1
#else
SoftwareSerial btSerial(4, 3); // Modify this line, if your board is neither above.
#endif

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
void setSpeedGaugeValue(float value) {
  speedGauge.value = value;
  speedGauge.cmdId = BIND_DATA_ONLY_CMD;
  if (bind.isReady()){
    bind.sync(speedGauge);
  }
}

void setup() {
  Serial.begin(115200);
// If you want to utilize the full resolution, 
// modify the value conversion in the syncPotentiometer() function.
// Set the resulotion to 10bit, so we get 0-1023 from analogRead.
#if defined(ESP32) || defined(ARDUINO_ARCH_RP2040)
  analogReadResolution(10);
#endif

  // Note: Adjust the baud rate to match your Bluetooth module's configuration.
  btSerial.begin(57600);

  bind.init(btSerial, onConnection);

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
    setSpeedGaugeValue(outputValue);
  }
}
