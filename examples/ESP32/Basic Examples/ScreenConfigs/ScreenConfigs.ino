#include "Bind.h"
#include "BindUtil/BindOverBLE.h"  // For BLE
// If you want to use Bluetooth Classic (which is faster), uncomment the
// following two lines. However, please note that Bluetooth Classic is not
// compatible with ESP32-C3 or ESP32-S3 models (BLE only).
//#include "BluetoothSerial.h" 
//BluetoothSerial SerialBT; 

Bind bind;
BindCanvasSettings canvasSettings;

void setScreenConfig() {
  // Configure screen settings

  // Screen orientation is unspecified, allowing the system to decide.
  // canvasSettings.screenOrientation = SCREEN_ORIENTATION_UNSPECIFIED;

  // Portrait mode: screen height > width.
  // canvasSettings.screenOrientation = SCREEN_ORIENTATION_PORTRAIT;

  // Landscape mode: screen width > height.
  canvasSettings.screenOrientation = SCREEN_ORIENTATION_LANDSCAPE;
  canvasSettings.backColor = BLACK;
  // Or use RGB(R:0-255, G:0-255, B0-255).
  // For example:
  // canvasSettings.backColor = RGB(100,255,40);
  bind.sync(canvasSettings);
}

void onConnection(int16_t width, int16_t height) {
  Serial.print("Screen setup started!");
  Serial.print(width);
  Serial.print("x");
  Serial.println(height);
  setScreenConfig();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  BleStream* SerialBT = ble_init(bind, "BindOnESP32_ble"); // Only when using BLE! otherwise comment the line.
  //SerialBT.begin("BindOnESP32"); // Uncomment For Bluetooth Classic
  bind.init(SerialBT, onConnection);
}

void loop() {
  // bind.sync(); // Uncomment For Bluetooth Classic
  // For BLE, no need to periodically call bind.sync(); it's already handled by the ESP32 BLE service
  delay(10);
}
