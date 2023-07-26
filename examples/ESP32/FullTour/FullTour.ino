#include "BluetoothSerial.h"

#include "UIduino.hpp"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
// make an echo protocole.
BluetoothSerial SerialBT;
bool doWait = false;
byte inp = 0;
const int ledPin = 2;
ScreenTextLabel textLabel;
ScreenButton screenButton1;
ScreenButton screenButton3;
ScreenButton screenButton2;
ScreenKnob screenknob;
ScreenGauge screenGauge;
ScreenMap screenMap;
ScreenMapMarker screenMapMarker1;
ScreenMapMarker screenMapMarker2;
ScreenSwitch screenSwitch;
ScreenSwitch screenSwitch1;
ScreenAttitudeIndicator screenAttitudeIndicator;
ScreenHeadingIndicator screenHeadingIndicator;
ScreenGaugeSimple screenGaugeSimple;
ScreenGaugeCompact screenCompact;
ScreenColorPicker screenColorPicker;
ScreenChart screenChart;
ScreenRectangle screenRectangle;
ScreenTerminal screenTerminal;
bool label_counter = false;
bool button_counter = false;
int inpTemp;
uint8_t frameSendBuffer[MAX_DATA_LENGHT + 6];
int frameSendBufferSize = 0;

int16_t knb1;
int16_t knb2;
int16_t knb3;
int16_t knb4;

int datacntr = 0;
ScreenSettings screenSettings;

void buttonClicked1()
{
  Serial.print("\nA 1 button has been clicked!\n");
  screenButton3.x = 60;
  screenButton3.y = 220;
  screenButton3.color = BLACK;
  button_counter = !button_counter;
  screenButton3.backColor = YELLOW;
  if (button_counter) {
    screenButton3.cmdId = DISABLE_CMD;
    screenButton3.setlabel("@C++@");
    screenButton3.fontSize = 23;
  } else {
    screenButton3.cmdId = ENABLE_CMD;
    screenButton3.setlabel("!C++! ");
    screenButton3.fontSize = 18;
  }
  sendScreenStream(&screenButton3, &SerialBT);
  datacntr++;
  screenButton2.x = 200;
  screenButton2.y = 220;
  screenButton2.color = WHITE;
  screenButton2.backColor = LTGRAY;
  if (button_counter) {
    screenButton2.cmdId = DISABLE_CMD;
    screenButton2.setlabel("BTN2");
    screenButton2.fontSize = 23;
  } else {
    screenButton2.cmdId = ENABLE_CMD;
    screenButton2.setlabel("Start Motor");
    screenButton2.fontSize = 18;
  }
  sendScreenStream(&screenButton2, &SerialBT);
  screenSettings.screenOrientation = SCREEN_ORIENTATION_UNSPECIFIED;
  screenSettings.backColor = UBUNTU;
  screenSettings.actionBarColor = DKGRAY;
  screenSettings.setlabel("ActionBar From C++");
  sendScreenStream(&screenSettings, &SerialBT);
}

ScreenObjects screenObjects;
ScreenSeekBar screenSeekBar;
ScreenSeekBar screenSeekBar2;
ScreenJoystick screenJoystick1;
void setup() {
  Serial.begin(115200);
  screenObjects.registerScreenSetup(&buttonClicked1);
  screenObjects.registerDialKnob(&screenknob);
  screenButton1.setCallback(&buttonClicked1);
  screenButton2.setCallback(&buttonClicked2);
  screenButton3.setCallback(&buttonClicked3);
  screenObjects.registerButton(&screenButton1);
  screenObjects.registerButton(&screenButton2);
  screenObjects.registerButton(&screenButton3);
  screenObjects.registerSwitch(&screenSwitch);//Todo just get screenSwitch
  screenObjects.registerSwitch(&screenSwitch1);
  screenObjects.registerSeekBar(&screenSeekBar);
  screenObjects.registerSeekBar(&screenSeekBar2);
  screenObjects.registerJoystick(&screenJoystick1);
  screenObjects.registerColorPicker(&screenColorPicker);
  Serial.print("datacntr: ");
  Serial.println(datacntr);
  String devName = "ESP32testB";
  pinMode (ledPin, OUTPUT);
  SerialBT.begin(devName); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  Serial.println("devName:");
  Serial.println(devName);
}


