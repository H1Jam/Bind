/**
 * @brief This is a demo application for testing the Bind library with a servo motor.
 * 
 * The code demonstrates how to use the Bind library to create a graphical user interface (GUI)
 * for controlling a servo motor using various UI elements such as buttons, knobs, and labels.
 * 
 * The servo motor is connected to pin 13 (SERVO_PIN) of the Arduino board.
 * 
 * The code also includes platform-specific configurations for different boards such as AVR, ESP32, and Raspberry Pi Pico W.
 * 
 * Note: For Raspberry Pi Pico W. Enable Bluetooth using the IDE menu.
 * Use the 'Tools->IP/Bluetooth Stack' menu in the IDE to enable it (x + Bluetooth).
 */
#include "Bind.h"

// Include libraries based on the board.
#ifdef __AVR__
// Using bluetooth module (like HC-06) with SoftwareSerial.
// For AVR Arduinos like Pro Mini or Mega: RX: pin 4, TX: pin 3
#include <SoftwareSerial.h>
SoftwareSerial bindPort(4, 3);
#elif defined(ESP32)
// Using built-in Bluetooth module.
#include "BluetoothSerial.h"
#include <ESP32Servo.h>
BluetoothSerial bindPort;
#elif defined(ARDUINO_ARCH_RP2040)
// Using built-in Bluetooth module.
#include <Servo.h>
#include <SerialBT.h>
#define bindPort SerialBT
#endif

// Note: Alternativlly you can use any HardwareSerial for the external Bluetooth module,
// or use USB port (Serial) with an OTG adapter to connect to the phone.
//#define bindPort Serial // To use HardwareSerial over USB port.
//#define USE_USB_SERIAL_FOR_BIND  // To use USB port for serial communication.

// If the board doesn't have a built-in LED, assign an external LED to the LED_BUILTIN pin (if you want to use it).
#ifndef LED_BUILTIN
#define LED_BUILTIN 10
#endif

#define SERVO_PIN 13

// Define variables
Servo myservo;

// Create Bind objects
Bind bind;

BindButton button1;
BindTextLabel textLabel1;
BindChart chart1;
BindKnob knob1;
BindRectangle rectangle1;

// Callback function for screen setup
void onConnection(int16_t width, int16_t height)
{
  Serial.println("Screen setup started!");
  setScreenConfig();
  addRectangle1(width, height);
  addButton1();
  addKnob();
  addtTextlabel();
  Serial.println("Screen setup done!");
}

void setup()
{
  Serial.begin(115200);
#if defined(ESP32)
  myservo.setPeriodHertz(50);          // standard #if defined(ESP32)
  myservo.setPeriodHertz(50);          // standard 50 hz servo50 hz servo
  myservo.attach(SERVO_PIN, 500, 2500); // attaches the servo on pin 18 to the servo object
#ifndef USE_USB_SERIAL_FOR_BIND
  String devName = "BindOnESP32";
  bindPort.begin(devName);
  Serial.println("The Bluetooth device started. Pair your phone with Bluetooth!");
  Serial.println("Device Name:");
  Serial.println(devName);
#endif // USE_USB_SERIAL_FOR_BIND
#elif defined(ARDUINO_ARCH_RP2040) // Raspberry Pi Pico W
  // servo pin is 2 for Raspberry Pi Pico W
  myservo.attach(SERVO_PIN, 500, 2500);
#ifndef USE_USB_SERIAL_FOR_BIND
  bindPort.begin();
#endif // USE_USB_SERIAL_FOR_BIND
#endif

  pinMode(LED_BUILTIN, OUTPUT);
  // Initialize the Bind object and specify the communication method (bindPort) and callback function (onConnection).
  bind.init(bindPort, onConnection);
  // Note: It was bindPort here, but it could be any serial port, including hardware and software serial.
  // Connect the callback functions with the Bind objects.
  bind.join(button1, button1_pressed);
  bind.join(knob1, knob1_changed);
}

void loop()
{
  // Regularly synchronize Bind UI events
  bind.sync();
  // This delay is not an essential part of the code
  // but is included here to simulate a brief pause..
  delay(10);
}