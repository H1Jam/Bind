// Atention: For Raspberry Pi Pico W, this library needs Bluetooth enabled.
// Go to 'Tools->IP/Bluetooth Stack' menu in the IDE and select 'x + Bluetooth'.
#include "Bind.h"
#include <SerialBT.h>

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
  SerialBT.begin();
	bind.init(SerialBT, onConnection);
  // Note: We used Serial here, but it could be any serial port, including hardware and software serial.
}

void loop() {
  // Regularly synchronize Bind UI events to receive events.
  // Synchronize Bind UI Events (Not required on ESP32 when using BindOverBLE or BindOverWifi)
  // Callin bind.sync() regularly is crucial to handle of user inputs and touch events.
  // It's recommended to call bind.sync() a couple of times per second, but the faster, the better!
  bind.sync();
  
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
