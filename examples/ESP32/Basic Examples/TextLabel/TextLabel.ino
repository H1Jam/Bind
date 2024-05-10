#include "Bind.hpp"
#include "BindUtil/esp32ble.h"

Bind bind;
BindTextLabel textLabel1;
BindTextLabel textLabel2;

int counter = 0;
char buffer[10];

/**
 * Add the TextViews to the BindCanvas.
 */
void addtTextlabel() {
  textLabel1.x = 20;
  textLabel1.y = 200;
  textLabel1.setlabel("Hello Android!");
  textLabel1.color = WHITE;
  textLabel1.fontSize = 28;
  textLabel1.cmdId = BIND_ADD_OR_REFRESH_CMD;
  bind.sync(textLabel1);

  textLabel2.x = 20;
  textLabel2.y = 230;
  textLabel2.setlabel("Second caption");
  textLabel2.color = YELLOW;
  textLabel2.fontSize = 18;
  textLabel2.cmdId = BIND_ADD_OR_REFRESH_CMD;
  bind.sync(textLabel2);
}

/**
 * @brief Screen Setup Callback for BindCanvas.
 *
 * This callback function is automatically invoked by BindCanvas upon
 * establishing a connection. It plays a crucial role in configuring the screen
 * and ensuring that all screen objects are synchronized properly. You will
 * receive two parameters: 'width' for screen width and 'height' for screen
 * height in density-independent pixels (dp). These values allow you to maintain
 * consistent object positioning and size across various devices with different
 * screen dimensions.
 *
 * Note: You do not need to manually call this function; it is automatically
 * triggered by BindCanvas upon connection. Note: For more information about
 * density-independent pixels (dp) visit:
 *                 https://en.wikipedia.org/wiki/Device-independent_pixel
 *
 * @param width The width of the screen in dp (Density-Independent Pixels).
 * @param height The height of the screen in dp (Density-Independent Pixels).
 */
void onConnection(int16_t width, int16_t height) {
  Serial.println("Screen setup started!");
  addtTextlabel();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  // Initialize the Bind object and specify the communication method (SerialBT)
  // and callback function (onConnection).
  BleStream* SerialBT = ble_init(bind, "BindOnESP32_ble");
  bind.init(SerialBT, onConnection);
  // Note: It was SerialBT here, but it could be any serial port, including
  // hardware and software serial.
}

void loop() {
  // No need to periodically call bind.sync(); it's already handled by the ESP32 BLE service 
  // This delay is not an essential part of the code but is included here to
  // simulate a brief pause.
  delay(10);
  // Update the text label:
  counter++;
  if (counter > 100) {
    counter = 0;
    snprintf(buffer, 10, "%d", millis());
    textLabel2.setlabel(buffer);
    textLabel2.cmdId = BIND_DATA_ONLY_CMD;
    bind.sync(textLabel2);
  }
}
