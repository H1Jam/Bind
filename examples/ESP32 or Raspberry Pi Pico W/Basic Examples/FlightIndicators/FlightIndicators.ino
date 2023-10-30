//Atention: For Raspberry Pi Pico W, this library needs Bluetooth enabled.  
//Use the 'Tools->IP/Bluetooth Stack' menu in the IDE to enable it (x + Bluetooth).

#if defined(ESP32)
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
#elif defined(ARDUINO_ARCH_RP2040)
#include <SerialBT.h>
#endif

#include "Bind.hpp"

Bind bind;
BindAttitudeIndicator attitudeIndicator;
BindHeadingIndicator headingIndicator;

int counter = 0;
float rollC = 0;
float pitchC = 0;

float rollDelta = 2;
float pitchDelta = 1;

float headingC = 0;

void onConnection(int16_t width, int16_t height) {
  Serial.println("Screen setup started!");
  drawAttitudeIndicator();
  addHeadingIndicator();
  Serial.println("Screen setup done!");
}

void drawAttitudeIndicator() {
  attitudeIndicator.x = 80;
  attitudeIndicator.y = 70;
  attitudeIndicator.cmdId = BIND_ADD_OR_REFRESH_CMD;
  attitudeIndicator.dimSize = 200;

  // Specify the initial roll and pitch values.
  attitudeIndicator.roll = 0.0f;
  attitudeIndicator.pitch = 0.0f;

  // Synchronize the attitudeIndicator object with BindCanvas.
  bind.sync(attitudeIndicator);
}

void addHeadingIndicator() {
  headingIndicator.x = 80;
  headingIndicator.y = 270;
  headingIndicator.cmdId = BIND_ADD_OR_REFRESH_CMD;
  headingIndicator.dimSize = 200;

  // Specify the initial heading value.
  headingIndicator.heading = 0.0f;

  // Synchronize the headingIndicator object with BindCanvas.
  bind.sync(headingIndicator);
}

void setup() {
  Serial.begin(115200);
  
#if defined(ESP32)
  String devName = "BindOnESP32";
  SerialBT.begin(devName);
  Serial.println("The Bluetooth device started. Pair your phone with Bluetooth!");
  Serial.println("Device Name:");
  Serial.println(devName);
#elif defined(ARDUINO_ARCH_RP2040)
  SerialBT.begin();
#endif

  bind.init(SerialBT, onConnection);
  
  Serial.println("The Bluetooth device started, now you can pair the phone with Bluetooth!");
}

void loop() {
  bind.sync();
  delay(10);
  counter++;
  if (counter > 20) {
    counter = 0;
    rollC += rollDelta;
    pitchC += pitchDelta;
    headingC += 5;

    if (rollC > 20 || rollC < -20) {
      rollDelta = -1 * rollDelta;
    }

    if (pitchC > 20 || pitchC < -20) {
      pitchDelta = -1 * pitchDelta;
    }

    if (headingC > 360) {
      headingC = 0.0f;
    }
    setAttitudeIndicator(rollC, pitchC);
    setHeadingIndicator(headingC);
  }
}

void setAttitudeIndicator(float roll, float pitch) {
  attitudeIndicator.cmdId = BIND_DATA_ONLY_CMD;
  attitudeIndicator.roll = roll;
  attitudeIndicator.pitch = pitch;
  bind.sync(attitudeIndicator);
}

void setHeadingIndicator(float heading) {
  headingIndicator.cmdId = BIND_DATA_ONLY_CMD;
  headingIndicator.heading = heading;
  bind.sync(headingIndicator);
}
