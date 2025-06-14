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
BindChart chart1;

int counter = 0;
int X = 0;
float sinX = 0;

/**
 * @brief Sends Dummy Sine Wave Chart Data
 *
 * This function generates a dummy sine wave data point and sends it to a BindChart object.
 * The data point is synchronized with a BindChart object using the 'bind.sync' function.
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
 * This function configures and adds (or refreshes if already exists) a chart object to the BindCanvas screen.
 * After configuring the chart, it is synchronized with the BindCanvas using 'bind.sync'.
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
  addChart();
}

void setup() {
  Serial.begin(115200);
  // Initialize the Bind object and specify the communication method (bindUdp) and callback function (onConnection).
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
  delay(2);
  counter++;
  if (counter > 50) {
    counter = 0;
    send_Dummy_SinWave_Chartdata(); // Send sin wave data to update the chart
  }
}
