// Atention: For Raspberry Pi Pico W, this library needs Bluetooth enabled.
// Go to 'Tools->IP/Bluetooth Stack' menu in the IDE and select 'x + Bluetooth'.
#include "Bind.h"
#include <SerialBT.h>

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
  textLabel1.setLabel("Hello Android!");
  textLabel1.color = WHITE;
  textLabel1.fontSize = 28;
  textLabel1.cmdId = BIND_ADD_OR_REFRESH_CMD;
  bind.sync(textLabel1);

  textLabel2.x = 20;
  textLabel2.y = 230;
  textLabel2.setLabel("Second caption");
  textLabel2.color = YELLOW;
  textLabel2.fontSize = 18;
  textLabel2.cmdId = BIND_ADD_OR_REFRESH_CMD;
  bind.sync(textLabel2);
}

/**
 * @brief Screen Setup Callback for BindCanvas.
 *
 * This callback function is automatically invoked by BindCanvas upon establishing a connection.
 * It plays a crucial role in configuring the screen and ensuring that all screen objects are
 * synchronized properly. You will receive two parameters: 'width' for screen width and 'height' for screen height
 * in density-independent pixels (dp). These values allow you to maintain consistent object positioning
 * and size across various devices with different screen dimensions.
 *
 * Note: You do not need to manually call this function; it is automatically triggered by BindCanvas
 * upon connection.
 * Note: For more information about density-independent pixels (dp) visit:
 *                 https://en.wikipedia.org/wiki/Device-independent_pixel
 *
 * @param width The width of the screen in dp (Density-Independent Pixels).
 * @param height The height of the screen in dp (Density-Independent Pixels).
 */
void onConnection(int16_t width, int16_t height) {
  addtTextlabel();
}

void setup() {
  Serial.begin(115200);

  // Initialize the Bind object and specify the communication method (SerialBT) and callback function (onConnection).
  SerialBT.begin();
	bind.init(SerialBT, onConnection);
}

void loop() {
  // Synchronize Bind UI Events (Not required on ESP32 when using BindOverBLE or BindOverWifi)
  // Callin bind.sync() regularly is crucial to handle of user inputs and touch events.
  // It's recommended to call bind.sync() a couple of times per second, but the faster, the better!
  bind.sync();

  // This delay is not an essential part of the code but is included here to simulate a brief pause.
  delay(10);
  // Update the text label:
  counter++;
  if (counter > 100) {
    counter = 0;
    snprintf(buffer, 10, "%d", millis());
    textLabel2.setLabel(buffer);
    textLabel2.cmdId = BIND_DATA_ONLY_CMD;
    bind.sync(textLabel2);
  }
}
