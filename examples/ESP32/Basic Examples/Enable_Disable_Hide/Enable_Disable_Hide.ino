#include "Bind.h"
#include "BindUtil/BindOverBLE.h"  // For BLE
// If you want to use Bluetooth Classic (which is faster), uncomment the
// following two lines. However, please note that Bluetooth Classic is not
// compatible with ESP32-C3 or ESP32-S3 models (BLE only).
//#include "BluetoothSerial.h" 
//BluetoothSerial SerialBT; 

// Note: This Disable/Enable logic can be applied to all Bind objects;

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
  Serial.println("Button 1 has been pressed!");
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
 * This function adds (or refreshes, if already exist) Button 1 on the
 * BindCanvas screen. It synchronizes the Button's properties with the
 * BindCanvas to display it correctly. You can customize the Button's position,
 * size, text, and more.
 * @attention a button object need the calback function as well. See the
 * button1_pressed() function.
 * events.
 */
void addButton1() {
  // Syncing the first Button:
  // Set the Button's position on the screen.
  // Tip: You can use the grid view mode in BindCanvas app to determine the x
  // and y coordinates and replace these numbers with the grid values for
  // precise positioning.
  button1.x = 100;
  button1.y = 300;
  // Set the Button's text label.
  button1.setlabel("Toggle LED");  // button label
  button1.fontSize =
      23;  // The dimensions(width and height) of the Button on the screen are
           // determined relative to the Font size.
  button1.textColor = BLACK;               // Text color
  button1.backColor = RGB(153, 204, 255);  // button color
  // Specify the command to either add the object to the BindCanvas or refresh
  // the existing one.
  button1.cmdId = BIND_ADD_OR_REFRESH_CMD;
  // Synchronize the button1 object with BindCanvas.
  bind.sync(button1);
}

void addButtonShowHide() {
  // Syncing 2nd Button:
  // See addButton1 descripotions!
  buttonShowHide.x = 100;
  buttonShowHide.y = 150;
  // Set the Button's text label.
  buttonShowHide.setlabel("Show/Hide");  // button label
  buttonShowHide.fontSize =
      23;  // The dimensions(width and height) of the Button on the screen are
           // determined relative to the Font size.
  buttonShowHide.textColor = BLACK;   // Text color
  buttonShowHide.backColor = YELLOW;  // button color
  // Specify the command to either add the object to the BindCanvas or refresh
  // the existing one.
  buttonShowHide.cmdId = BIND_ADD_OR_REFRESH_CMD;
  // Synchronize the button1 object with BindCanvas.
  bind.sync(buttonShowHide);
}

void addButtonDisableEnable() {
  // Syncing 3rd Button:
  // See addButton1 descripotions!
  buttonDisableEnable.x = 80;
  buttonDisableEnable.y = 100;
  // Set the Button's text label.
  buttonDisableEnable.setlabel("Enable/Disable");  // button label
  buttonDisableEnable.fontSize =
      23;  // The dimensions(width and height) of the Button on the screen are
           // determined relative to the Font size.
  buttonDisableEnable.textColor = BLACK;   // Text color
  buttonDisableEnable.backColor = YELLOW;  // button color
  // Specify the command to either add the object to the BindCanvas or refresh
  // the existing one.
  buttonDisableEnable.cmdId = BIND_ADD_OR_REFRESH_CMD;
  // Synchronize the button1 object with BindCanvas.
  bind.sync(buttonDisableEnable);
}

void onConnection(int16_t w, int16_t h) {
  Serial.println("Screen setup started!");
  addButton1();
  addButtonShowHide();
  addButtonDisableEnable();
  button1visible = true;
  button1Enable = true;
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize the Bind object and specify the communication method (SerialBT)
  // and callback function (onConnection).
  BleStream* SerialBT = ble_init(bind, "BindOnESP32_ble"); // Only when using BLE! otherwise comment the line.
  //SerialBT.begin("BindOnESP32"); // Uncomment For Bluetooth Classic
  bind.init(SerialBT, onConnection);
  // Note: It was SerialBT here, but it could be any serial port, including
  // hardware and software serial.

  // Connect the callback functions with the Bind objects.
  bind.join(button1, button1_pressed);
  bind.join(buttonShowHide, buttonShowHide_pressed);
  bind.join(buttonDisableEnable, buttonDisableEnable_pressed);
}

void loop() { 
  // bind.sync(); // Uncomment For Bluetooth Classic
  // For BLE, no need to periodically call bind.sync(); it's already handled by the ESP32 BLE service
  delay(10); 
}