void loop() {
  doWait = true;
  if (Serial.available()) {
    inpTemp = Serial.read();
    doWait = false;
  }
  if (SerialBT.available()) {
    inp = SerialBT.read();
    int a = screenObjects.updateScreen(inp);
    if (a > 0) {
      Serial.print("Got:");
      Serial.println(a);
      if (a == ScreenIDs::knob) {
        Serial.print("\nknb:");
        Serial.println(screenknob.value);
      }

      if (a == ScreenIDs::toggleSwitch) {
        Serial.print("\nSwitchs:");
        Serial.print(screenSwitch.switchValue);
        Serial.print(" ");
        Serial.println(screenSwitch1.switchValue);
      }

      if (a == ScreenIDs::seekBar) {
        Serial.print("\nSeek:");
        Serial.print(screenSeekBar.seekValue);
        Serial.print(" ");
        Serial.println(screenSeekBar2.seekValue);
      }

      if (a == ScreenIDs::joystick) {
        Serial.print("\nJoystick:");
        Serial.print(screenJoystick1.sX);
        Serial.print(" ");
        Serial.println(screenJoystick1.sY);
      }

      if (a == ScreenIDs::colorPicker) {
        Serial.print("\nColorPicker:");
        Serial.print(screenColorPicker.red);
        Serial.print(" ");
        Serial.print(screenColorPicker.green);
        Serial.print(" ");
        Serial.println(screenColorPicker.blue);
      }
      Serial.println("------------");
      Serial.print("\n");
    }
    doWait = false;
  }
  if (doWait) {
    delay(1);
  }
}

bool hasMap = false;
bool hasMapMarker = false;
float gVal = 0;
void buttonClicked2()
{
  textLabel.x = 60;
  textLabel.y = 120;
  //textLabel.text = "Hello From C++! ";
  label_counter = !label_counter;
  if (label_counter) {
    // textLabel.str = "Second";
    textLabel.setlabel("The Other Label!");
    textLabel.color = BLUE;
    textLabel.fontSize = 23;
    // textLabel.cmdId = REMOVE_CMD;
  } else {
    textLabel.setlabel("Hello");
    //textLabel.str = "Hello";
    textLabel.color = RED;
    textLabel.fontSize = 18;
    textLabel.cmdId = ADD_OR_REFRESH_CMD;
  }
  //screenSettings.resetScreen = true;
  sendScreenStream(&screenSettings, &SerialBT);
  sendScreenStream(&textLabel, &SerialBT);
  Serial.print("\nA 2 button has been clicked!\n");
  addScreenTerminalData2();
}

void buttonClicked3()
{
  //  if (hasMap) {
  //    if (!hasMapMarker) {
  //      //  addMapMarker();
  //      hasMapMarker = true;
  //    } else {
  //      // removeMapMarker();
  //      hasMapMarker = false;
  //    }
  //    // addMap();
  //    hasMap = false;
  //  } else {
  //    // addMap();
  //    hasMap = true;
  //  }
  addSwitch();
  addSeekBar();
  //addAH();
  //addHeading();
  addJoystick();
  // addGaugeSimple();
  //addScreenCompact();
  addColorPicker();
  hasMapMarker = !hasMapMarker;
  //  if (!hasMap) {
  addChart();
  addScreenTerminal();
  //  }
  addGauge(&screenGauge, &SerialBT);
  //addKnob();
  hasMap = true;
  //addRectangle();
  addChartdata();
  addScreenTerminalData();
  gVal += 10;
  Serial.print("\n3rd button has been clicked!\n");
}



void addScreenTerminalData2() {
  ScreenTerminalPrint("One lazy dog jumped or did somthing else the other day!", RED, hasMapMarker, true, true, false, &screenTerminal, &SerialBT);
}

void addScreenTerminalData() {
  char cstr[16];
  sprintf(cstr, "%05d", (int)gVal);
  ScreenTerminalPrint(cstr, GREEN, true, true, true, false, &screenTerminal, &SerialBT);
}

