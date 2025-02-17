#include <WiFi.h>
#include "Bind.h"
#include "BindUtil/BindOverWifi.h"
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
UDPStream bindUdp;

Bind bind;
BindTerminal bindTerminal;

int counter = 0;
int counter2 = 0;
char buffer[15];

void addScreenTerminal() {
  bindTerminal.x = 10;
  bindTerminal.y = 70;
  bindTerminal.cmdId = BIND_ADD_OR_REFRESH_CMD;
  bindTerminal.width = 300;
  bindTerminal.height = 200;
  bindTerminal.textSize = 10;
  bindTerminal.backColor = UBUNTU;
  bind.sync(bindTerminal);
}

void updateScreenTerminalData(const char *cstr) {
  bind.sync(cstr, GREEN, true, true, true, false, bindTerminal);
}

void updateScreenTerminalDataBigger(const char *cstr) {
  bind.sync(cstr, WHITE, true, true, true, false, bindTerminal);
}

void onConnection(int16_t w, int16_t h) {
  addScreenTerminal();
}

void setup() {
  Serial.begin(115200);
  // Initialize the Bind object and specify the communication method (swSerial) and callback function (onConnection).
  // Start WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  bindUdp.begin("YOUR_DEVICE_NAME", bind);
	bind.init(bindUdp, onConnection);
  // Note: We used Serial here, but it could be any serial port, including hardware and software serial.
}

void loop() {
  // Regularly synchronize Bind UI events to receive events.
  
  delay(10);
  counter++;
  if (counter > 100) {
    counter = 0;
    snprintf(buffer, 15, "Time: %d", millis());
    updateScreenTerminalData(buffer);
    counter2++;
    if (counter2 >= 5) {
      updateScreenTerminalDataBigger("Print with diffrent color!");
      counter2 = 0;
    }
  }
}
