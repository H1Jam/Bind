#include "Bind.h"
#include "BindUtil/BindOverBLE.h"  // For BLE
// If you want to use Bluetooth Classic (which is faster), uncomment the
// following two lines. However, please note that Bluetooth Classic is not
// compatible with ESP32-C3 or ESP32-S3 models (BLE only). 
//#include "BluetoothSerial.h"
//BluetoothSerial SerialBT;

Bind bind;
BindColorPicker colorPicker1;

/**
 * @brief colorPicker1's Callback
 */
void colorPicker1_changed(uint8_t red, uint8_t green, uint8_t blue) {
  Serial.print("ColorPicker has been changed: r:");
  Serial.print(red);
  Serial.print("\tg:");
  Serial.print(green);
  Serial.print("\tb:");
  Serial.println(blue);
}

void addColorPicker() {
  colorPicker1.x =
      50;  /// The x-coordinate position of the color picker on the screen.
  colorPicker1.y =
      100;  /// The y-coordinate position of the color picker on the screen.
  colorPicker1.dimSize = 200;  /// The dimensions (size) of the color picker.
  colorPicker1.red = 160;    /// The initial value for the red component of the
                             /// selected color (0-255).
  colorPicker1.green = 190;  /// The initial value for the green component of
                             /// the selected color (0-255).
  colorPicker1.blue = 220;   /// The initial value for the blue component of the
                             /// selected color (0-255).
  colorPicker1.cmdId =
      BIND_ADD_OR_REFRESH_CMD;  /// Command identifier to add or refresh the
                                /// color picker.
  bind.sync(colorPicker1);
}

/**
 * @brief Connection Callback for BindCanvas.
 */
void onConnection(int16_t w, int16_t h) {
  Serial.println("Screen setup started!");
  addColorPicker();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  // Initialize the Bind object and specify the communication method (SerialBT)
  // and callback function (onConnection).
  BleStream* SerialBT = ble_init(bind, "BindOnESP32_ble"); // Only when using BLE! otherwise comment the line.
  //SerialBT.begin("BindOnESP32"); // Uncomment For Bluetooth Classic
  bind.init(SerialBT, onConnection);
  // Note: It was SerialBT here, but it could be any serial port, including
  // hardware and software serial.

  // Connect the callback functions with the Bind objects.
  bind.join(colorPicker1, colorPicker1_changed);
}

void loop() {
  // bind.sync(); // Uncomment For Bluetooth Classic
  // For BLE, no need to periodically call bind.sync(); it's already handled by the ESP32 BLE service
  delay(10);
}