void addRectangle() {
  screenRectangle.x = 127;
  screenRectangle.y = 280;
  screenRectangle.cmdId = ADD_OR_REFRESH_CMD;
  screenRectangle.width = 130;
  screenRectangle.height = 140;
  screenRectangle.cornersRadius = 131;
  sendScreenStream(&screenRectangle, &SerialBT);
}


void addChartdata() {
  addChartdata(random(-30, 30), &screenChart, &SerialBT);
}

void addChart() {
  screenChart.x = 10;
  screenChart.y = 80;
  screenChart.cmdId = ADD_OR_REFRESH_CMD;
  screenChart.width = 200;
  screenChart.height = 140;
  screenChart.maxY = 10;
  screenChart.minY = -10;
  screenChart.maxX = 20;
  screenChart.autoSize = true;
  screenChart.color = MAGENTA;
  sendScreenStream(&screenChart, &SerialBT);
}

void addJoystick() {
  screenJoystick1.x = 200;
  screenJoystick1.y = 80;
  if (hasMapMarker) {
    screenJoystick1.cmdId = REMOVE_CMD;
  } else {
    screenJoystick1.cmdId = ADD_OR_REFRESH_CMD;
  }
  screenJoystick1.dimSize = 160;
  sendScreenStream(&screenJoystick1, &SerialBT);
}

void addHeading() {
  screenHeadingIndicator.x = 200;
  screenHeadingIndicator.y = 450;
  if (hasMapMarker) {
    screenHeadingIndicator.cmdId = REMOVE_CMD;
  } else {
    screenHeadingIndicator.cmdId = ADD_OR_REFRESH_CMD;
  }
  screenHeadingIndicator.heading =  gVal;
  screenHeadingIndicator.dimSize = 100;
  sendScreenStream(&screenHeadingIndicator, &SerialBT);
}

void addAH() {
  screenAttitudeIndicator.x = 40;
  screenAttitudeIndicator.y = 100;
  if (hasMapMarker) {
    screenAttitudeIndicator.cmdId = REMOVE_CMD;
  } else {
    screenAttitudeIndicator.cmdId = ADD_OR_REFRESH_CMD;
  }
  screenAttitudeIndicator.roll = 10.0f + gVal;
  screenAttitudeIndicator.pitch = gVal;
  screenAttitudeIndicator.dimSize = 100;
  sendScreenStream(&screenAttitudeIndicator, &SerialBT);
}

void addSeekBar() {
  screenSeekBar.x = 40;
  screenSeekBar.y = 340;
  if (hasMapMarker) {
    screenSeekBar.cmdId = DISABLE_CMD;
  } else {
    screenSeekBar.cmdId = ENABLE_CMD;
  }
  screenSeekBar.seekValue = (int)gVal;
  screenSeekBar.maxValue = 300;
  screenSeekBar.width = 290;

  sendScreenStream(&screenSeekBar, &SerialBT);

  screenSeekBar2.x = 40;
  screenSeekBar2.y = 380;
  screenSeekBar2.cmdId = ADD_OR_REFRESH_CMD;
  screenSeekBar2.seekValue = 0;
  screenSeekBar2.maxValue = 300;
  screenSeekBar2.width = 290;
  sendScreenStream(&screenSeekBar2, &SerialBT);
}

void addSwitch() {

  screenSwitch.x = 50;
  screenSwitch.y = 270;
  if (hasMapMarker) {
    screenSwitch.cmdId = DISABLE_CMD;
  } else {
    screenSwitch.cmdId = ENABLE_CMD;
  }
  screenSwitch.switchValue = hasMapMarker;
  screenSwitch.fontSize = 30;
  screenSwitch.textColor = MAGENTA;
  screenSwitch.setlabel( "SwitchFromC++");
  sendScreenStream(&screenSwitch, &SerialBT);

  screenSwitch1.x = 50;
  screenSwitch1.y = 320;
  screenSwitch1.cmdId = ADD_OR_REFRESH_CMD;
  screenSwitch1.switchValue = !hasMapMarker;
  screenSwitch1.fontSize = 20;
  screenSwitch1.textColor = YELLOW;
  screenSwitch1.setlabel("Switch2");
  sendScreenStream(&screenSwitch1, &SerialBT);
}

