#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
Bind bind;
BindChart chart1;

int counter = 0;
int X = 0;
int sinX = 0;

void sendDummySinWaveChartdata() {
  X += 10;
  X %= 360;
  sinX = sin(sinX * PI / 180.0f) * 30 bind.sync(sinX, &chart1);
}

void addChart() {
  chart1.x = 10;
  chart1.y = 10;
  chart1.cmdId = BIND_ADD_OR_REFRESH_CMD;
  chart1.width = 300;
  chart1.height = 140;
  chart1.maxY = 10;
  chart1.minY = -10;
  chart1.maxX = 20;
  chart1.autoSize = true;
  chart1.color = YELLOW;
  bind.sync(&chart1);
}

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
  // Initialize the Bind object and specify the communication method (SerialBT) and callback function (onConnection).
  bind.init(&SerialBT, &onConnection);

  String devName = "ESP32testB";
  SerialBT.begin(devName);
  Serial.println("The bluetooth device started, now you can pair the phone with bluetooth!");
  Serial.println("devName:");
  Serial.println(devName);
}

void loop() {
  bind.sync();
  delay(2);
  counter++;
  if (counter > 50) {
    counter = 0;
    sendDummyChartdata();
  }
}
