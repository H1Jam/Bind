#include <WiFi.h>
#include "Bind.h"
#include "BindUtil/BindOverWifi.h"
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
UDPStream bindUdp;

Bind bind;
BindSwitch switch1;
BindSwitch switch2;

const int ledPin = 2;

/**
 * @brief Callback for Switch 1 Value Change
 *
 * This function is automatically triggered when Switch 1's value changes on the screen.
 * It receives a boolean parameter, 'state,' representing the new state of Switch 1 (ON or OFF).
 * You can define specific actions based on this state to respond to Switch changes.
 * To link this callback function with the Bind object, use the following syntax (in the Setup()):
 * `bind.join(your_switch_object, switch1_changed);`
 * Make sure to include the '&' symbols as they indicate pointers to the function and object.
 *
 * @param state The new state of Switch 1 (true for ON, false for OFF).
 */
void switch1_changed(bool state) {
  // Implement your custom actions here:
  if (state) {
    digitalWrite(ledPin, HIGH); // Turn on the LED
    switch1.setlabel("ON");
  } else {
    digitalWrite(ledPin, LOW); // Turn off the LED
    switch1.setlabel("OFF");
  }
  bind.sync(switch1);
}

/**
 * @brief Callback for Switch 2 Value Change
 */
void switch2_changed(bool state) {
  if (state){
    switch2.setlabel("Enable");
  }else{
    switch2.setlabel("Disable");
  }
  switch2.cmdId = BIND_DATA_ONLY_CMD;
  bind.sync(switch2);
}

/**
 * @brief Adds Switches to the BindCanvas
 *
 * This function adds (or refreshes, if already exist) Switches on the BindCanvas screen. It synchronizes
 * the Switches' properties with their respective BindCanvas to display them correctly.
 * You can customize the Switches' position, size, and initial state.
 */
void addSwitches() {
  // Syncing the first Switch:
  // Set the Switch's position on the screen.
  // Tip: You can use the grid view mode in BindCanvas app to determine the x and y coordinates
  // and replace these numbers with the grid values for precise positioning.
  switch1.x = 30;
  switch1.y = 100;
  switch1.fontSize = 16;
  switch1.textColor = YELLOW;
  switch1.setlabel("OFF");
  // Set the initial state of the Switch (true for ON, false for OFF).
  switch1.switchValue = false;
  // Specify the command to either add the object to the BindCanvas screen or refresh the existing one.
  switch1.cmdId = BIND_ADD_OR_REFRESH_CMD;
  // Synchronize the switch1 object with BindCanvas.
  bind.sync(switch1);

  // Syncing the second Switch:
  switch2.x = 30;
  switch2.y = 150;
  switch2.fontSize = 16;
  switch2.textColor = YELLOW;
  switch2.setlabel("Enable");
  switch2.cmdId = BIND_ADD_OR_REFRESH_CMD;
  switch2.switchValue = true;
  // Synchronize the switch2 object with BindCanvas.
  bind.sync(switch2);
}

/**
 * @brief Screen Setup Callback for BindCanvas.
 *
 * This callback function is automatically invoked by BindCanvas upon establishing a connection.
 * It plays a crucial role in configuring the screen and ensuring that all screen objects are
 * synchronized properly. You will receive two parameters: 'w' for screen width and 'h' for screen height
 * in density-independent pixels (dp). These values allow you to maintain consistent object positioning
 * and size across various devices with different screen dimensions.
 *
 * Note: You do not need to manually call this function; it is automatically triggered by BindCanvas
 * upon connection.
 * Note: For more information about density-independent pixels (dp) visit:
 *                 https://en.wikipedia.org/wiki/Device-independent_pixel
 *
 * @param w The width of the screen in dp (Density-Independent Pixels).
 * @param h The height of the screen in dp (Density-Independent Pixels).
 */
void onConnection(int16_t w, int16_t h) {
  addSwitches();
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

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

  // Connect the callback functions with the Bind objects.
  bind.join(switch1, switch1_changed);
  bind.join(switch2, switch2_changed);
  // Please ensure that you include the '&' symbols in the function parameters; these are pointers.

}

void loop() {
  // Regularly synchronize Bind UI events

  // This delay is not an essential part of the code but is included here to simulate a brief pause.
  delay(10);
}


