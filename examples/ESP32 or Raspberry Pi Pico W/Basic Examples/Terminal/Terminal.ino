//Atention: For Raspberry Pi Pico W, this library needs Bluetooth enabled.  
//Use the 'Tools->IP/Bluetooth Stack' menu in the IDE to enable it (x + Bluetooth).

#if defined(ESP32)
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
#elif defined(ARDUINO_ARCH_RP2040)
#include <SerialBT.h>
#endif

#include "Bind.hpp"


Bind bind;
BindTerminal bindTerminal;

int counter = 0;
int counter2 = 0;
char buffer[15];

void addScreenTerminal() {
  bindTerminal.x = 10;
  bindTerminal.y = 10;
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
  Serial.println("Screen setup started!");
  addScreenTerminal();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  
#if defined(ESP32)
  String devName = "BindOnESP32";
  SerialBT.begin(devName);
  Serial.println("The Bluetooth device started. Pair your phone with Bluetooth!");
  Serial.println("Device Name:");
  Serial.println(devName);
#elif defined(ARDUINO_ARCH_RP2040)
  SerialBT.begin();
#endif

  // Initialize the Bind object and specify the communication method (SerialBT) and callback function (onConnection).
  bind.init(SerialBT, onConnection);

}

void loop() {
  // Regularly synchronize Bind UI events to receive events.
  bind.sync();
  delay(10);
  counter++;
  if (counter > 100) {
    counter = 0;
    snprintf(buffer, 15, "Time: %lu", millis());
    updateScreenTerminalData(buffer);
    counter2++;
    if (counter2 >= 5) {
      updateScreenTerminalDataBigger("Print with diffrent color!");
      counter2 = 0;
    }
  }
}
