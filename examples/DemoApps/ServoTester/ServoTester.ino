// Atention: For Raspberry Pi Pico W, this library needs Bluetooth enabled.
// Use the 'Tools->IP/Bluetooth Stack' menu in the IDE to enable it (x + Bluetooth).

// Include libraries
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif
#include "Bind.hpp"
#if defined(ESP32)
#include "BluetoothSerial.h"
#include <ESP32Servo.h>
BluetoothSerial SerialBT;
#elif defined(ARDUINO_ARCH_RP2040)
#include <Servo.h>
#include <SerialBT.h>
#endif

// Define variables
int analogInPin = 15;
int sensorValue = 0;
int outputValue = 0;
int counter = 0;
int r = 4, g = 4, b = 2;
int ledCount = 0;
unsigned long lastMs = 0;
unsigned long deltaMs = 0;
Servo myservo;

// Define pin for NeoPixels
#define PIN 12  // On Trinket or Gemma, suggest changing this to 1

// Define number of NeoPixels
#define NUMPIXELS 8  // Popular NeoPixel ring size

// If the board doesn't have built-in LED, assign an external LED here (if wish to use it):
#ifndef LED_BUILTIN
#define LED_BUILTIN 10
#endif

#define servoPin 13

// Create Bind objects
Bind bind;
BindSeekBar seekBar1;
BindGaugeCompact gauge1;
BindColorPicker colorPicker1;
BindButton button1;
BindButton button2;
BindTextLabel textLabel1;
BindChart chart1;
BindKnob knob1;

// Callback function for screen setup
void onConnection(int16_t width, int16_t height) {
  Serial.println("Screen setup started!");
  setScreenConfig();
  addButton1();
  addKnob();
  addtTextlabel();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);

  // Set analog read resolution for ESP32 and RP2040
#if defined(ESP32) || defined(ARDUINO_ARCH_RP2040)
  analogReadResolution(10);
#endif

#if defined(ESP32)
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 500, 2400); // attaches the servo on pin 18 to the servo object
  String devName = "BindOnESP32";
  SerialBT.begin(devName);
  Serial.println("The Bluetooth device started. Pair your phone with Bluetooth!");
  Serial.println("Device Name:");
  Serial.println(devName);
  analogInPin = 15;
#elif defined(ARDUINO_ARCH_RP2040)
  myservo.attach(2);
  analogInPin = A0;
  SerialBT.begin();
#endif

  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize the Bind object and specify the communication method (SerialBT) and callback function (onConnection).
  bind.init(SerialBT, onConnection);
  // Note: It was SerialBT here, but it could be any serial port, including hardware and software serial.

  // Connect the callback functions with the Bind objects.
  bind.join(button1, button1_pressed);
  // bind.join(button2, button2_pressed);
  bind.join(knob1, knob1_changed);
}

void loop() {
  // Regularly synchronize Bind UI events
  bind.sync();
  // This delay is not an essential part of the code
  // but is included here to simulate a brief pause..
  //syncPotentiometer();
  delay(10);
}