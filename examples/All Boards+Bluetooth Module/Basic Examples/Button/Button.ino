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
#define btSerial Serial1 // For RP2040(Raspberry Pi Pico): Use serial1 RX: pin 2, TX: pin 3
#else
SoftwareSerial btSerial(4, 3); // Modify this line, if your board is neither above.
#endif

Bind bind;
BindButton buttonON;
BindButton buttonOFF;

/**
 * @brief Callback for Button 1 Press Event
 *
 * This function is automatically triggered when Button 1 is pressed on the screen.
 * It allows you to define specific actions to perform when the button is pressed.
 * To link this callback function with the Bind object, use the following syntax (in the Setup()):
 * `bind.join(your_button_object, buttonON_pressed);`
 * Make sure to include the '&' symbols as they indicate pointers to the function and object.
 * @note Ensure you call "bind.sync();" in the main loop to receive button press events.
 */
void buttonON_pressed() {
  Serial.println("ON has been pressed!");

  // Implement your custom actions here:
  digitalWrite(LED_BUILTIN, HIGH);

  // Add more actions as needed.
}

/**
 * @brief Callback for Button 1 Press Event
 */
void buttonOFF_pressed() {
  // See buttonON_pressed descripotions!
  Serial.println("OFF has been pressed!");
  digitalWrite(LED_BUILTIN, LOW);

  // Add more actions as needed.
}

/**
 * @brief Adds Button 1 to the BindCanvas
 *
 * This function adds (or refreshes, if already exist) Button 1 on the BindCanvas screen.
 * It synchronizes the Button's properties with the BindCanvas to display it correctly.
 * You can customize the Button's position, size, text, and more.
 * @attention a button object need the calback function as well. See the buttonON_pressed()
 * function.
 * @note Ensure you call "bind.sync();" in the main loop to receive button press events.
 */
void addbuttonON() {
  // Syncing Button 1:
  // Set the Button's position on the screen.
  // Tip: You can use the grid view mode in BindCanvas app to determine the x and y coordinates
  // and replace these numbers with the grid values for precise positioning.
  buttonON.x = 30;
  buttonON.y = 150;
  // Set the Button's text label.
  buttonON.setlabel("ON");     // button label
  buttonON.fontSize = 23;      // The dimensions(width and height) of the Button on the screen are determined relative to the Font size.
  buttonON.textColor = BLACK;  // Text color
  buttonON.backColor = GREEN;  // button color
  // Specify the command to either add the object to the BindCanvas or refresh the existing one.
  buttonON.cmdId = BIND_ADD_OR_REFRESH_CMD;
  // Synchronize the buttonON object with BindCanvas.
  bind.sync(buttonON);
}

void addbuttonOFF() {
  // Syncing Button 2:
  // See addbuttonON descripotions!
  buttonOFF.x = 30;
  buttonOFF.y = 200;
  // Set the Button's text label.
  buttonOFF.setlabel("OFF");     // button label
  buttonOFF.fontSize = 23;       // The dimensions(width and height) of the Button on the screen are determined relative to the Font size.
  buttonOFF.textColor = BLACK;   // Text color
  buttonOFF.backColor = YELLOW;  // button color
  // Specify the command to either add the object to the BindCanvas or refresh the existing one.
  buttonOFF.cmdId = BIND_ADD_OR_REFRESH_CMD;
  // Synchronize the buttonON object with BindCanvas.
  bind.sync(buttonOFF);
}

void onConnection(int16_t w, int16_t h) {
  Serial.println("Screen setup started!");
  addbuttonON();
  addbuttonOFF();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  // Note: Adjust the baud rate to match your Bluetooth module's configuration.
  btSerial.begin(57600);
  // Initialize the Bind object and specify the communication method (swSerial) and callback function (onConnection).
  bind.init(btSerial, onConnection);
  // Note: We used Software Serial here, but it could be any serial port, including hardware and software serial.

  // Connect the callback functions with the Bind objects.
  bind.join(buttonON, buttonON_pressed);
  bind.join(buttonOFF, buttonOFF_pressed);

}

void loop() {
  // Regularly synchronize Bind UI events to receive button press events.
  bind.sync();

  // This delay is not an essential part of the code
  // but is included here to simulate the other work you may want to do.
  delay(10);
}
