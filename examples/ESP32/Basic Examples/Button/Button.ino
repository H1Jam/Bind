#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
ScreenObjects screenObjects;
ScreenButton screenButton1;
const int ledPin = 2;
bool ledIsON = false;

void buttonClicked1() {
  Serial.println("button1 has been clicked!");
  ledIsON = !ledIsON;
  digitalWrite(ledPin, ledIsON);
}

void addButton1() {
  // Syncing Button 1:
  // Set the Button's position on the screen.
  // Tip: You can use the grid view mode in BindCanvas app to determine the x and y coordinates
  // and replace these numbers with the grid values for precise positioning.
  button1.x = 30;
  button1.y = 150;
  // Set the Button's text label.
  button1.setlabel("Click Me");  // button label
  button1.fontSize = 23;         // The dimensions(width and height) of the Button on the screen are determined relative to the Font size.
  button1.textColor = BLACK;         // Text color
  button1.backColor = YELLOW;    // button color
  // Specify the command to either add the object to the BindCanvas or refresh the existing one.
  button1.cmdId = BIND_ADD_OR_REFRESH_CMD;
  // Synchronize the button1 object with BindCanvas.
  bind.sync(&button1);
}

void screenSetup(int16_t w, int16_t h) {
  Serial.println("Screen setup started!");
  addButton1();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  screenObjects.registerScreenSetup(&screenSetup);
  screenObjects.registerButton(&screenButton1, &buttonClicked1);
  String devName = "ESP32testB";
  SerialBT.begin(devName);
  Serial.println("The bluetooth device started, now you can pair the phone with bluetooth!");
  Serial.println("devName:");
  Serial.println(devName);
}

void loop() {
  while (SerialBT.available()) {
    screenObjects.updateScreen(SerialBT.read());
  }
  delay(10);
}
