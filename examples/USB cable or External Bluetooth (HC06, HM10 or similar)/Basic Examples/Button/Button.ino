// This example uses USB cable or External Bluetooth (HC06, HM10 or similar) for communication.
// If using the USB cable, you can connect your Arduino Board to 
// your phone/tablet using a USB OTG cable.
// If using an external Bluetooth module, you can connect your Arduino Board to
// the Bluetooth module using the Serial pins (RX, TX). Check your Arduino Board
// documentation for the correct pins.
// Also, remember to configure your Bluetooth module buad rate. 
// We assume 115200 bps as baud rate in this example.
#include "Bind.h"

Bind bind;
BindButton button1;
BindButton button2;

const int ledPin = 2; // change this to the pin where your LED is connected.

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
  addButton1();
  addButton2();
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // Initialize the Bind object and specify the communication method  and callback function (onConnection).
	bind.init(Serial, onConnection);

  // Connect the callback functions with the Bind objects.
  bind.join(button1, button1_pressed);
  bind.join(button2, button2_pressed);
}

void loop() {
  // Synchronize Bind UI Events (Not required on ESP32 when using BindOverBLE or BindOverWifi)
  // Callin bind.sync() regularly is crucial to handle of user inputs and touch events.
  // It's recommended to call bind.sync() a couple of times per second, but the faster, the better!
  bind.sync();
  // This delay is not an essential part of the code
  // but is included here to simulate the other work you may want to do.
  delay(10);
}
