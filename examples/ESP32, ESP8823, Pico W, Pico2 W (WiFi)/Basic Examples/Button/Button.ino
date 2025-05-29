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

Bind bind;
BindButton button1;
BindButton button2;

// if the LED_BUILTIN is not defined by the board, define it as pin 2
#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif

const int ledPin = LED_BUILTIN; // change this to the pin where your LED is connected.

// This function is automatically triggered when Button 1 is pressed on the screen.
void button1_pressed() {
  // Implement your custom actions here:
  digitalWrite(ledPin, HIGH);
  // Add more actions as needed.
}

// Callback for Button 1 Press Event
void button2_pressed() {
  // See button1_pressed descripotions!
  digitalWrite(ledPin, LOW);
  // Add more actions as needed.
}

// This function adds (or refreshes, if already exist) Button 1 on the BindCanvas screen.
void addButton1() {
  // Syncing Button 1:
  // Set the Button's position on the screen.
  // Tip: You can use the grid view mode in BindCanvas app to determine the x and y coordinates
  // and replace these numbers with the grid values for precise positioning.
  button1.x = 30;
  button1.y = 150;
  // Set the Button's text label.
  button1.setLabel("ON");     // button label
  button1.fontSize = 23;      // The dimensions(width and height) of the Button on the screen are determined relative to the Font size.
  button1.textColor = BLACK;  // Text color
  button1.backColor = GREEN;  // button color
  // Specify the command to either add the object to the BindCanvas or refresh the existing one.
  button1.cmdId = BIND_ADD_OR_REFRESH_CMD;
  // Set the callback function for the Button 1 object.
  button1.setCallback(button1_pressed);
  // Synchronize the button1 object with BindCanvas.
  bind.sync(button1);
}

void addButton2() {
  // Syncing Button 2:
  // See addButton1 descripotions!
  button2.x = 30;
  button2.y = 200;
  // Set the Button's text label.
  button2.setLabel("OFF");     // button label
  button2.fontSize = 23;       // The dimensions(width and height) of the Button on the screen are determined relative to the Font size.
  button2.textColor = BLACK;   // Text color
  button2.backColor = YELLOW;  // button color
  // Specify the command to either add the object to the BindCanvas or refresh the existing one.
  button2.cmdId = BIND_ADD_OR_REFRESH_CMD;
  // Set the callback function for the Button 2 object.
  button2.setCallback(button2_pressed);
  // Synchronize the button1 object with BindCanvas.
  bind.sync(button2);
}

void onConnection(int16_t w, int16_t h) {
  addButton1();
  addButton2();
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
}
