//We only use SoftwareSerial for AVR Arduinos or ESP8266 library.
#if defined(__AVR__) || defined(ESP8266)
#include <SoftwareSerial.h>
#endif

#include "Bind.h"

// Note: Adjust the pins to match your Bluetooth module's configuration.
// We may use SoftwareSerial for AVR Arduinos or ESP8266.
#ifdef __AVR__
SoftwareSerial btSerial(4, 3);  // For AVR Arduinos like Pro Mini or Mega: RX: pin 4, TX: pin 3
#elif defined(ESP8266)
SoftwareSerial btSerial(D1, D2);  // For ESP8266: RX: pin D1, TX: pin D2
#elif defined(ESP32)
#define btSerial Serial2  // For ESP32 we use Serial2.
#elif defined(ARDUINO_ARCH_RP2040)
#define btSerial Serial1  // For RP2040(Raspberry Pi Pico): Use serial1 RX: pin 2, TX: pin 1
#else
SoftwareSerial btSerial(4, 3);  // Modify this line, if your board is neither above.
#endif

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
  Serial.println("Screen setup started!");
  Serial.print(w);
  Serial.print(" ");
  Serial.println(h);
  addChart();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  // Initialize the Bind object and specify the communication method (btSerial) and callback function (onConnection).
  bind.init(btSerial, onConnection);

  // Note: Adjust the baud rate to match your Bluetooth module's configuration.
  btSerial.begin(57600);
}

void loop() {
  // Regularly synchronize Bind UI events to receive events.
  bind.sync();
  delay(2);
  counter++;
  if (counter > 50) {
    counter = 0;
    send_Dummy_SinWave_Chartdata();  // Send sin wave data to update the chart
  }
}
