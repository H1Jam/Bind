//We only use SoftwareSerial for AVR Arduinos or ESP8266 library.
#if defined(__AVR__) || defined(ESP8266)
#include <SoftwareSerial.h>
#endif

#include "Bind.hpp"

// Note: Adjust the pins to match your Bluetooth module's configuration.
// We may use SoftwareSerial for AVR Arduinos or ESP8266.
#ifdef __AVR__
SoftwareSerial btSerial(4, 3); // For AVR Arduinos like Pro Mini or Mega: RX: pin 4, TX: pin 3
#elif defined(ESP8266)
SoftwareSerial btSerial(D1, D2); // For ESP8266: RX: pin D1, TX: pin D2
#elif defined(ESP32) 
#define btSerial Serial2 // For ESP32 we use Serial2.
#elif defined(ARDUINO_ARCH_RP2040)
#define btSerial Serial1 // For RP2040(Raspberry Pi Pico): Use serial1 RX: pin 2, TX: pin 1
#else
SoftwareSerial btSerial(4, 3); // Modify this line, if your board is neither above.
#endif

// If the board doesn't have built-in LED, assign an external LED here (if wish to use it):
#ifndef LED_BUILTIN
#define LED_BUILTIN 10
#endif  

Bind bind;
BindSwitch switch1;
BindSwitch switch2;

/**
 * @brief Callback for Switch 1 Value Change
 *
 * This function is automatically triggered when Switch 1's value changes on the screen.
 * It receives a boolean parameter, 'state,' representing the new state of Switch 1 (ON or OFF).
 * You can define specific actions based on this state to respond to Switch changes.
 * To link this callback function with the Bind object, use the following syntax (in the Setup()):
 * `bind.join(your_switch_object, switch1_changed);`
 * Make sure to include the '&' symbols as they indicate pointers to the function and object.
 * @note Ensure you call "bind.sync();" in the main loop to get the callback and change events.
 *
 * @param state The new state of Switch 1 (true for ON, false for OFF).
 */
void switch1_changed(bool state) {
  Serial.print("Switch 1 state has changed to: ");
  Serial.println(state);
  // Implement your custom actions here:
  if (state) {
    digitalWrite(LED_BUILTIN, HIGH); // Turn on the LED
    switch1.setlabel("ON");
  } else {
    digitalWrite(LED_BUILTIN, LOW); // Turn off the LED
    switch1.setlabel("OFF");
  }
  bind.sync(switch1);
}

/**
 * @brief Callback for Switch 2 Value Change
 */
void switch2_changed(bool state) {
  Serial.print("Switch 2 state has changed to: ");
  Serial.println(state);
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
 * @note Ensure you call "bind.sync();" in the main loop to get the callback and change events.
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
  Serial.println("Screen setup started!");
  addSwitches();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  // Note: Adjust the baud rate to match your Bluetooth module's configuration.
  btSerial.begin(57600);

  // Initialize the Bind object and specify the communication method (btSerial) and callback function (onConnection).
  bind.init(btSerial, onConnection);
  // Note: It was swSerial here, but it could be any serial port, including hardware and software serial.

  // Connect the callback functions with the Bind objects.
  bind.join(switch1, switch1_changed);
  bind.join(switch2, switch2_changed);
  // Please ensure that you include the '&' symbols in the function parameters; these are pointers.

  Serial.println("The Bluetooth device started; now you can pair the phone with Bluetooth!");
}

void loop() {
  // Regularly synchronize Bind UI events
  bind.sync();

  // This delay is not an essential part of the code but is included here to simulate a brief pause.
  delay(10);
}


