#if defined(ARDUINO_ARCH_ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#include "Bind.h"
#include "BindUtil/BindOverWifi.h"
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
UDPStream bindUdp;
// Note: This logic can be applied to all Bind objects; I used bind button (button1) here.
// Note: Check the button sample for a better understanding of how Bind buttons work.
#ifndef LED_BUILTIN
#define LED_BUILTIN 10
#endif

Bind bind;
BindButton button1;
BindButton buttonShowHide;
BindButton buttonDisableEnable;

bool ledStatus = false;

bool button1visible = true;
bool button1Enable = true;

void button1_pressed() {
  ledStatus = !ledStatus;
  digitalWrite(LED_BUILTIN, ledStatus);
}

/**
 * @brief Callback for buttonShowHide Press Event
 */
void buttonShowHide_pressed() {
  if (button1visible) {
    button1.cmdId = BIND_HIDE_CMD;
  } else {
    button1.cmdId = BIND_VISIBLE_CMD;
  }
  button1visible = !button1visible;
  // Synchronize the button1 object with BindCanvas.
  bind.sync(button1);
}

/**
 * @brief Callback for buttonDisableEnable Press Event
 */
void buttonDisableEnable_pressed() {
  if (button1Enable) {
    button1.cmdId = BIND_DISABLE_CMD;
  } else {
    button1.cmdId = BIND_ENABLE_CMD;
  }
  button1Enable = !button1Enable;
  // Synchronize the button1 object with BindCanvas.
  bind.sync(button1);
}

/**
 * @brief Adds Button 1 to the BindCanvas
 *
 * This function adds (or refreshes, if already exist) Button 1 on the BindCanvas screen.
 * It synchronizes the Button's properties with the BindCanvas to display it correctly.
 * You can customize the Button's position, size, text, and more.
 * @attention a button object need the calback function as well. See the button1_pressed()
 * function.
 */
void addButton1() {
  // Syncing the first Button:
  // Set the Button's position on the screen.
  // Tip: You can use the grid view mode in BindCanvas app to determine the x and y coordinates
  // and replace these numbers with the grid values for precise positioning.
  button1.x = 100;
  button1.y = 300;
  // Set the Button's text label.
  button1.setLabel("Toggle LED");          // button label
  button1.fontSize = 23;                   // The dimensions(width and height) of the Button on the screen are determined relative to the Font size.
  button1.textColor = BLACK;               // Text color
  button1.backColor = RGB(153, 204, 255);  // button color
  // Specify the command to either add the object to the BindCanvas or refresh the existing one.
  button1.cmdId = BIND_ADD_OR_REFRESH_CMD;
  // Set the callback function for the Button 1 object.
  button1.setCallback(button1_pressed);
  // Synchronize the button1 object with BindCanvas.
  bind.sync(button1);
}

void addButtonShowHide() {
  // Syncing 2nd Button:
  // See addButton1 descripotions!
  buttonShowHide.x = 100;
  buttonShowHide.y = 150;
  // Set the Button's text label.
  buttonShowHide.setLabel("Show/Hide");  // button label
  buttonShowHide.fontSize = 23;          // The dimensions(width and height) of the Button on the screen are determined relative to the Font size.
  buttonShowHide.textColor = BLACK;      // Text color
  buttonShowHide.backColor = YELLOW;     // button color
  // Specify the command to either add the object to the BindCanvas or refresh the existing one.
  buttonShowHide.cmdId = BIND_ADD_OR_REFRESH_CMD;
  buttonShowHide.setCallback(buttonShowHide_pressed);
  // Synchronize the button1 object with BindCanvas.
  bind.sync(buttonShowHide);
}

void addButtonDisableEnable() {
  // Syncing 3rd Button:
  // See addButton1 descripotions!
  buttonDisableEnable.x = 80;
  buttonDisableEnable.y = 100;
  // Set the Button's text label.
  buttonDisableEnable.setLabel("Enable/Disable");  // button label
  buttonDisableEnable.fontSize = 23;               // The dimensions(width and height) of the Button on the screen are determined relative to the Font size.
  buttonDisableEnable.textColor = BLACK;           // Text color
  buttonDisableEnable.backColor = YELLOW;          // button color
  // Specify the command to either add the object to the BindCanvas or refresh the existing one.
  buttonDisableEnable.cmdId = BIND_ADD_OR_REFRESH_CMD;
  buttonDisableEnable.setCallback(buttonDisableEnable_pressed);
  // Synchronize the button1 object with BindCanvas.
  bind.sync(buttonDisableEnable);
}

void onConnection(int16_t w, int16_t h) {
  addButton1();
  addButtonShowHide();
  addButtonDisableEnable();
  button1visible = true;
  button1Enable = true;
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

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
}

void loop() {

  // This delay is not an essential part of the code
  // but is included here to simulate the other work you may want to do.
  delay(10);
}
