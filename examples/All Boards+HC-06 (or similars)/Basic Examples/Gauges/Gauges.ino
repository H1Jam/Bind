//We only use SoftwareSerial for AVR Arduinos or ESP8266 library.
#if defined(__AVR__) || defined(ESP8266)
#include <SoftwareSerial.h>
#endif

#include "Bind.hpp"

// Note: Adjust the pins to match your Bluetooth module's configuration.
// We may use SoftwareSerial for AVR Arduinos or ESP8266.
#ifdef __AVR__
SoftwareSerial btSerial(4, 3); // For AVR Arduinos like Pro Mini or Mega: RX: pin 4, TX: pin 3
#elif defined(ESP8266)
SoftwareSerial btSerial(D1, D2); // For ESP8266: RX: pin D1, TX: pin D2
#elif defined(ESP32) 
#define btSerial Serial2 // For ESP32 we use Serial2.
#elif defined(ARDUINO_ARCH_RP2040)
#define btSerial Serial1 // For RP2040(Raspberry Pi Pico): Use serial1 RX: pin 2, TX: pin 1
#else
SoftwareSerial btSerial(4, 3); // Modify this line, if your board is neither above.
#endif

Bind bind;
BindGauge gauge1;
BindGaugeCompact gauge2;
BindGaugeSimple gauge3;

int counter = 0;
float g1 = 0.0f;
float speed = 0.0f;
float gDelta = 1.0f;
float speedDelta = 5.0f;
unsigned long lastMs = 0;

// Configure and add the first gauge (BindGauge)
void addGauge() {
  gauge1.x = 40;
  gauge1.y = 70;
  gauge1.dimSize = 200;
  gauge1.value = 0.0f;
  gauge1.maxValue = 200.0f;
  gauge1.drawArc = 100;
  gauge1.arcGreenMaxVal = 100.0f;
  gauge1.arcYellowMaxVal = 150.0f;
  gauge1.arcRedMaxVal = 180.0f;
  gauge1.setlabel("Speed mph");
  gauge1.cmdId = BIND_ADD_OR_REFRESH_CMD;
  bind.sync(gauge1);
}

void updateGauge(float value) {
  gauge1.value = value;
  gauge1.cmdId = BIND_DATA_ONLY_CMD;
  bind.sync(gauge1);
}

// Configure and add the second gauge (BindGaugeCompact)
void addGaugeCompact() {
  gauge2.x = 40;
  gauge2.y = 270;
  gauge2.dimSize = 200;
  gauge2.value = 0.0f;
  gauge2.maxValue = 200.0f;
  gauge2.drawArc = 100;
  gauge2.arcGreenMaxVal = 100.0f;
  gauge2.arcYellowMaxVal = 150.0f;
  gauge2.arcRedMaxVal = 180.0f;
  gauge2.setlabel("Speed Km/h");
  gauge2.cmdId = BIND_ADD_OR_REFRESH_CMD;
  bind.sync(gauge2);
}

void updateGaugeCompact(float value) {
  gauge2.value = value;
  gauge2.cmdId = BIND_DATA_ONLY_CMD;
  bind.sync(gauge2);
}

void addGaugeSimple() {
  gauge3.x = 40;
  gauge3.y = 370;
  gauge3.dimSize = 200;
  gauge3.value = 0.0f;
  gauge3.maxValue = 20;
  gauge3.minValue = -20;
  gauge3.style = 0;
  gauge3.isSymmetrical = true;
  gauge3.color = BLUE;
  gauge3.setlabel("Simple Gauge");
  gauge3.cmdId = BIND_ADD_OR_REFRESH_CMD;
  bind.sync(gauge3);
}

void updateGaugeSimple(float value) {
  gauge3.value = value;
  gauge3.cmdId = BIND_DATA_ONLY_CMD;
  bind.sync(gauge3);
}

void onConnection(int16_t width, int16_t height) {
  Serial.println("Screen setup started!");
  addGauge();
  addGaugeCompact();
  addGaugeSimple();
  Serial.println("Screen setup done!");
}

void setup() {
  Serial.begin(115200);
  // Note: Adjust the baud rate to match your Bluetooth module's configuration.
  btSerial.begin(57600);

  bind.init(btSerial, onConnection);

  Serial.println("The Bluetooth device started. Pair your phone with Bluetooth!");
  Serial.println("Device Name:");
}

void loop() {
  bind.sync();
  delay(5);

  // Sending some dummy data to the gauges:
  if (millis() - lastMs > 100) {
    lastMs = millis();

    g1 += gDelta;
    speed += speedDelta;

    if (g1 >= 20.0f || g1 <= -20.0f) {
      gDelta = -1 * gDelta;
    }

    if (speed >= 200.0f || speed <= -0.0f) {
      speedDelta = -1 * speedDelta;
    }

    if (bind.isReady()) {
      updateGauge(speed);
      updateGaugeCompact(speed);
      updateGaugeSimple(g1);
    }
  }
}