uint8_t iconId = 0;
void addMapMarker()
{
  gVal += 10;
  screenMapMarker1.lat = 43.732825f;
  screenMapMarker1.lon = -79.442881f;
  screenMapMarker1.rotation = gVal;
  screenMapMarker1.iconId = iconId;
  screenMapMarker1.cmdId = ADD_OR_REFRESH_CMD;
  sendScreenStream(&screenMapMarker1, &SerialBT);
  iconId++;
  if (iconId > 11) {
    iconId = 0;
  }
  screenMapMarker2.lat = 43.733825f;
  screenMapMarker2.lon = -79.443881f;
  screenMapMarker2.rotation = gVal;
  screenMapMarker2.iconId = iconId;
  screenMapMarker2.cmdId = ADD_OR_REFRESH_CMD;
  sendScreenStream(&screenMapMarker2, &SerialBT);
}

void removeMapMarker()
{
  screenMapMarker2.cmdId = REMOVE_CMD;
  sendScreenStream(&screenMapMarker2, &SerialBT);
}

void addMap()
{
  gVal += 10;
  if (hasMap) {
    screenMap.cmdId = HIDE_CMD;
  } else {
    screenMap.cmdId = VISIBLE_CMD;
  }
  screenMap.x = 10;
  screenMap.y = 450;
  screenMap.width = 300;
  screenMap.height = 200;
  screenMap.lat = 43.730825f;
  screenMap.lon = -79.440881f;
  screenMap.mapOrientation = gVal;
  screenMap.zoom = 16;
  sendScreenStream(&screenMap, &SerialBT);
}

void addKnob()
{
  screenknob.x = 280;
  screenknob.y = 500;
  if (hasMapMarker) {
    screenknob.cmdId = DISABLE_CMD;
  } else {
    screenknob.cmdId = ENABLE_CMD;
  }
  screenknob.dimSize = 95;
  screenknob.minValue = -500;
  screenknob.maxValue = 500;
  screenknob.value = 200;
  screenknob.setlabel("Servo03");
  sendScreenStream(&screenknob, &SerialBT);
}

void addColorPicker() {
  screenColorPicker.x = 200;
  screenColorPicker.y = 300;
  screenColorPicker.cmdId = ADD_OR_REFRESH_CMD;
  screenColorPicker.dimSize = 150;
  screenColorPicker.red = 160;
  screenColorPicker.green = 190;
  screenColorPicker.blue = 220;
  sendScreenStream(&screenColorPicker, &SerialBT);
}
void addScreenCompact() {
  screenCompact.x = 20;
  screenCompact.y = 270;
  screenCompact.dimSize = 120;
  screenCompact.value = gVal;
  screenCompact.maxValue = 200.0f;
  screenCompact.drawArc = 100;
  screenCompact.arcGreenMaxVal = 100.0f;
  screenCompact.arcYellowMaxVal = 150.0f;
  screenCompact.arcRedMaxVal = 180.0f;
  screenCompact.setlabel("Temp Celcesius");
  sendScreenStream(&screenCompact, &SerialBT);
}

void addGaugeSimple() {
  screenGaugeSimple.x = 129;
  screenGaugeSimple.y = 150;
  screenGaugeSimple.dimSize = 153;
  screenGaugeSimple.value = gVal;
  screenGaugeSimple.maxValue = 250;
  screenGaugeSimple.minValue = 175;
  screenGaugeSimple.style = 0;
  screenGaugeSimple.isSymmetrical = true;
  screenGaugeSimple.color = BLUE;
  screenGaugeSimple.setlabel("Engine RPM");
  sendScreenStream(&screenGaugeSimple, &SerialBT);
}

void addGauge(ScreenGauge *gauge, BluetoothSerial *serialBT)
{
  gauge->x = 120;
  gauge->y = 500;
  gauge->dimSize = 120;
  gauge->value = gVal;
  gauge->maxValue = 200.0f;
  gauge->drawArc = 100;
  gauge->arcGreenMaxVal = 100.0f;
  gauge->arcYellowMaxVal = 150.0f;
  gauge->arcRedMaxVal = 180.0f;
  gauge->setlabel("Celcesius");
  sendScreenStream(gauge, serialBT);
}
