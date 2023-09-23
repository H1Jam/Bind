#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
Bind bind;
BindRectangle rectangle1;
BindRectangle rectangle2;

// void addBoxes() {
//   screenRectangle1.x = 10;
//   screenRectangle1.y = 10;
//   screenRectangle1.cmdId = ADD_OR_REFRESH_CMD;
//   screenRectangle1.width = 300;
//   screenRectangle1.height = 100;
//   screenRectangle1.fillColor = UBUNTU;
//   screenRectangle1.strokeColor = YELLOW;
//   screenRectangle1.strokeWidth = 2;
//   screenRectangle1.cornersRadius = 5;
//   sendScreenStream(&screenRectangle1, &SerialBT);
  
//   screenRectangle2.x = 10;
//   screenRectangle2.y = 120;
//   screenRectangle2.cmdId = ADD_OR_REFRESH_CMD;
//   screenRectangle2.width = 300;
//   screenRectangle2.height = 200;
//   screenRectangle2.fillColor = UBUNTU;
//   screenRectangle2.strokeColor = YELLOW;
//   screenRectangle2.strokeWidth = 2;
//   screenRectangle2.cornersRadius = 10;
//   sendScreenStream(&screenRectangle2, &SerialBT);
  
//   screenRectangle3.x = 20;
//   screenRectangle3.y = 260;
//   screenRectangle3.cmdId = ADD_OR_REFRESH_CMD;
//   screenRectangle3.width = 280;
//   screenRectangle3.height = 50;
//   screenRectangle3.fillColor = BLACK;
//   screenRectangle3.strokeColor = YELLOW;
//   screenRectangle3.strokeWidth = 2;
//   screenRectangle3.cornersRadius = 50;
//   sendScreenStream(&screenRectangle3, &SerialBT);
// }

// onConnection Callback for BindCanvas
void onConnection(int16_t w, int16_t h) {
  Serial.println("Screen setup started!");
  addRectangles();
  Serial.println("Screen setup done!");
}

// Function to add a rectangle to the BindCanvas screen
void addRectangles() {
  // Configure and synchronize the rectangle
  rectangle1.x = 50;
  rectangle1.y = 50;
  rectangle1.width = 200;
  rectangle1.height = 100;
  rectangle1.cmdId = BIND_ADD_OR_REFRESH_CMD;
  rectangle1.fillColor = WHITE; // Fill color of the rectangle (in RGB format)
  rectangle1.borderColor = RGB(100, 100, 100); // Border color of the rectangle (in RGB format) 
  rectangle1.borderWidth = 2; // Border width in pixels
  rectangle1.cornersRadius = 5;  /// Radius of the rectangle's rounded corners.
  bind.sync(&rectangle1);

  rectangle2.x = 50;
  rectangle2.y = 180;
  rectangle2.width = 100;
  rectangle2.height = 100;
  rectangle2.cmdId = BIND_ADD_OR_REFRESH_CMD;
  rectangle2.fillColor = WHITE; // Fill color of the rectangle (in RGB format)
  rectangle2.borderColor = DKGRAY; // Border color of the rectangle (in RGB format) 
  rectangle2.borderWidth = 2; // Border width in pixels
  rectangle2.cornersRadius = 5;  /// Radius of the rectangle's rounded corners.
  bind.sync(&rectangle2);

}

void setup() {
  Serial.begin(115200);
    // Initialize the Bind object and specify the communication method (SerialBT) and callback function (onConnection).
  bind.init(&SerialBT, &onConnection);
  String devName = "ESP32testB";
  SerialBT.begin(devName);
  Serial.println("The bluetooth device started, now you can pair the phone with bluetooth!");
  Serial.println("devName:");
  Serial.println(devName);
}

void loop() {
  // Synchronize Bind UI events
  bind.sync();

  // Add a small delay to control the loop speed
  delay(10);
}

