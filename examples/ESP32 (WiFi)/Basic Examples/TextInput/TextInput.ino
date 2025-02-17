#include <WiFi.h>
#include "Bind.h"
#include "BindUtil/BindOverWifi.h"
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
UDPStream bindUdp;

Bind bind;
BindTextInput textInput1;
BindTextInput textInput2;

// if the LED_BUILTIN is not defined by the board, define it as pin 2
#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif

const int ledPin = LED_BUILTIN; // change this to the pin where your LED is connected.
unsigned long lastMs = 0;

// Atention: If you are using this Serial port for Bind,
// you should comment all Serial.print(...)/println(...) lines to avoid conflicts.

/**
 * @brief Callback for TextInput Value Change
 *
 * This function is automatically triggered when the text input's value changes on the screen.
 * It receives a string parameter, 'val,' representing the new value of the text input.
 * You can define specific actions based on this value to respond to text input changes.
 * To link this callback function with the Bind object, use the setCallback() function as follows:
 * `textInput1.setCallback(textInput1_changed);` before synchronizing the TextInput object with BindCanvas.
 *
 * @param val The new value of the text input.
 * @param length The length of the new value.
 */
void textInput1_changed(const char *val, uint8_t length) {
  // If using Serial Port as Bind stream, 
  // comment the following line with Serial.print/write to avoid errors.
  Serial.print("TextInput1 changed: [");
  Serial.print(length);
  Serial.print("]:");
  Serial.write(val, length);
  Serial.print("\n");

  // Example action: Turn on the LED if the text input is "ON", otherwise turn it off.
  if (strcmp(val, "ON") == 0) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}

// Callback for TextInput Value Change.
// Check the textInput1_changed function description for more details.
void textInput2_changed(const char *val, uint8_t length) {
  // custom actions based on the text input value
  // ...
}

/**
 * @brief Adds TextInput to the BindCanvas
 *
 * This function adds (or refreshes, if already exist) TextInput on the BindCanvas screen. It synchronizes
 * the TextInput's properties with the BindCanvas to display it correctly.
 * You can customize the TextInput's position, width, initial value, hint, font size, text color, and background color.
 */
void addTextInput1() {
  // Syncing the TextInput:
  // Set the TextInput's position on the screen.
  // Tip: You can use the grid view mode in BindCanvas app to determine the x and y coordinates
  // and replace these numbers with the grid values for precise positioning.
  textInput1.x = 30;
  textInput1.y = 100;
  // Set the width of the TextInput in characters.
  textInput1.widthChars = 15;
  // Set the initial value for the TextInput.
  textInput1.setText("Enter text");
  // Set the hint for the TextInput.
  textInput1.setHint("Type here...");
  // Set the font size for the TextInput.
  textInput1.fontSize = 18;
  // Set the text color for the TextInput.
  textInput1.textColor = BLACK;
  // Set the background color for the TextInput.
  textInput1.backColor = WHITE;
  // Specify the command to either add the object to the BindCanvas(screen) or refresh the existing one.
  textInput1.cmdId = BIND_ADD_OR_REFRESH_CMD;
  // Set the callback function for the TextInput object.
  textInput1.setCallback(textInput1_changed);
  // Synchronize the textInput1 object with BindCanvas.
  bind.sync(textInput1);
}

// Adds the second TextInput to the BindCanvas.
// Check the addTextInput1 function description for more details.
void addTextInput2(){
  textInput2.x = 30;
  textInput2.y = 150;
  textInput2.setText("");
  textInput2.setHint("");
  textInput2.fontSize = 18;
  textInput2.textColor = BLACK;
  textInput2.backColor = WHITE;
  textInput2.cmdId = BIND_ADD_OR_REFRESH_CMD;
  textInput2.setCallback(textInput2_changed);
  bind.sync(textInput2);
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
 * @param width The width of the screen in dp (Density-Independent Pixels).
 * @param height The height of the screen in dp (Density-Independent Pixels).
 */
void onConnection(int16_t width, int16_t height) {
  addTextInput1();
  addTextInput2();
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // Initialize the Bind object and specify the communication method  and callback function (onConnection).
  // Start WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  bindUdp.begin("YOUR_DEVICE_NAME", bind);
  bind.init(bindUdp, onConnection);
}

void loop() {
  // This delay is not an essential part of the code
  // but is included here to simulate the other work you may want to do.
  delay(10);
  // you access the text input values in the main loop as well.
  if (millis() - lastMs > 1000) {
    lastMs = millis();
    // Print the current values of the text inputs
    Serial.print("TextInput1 value: ");
    Serial.print(textInput1.getText());
    Serial.print("\tTextInput2 value: ");
    Serial.println(textInput2.getText());
  }
}
