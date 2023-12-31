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
BindButton button1;
BindButton button2;

/**
 * @brief Callback for Button 1 Press Event
 *
 * This function is automatically triggered when Button 1 is pressed on the screen.
 * It allows you to define specific actions to perform when the button is pressed.
 * To link this callback function with the Bind object, use the following syntax (in the Setup()):
 * `bind.join(your_button_object, button1_pressed);`
 * Make sure to include the '&' symbols as they indicate pointers to the function and object.
 * @note Ensure you call "bind.sync();" in the main loop to receive button press events.
 */
void button1_pressed() {
  Serial.println("Button 1 has been pressed!");

  // Implement your custom actions here:
  digitalWrite(LED_BUILTIN, HIGH);

  // Add more actions as needed.
}

/**
 * @brief Callback for Button 1 Press Event
 */
void button2_pressed() {
  // See button1_pressed descripotions!
  Serial.println("Button 2 has been pressed!");
  digitalWrite(LED_BUILTIN, LOW);

  // Add more actions as needed.
}

/**
 * @brief Adds Button 1 to the BindCanvas
 *
 * This function adds (or refreshes, if already exist) Button 1 on the BindCanvas screen.
 * It synchronizes the Button's properties with the BindCanvas to display it correctly.
 * You can customize the Button's position, size, text, and more.
 * @attention a button object need the calback function as well. See the button1_pressed()
 * function.
 * @note Ensure you call "bind.sync();" in the main loop to receive button press events.
 */
void addButton1() {
  // Syncing Button 1:
  // Set the Button's position on the screen.
  // Tip: You can use the grid view mode in BindCanvas app to determine the x and y coordinates
  // and replace these numbers with the grid values for precise positioning.
  button1.x = 30;
  button1.y = 150;
  // Set the Button's text label.
  button1.setlabel("ON");     // button label
  button1.fontSize = 23;      // The dimensions(width and height) of the Button on the screen are determined relative to the Font size.
  button1.textColor = BLACK;  // Text color
  button1.backColor = GREEN;  // button color
  // Specify the command to either add the object to the BindCanvas or refresh the existing one.
  button1.cmdId = BIND_ADD_OR_REFRESH_CMD;
  // Synchronize the button1 object with BindCanvas.
  bind.sync(button1);
}

void addButton2() {
  // Syncing Button 2:
  // See addButton1 descripotions!
  button2.x = 30;
  button2.y = 200;
  // Set the Button's text label.
  button2.setlabel("OFF");     // button label
  button2.fontSize = 23;       // The dimensions(width and height) of the Button on the screen are determined relative to the Font size.
  button2.textColor = BLACK;   // Text color
  button2.backColor = YELLOW;  // button color
  // Specify the command to either add the object to the BindCanvas or refresh the existing one.
  button2.cmdId = BIND_ADD_OR_REFRESH_CMD;
  // Synchronize the button1 object with BindCanvas.
  bind.sync(button2);
}

void onConnection(int16_t w, int16_t h) {
  Serial.println("Screen setup started!");
  addButton1();
  addButton2();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  
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
  // Note: It was SerialBT here, but it could be any serial port, including hardware and software serial.

  // Connect the callback functions with the Bind objects.
  bind.join(button1, button1_pressed);
  bind.join(button2, button2_pressed);

}

void loop() {
  // Regularly synchronize Bind UI events to receive button press events.
  bind.sync();

  // This delay is not an essential part of the code
  // but is included here to simulate the other work you may want to do.
  delay(10);
}
