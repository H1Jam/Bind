#include "Bind.h"
#include "BindUtil/BindOverBLE.h"  // For BLE
// If you want to use Bluetooth Classic (which is faster), uncomment the
// following two lines. However, please note that Bluetooth Classic is not
// compatible with ESP32-C3 or ESP32-S3 models (BLE only). 
//#include "BluetoothSerial.h"
//BluetoothSerial SerialBT;

Bind bind;
BindChart chart1;

int counter = 0;
int X = 0;
float sinX = 0;

/**
 * @brief Sends Dummy Sine Wave Chart Data
 *
 * This function generates a dummy sine wave data point and sends it to a
 * BindChart object. The data point is synchronized with a BindChart object
 * using the 'bind.sync' function.
 */
void send_Dummy_SinWave_Chartdata() {
  X += 10;
  X %= 360;
  sinX = sin(X * PI / 180.0f) * 30;
  bind.sync(sinX, chart1);
}

/**
 * @brief Adds a Chart to the BindCanvas
 *
 * This function configures and adds (or refreshes if already exists) a chart
 * object to the BindCanvas screen. After configuring the chart, it is
 * synchronized with the BindCanvas using 'bind.sync'.
 */
void addChart() {
  chart1.x = 30;
  chart1.y = 70;
  chart1.cmdId = BIND_ADD_OR_REFRESH_CMD;
  chart1.width = 300;
  chart1.height = 140;
  chart1.maxY = 10;
  chart1.minY = -10;
  chart1.maxX = 20;
  chart1.autoSize = true;
  chart1.color = YELLOW;
  bind.sync(chart1);
}

/**
 * @brief Screen Setup Callback for BindCanvas.
 */
void onConnection(int16_t w, int16_t h) {
  Serial.println("Screen setup started!");
  Serial.print(w);
  Serial.print(" ");
  Serial.println(h);
  addChart();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  // Initialize the Bind object and specify the communication method (SerialBT)
  // and callback function (onConnection).
  BleStream* SerialBT = ble_init(bind, "BindOnESP32_ble"); // Only when using BLE! otherwise comment the line.
  //SerialBT.begin("BindOnESP32"); // Uncomment For Bluetooth Classic
  bind.init(SerialBT, onConnection);
}

void loop() {
  // bind.sync(); // Uncomment For Bluetooth Classic
  // For BLE, no need to periodically call bind.sync(); it's already handled by the ESP32 BLE service
  delay(2);
  counter++;
  if (counter > 50) {
    counter = 0;
    send_Dummy_SinWave_Chartdata();  // Send sin wave data to update the chart
  }
}
