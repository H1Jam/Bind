#include "Bind.h"
#include "BindUtil/BindOverBLE.h"
BleStream bleStream;

Bind bind;
BindKnob knob1;
BindKnob knob2;
const int ledPin = 2;

// Screen Setup Callback for BindCanvas
void onConnection(int16_t w, int16_t h) {
  addKnobs();
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // Initialize the Bind object and specify the communication method (bleStream) and callback function (onConnection).
  bleStream.begin("YOUR_DEVICE_NAME", bind);
	bind.init(bleStream, onConnection);

  // Connect the callback functions with the Bind objects.
  bind.join(knob1, knob1_changed);
  bind.join(knob2, knob2_changed);

}

void loop() {

  // Do some work...
  delay(10);
}

// Callback for Knob 1 Value Change
void knob1_changed(int16_t val) {

  // Some action:
  if (val > 50) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}

// Callback for Knob 2 Value Change
void knob2_changed(int16_t val) {

  // Implement your custom actions here based on the knob value
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
  knob1.setlabel("knob1");
  bind.sync(knob1);

  // Configure and synchronize Knob 2
  knob2.x = 100;
  knob2.y = 260;
  knob2.dimSize = 150; // The dimensions(width = height) of the knob2.
  knob2.cmdId = BIND_ADD_OR_REFRESH_CMD;
  knob2.minValue = 0;
  knob2.maxValue = 100;
  knob2.value = 25;  // Initial value
  knob2.setlabel("knob2");
  bind.sync(knob2);
}
