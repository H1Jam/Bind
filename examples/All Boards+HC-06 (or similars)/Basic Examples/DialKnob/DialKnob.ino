//We only use SoftwareSerial for AVR Arduinos or ESP8266 library.
#if defined(__AVR__) || defined(ESP8266)
#include <SoftwareSerial.h>
#endif

#include "Bind.hpp"

// Note: Adjust the pins to match your Bluetooth module's configuration.
// We may use SoftwareSerial for AVR Arduinos or ESP8266.
#ifdef __AVR__
SoftwareSerial btSerial(4, 3);  // For AVR Arduinos like Pro Mini or Mega: RX: pin 4, TX: pin 3
#elif defined(ESP8266)
SoftwareSerial btSerial(D1, D2);  // For ESP8266: RX: pin D1, TX: pin D2
#elif defined(ESP32)
#define btSerial Serial2  // For ESP32 we use Serial2.
#elif defined(ARDUINO_ARCH_RP2040)
#define btSerial Serial1  // For RP2040(Raspberry Pi Pico): Use serial1 RX: pin 2, TX: pin 1
#else
SoftwareSerial btSerial(4, 3);  // Modify this line, if your board is neither above.
#endif

// If the board doesn't have built-in LED, assign an external LED here (if wish to use it):
#ifndef LED_BUILTIN
#define LED_BUILTIN 10
#endif  

Bind bind;
BindKnob knob1;
BindKnob knob2;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize the Bind object and specify the communication method (btSerial) and callback function (onConnection).
  bind.init(btSerial, onConnection);

  // Connect the callback functions with the Bind objects.
  bind.join(knob1, knob1_changed);
  bind.join(knob2, knob2_changed);

  // Note: Adjust the baud rate to match your Bluetooth module's configuration.
  btSerial.begin(57600);
}

void loop() {
  // Regularly synchronize Bind UI events to receive bind events.
  bind.sync();

  // This delay is not an essential part of the code
  // but is included here to simulate the other work you may want to do.
  delay(10);
}

// Callback for Knob 1 Value Change
void knob1_changed(int16_t val) {
  Serial.print("Knob 1 value has changed to: ");
  Serial.println(val);

  // Some action:
  if (val > 50) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}

// Callback for Knob 2 Value Change
void knob2_changed(int16_t val) {
  Serial.print("Knob 2 has been changed to: ");
  Serial.println(val);

  // Implement your custom actions here based on the knob value
}

// Screen Setup Callback for BindCanvas
void onConnection(int16_t w, int16_t h) {
  Serial.println("Screen setup started!");
  addKnobs();
  Serial.println("Screen setup done!");
}

// Function to add knobs to the BindCanvas screen
void addKnobs() {
  // Configure and synchronize Knob 1
  knob1.x = 100;
  knob1.y = 100;
  knob1.dimSize = 150; // The dimensions(width = height) of the knob1.
  knob1.cmdId = BIND_ADD_OR_REFRESH_CMD;
  knob1.minValue = 0;
  knob1.maxValue = 100;
  knob1.value = 50;  // Initial value
  bind.sync(knob1);

  // Configure and synchronize Knob 2
  knob2.x = 100;
  knob2.y = 260;
  knob2.dimSize = 150; // The dimensions(width = height) of the knob2.
  knob2.cmdId = BIND_ADD_OR_REFRESH_CMD;
  knob2.minValue = 0;
  knob2.maxValue = 100;
  knob2.value = 25;  // Initial value
  bind.sync(knob2);
}
