#include "Bind.hpp"
int dLenght = 0;
uint8_t bufFrame[100];
int frameBufferSize = 0;
uint8_t frameTXBuffer[MAX_DATA_LENGHT + 6];
int16_t tagIndex = 1;

ScreenStreamAutoTag::ScreenStreamAutoTag() {
  this->tag = tagIndex++;
}

void ScreenTerminalPrint(const char *str, ScreenTerminal *obj, Stream *stream){
  ScreenTerminalPrint(str, WHITE, true, false, false, false, obj, stream);
}

void ScreenTerminalPrintln(const char *str, ScreenTerminal *obj, Stream *stream){
  ScreenTerminalPrint(str, WHITE, true, false, true, false, obj, stream);
}

void copyAndOffset(uint8_t *out, uint16_t *offset, const void * source, size_t num) {
  memcpy(out + (*offset), source, num);
  *offset += num;
}

void ScreenTerminalPrint(const char *str, int32_t textColor, bool autoScroll, bool newLine, bool bold, bool italic, ScreenTerminal *obj, Stream *stream){
  dLenght = obj->getDataBytes(bufFrame, str, textColor, autoScroll, newLine, bold, italic);
  frameBufferSize = sendFrame(frameTXBuffer, bufFrame, dLenght);
  if (frameBufferSize > 0) {
    stream->write(frameTXBuffer, frameBufferSize);
  }
}

void addChartdata(float chartData, ScreenChart *obj, Stream *stream) {
  dLenght = obj->getDataBytes(bufFrame, chartData);
  frameBufferSize = sendFrame(frameTXBuffer, bufFrame, dLenght);
  if (frameBufferSize > 0) {
    stream->write(frameTXBuffer, frameBufferSize);
  }
}

void sendScreenStream(ScreenStream *obj, Stream *stream) {
  dLenght = obj->getBytes(bufFrame);
  frameBufferSize = sendFrame(frameTXBuffer, bufFrame, dLenght);
  if (frameBufferSize > 0) {
    stream->write(frameTXBuffer, frameBufferSize);
  }
}


void ScreenObjects::registerButton(ScreenButton * screenButton, void (*clickCallback)(void)) {
  if (buttonIndex < maxObjects) {
    screenButton->tag = buttonIndex++;
    buttons[screenButton->tag] = Button(clickCallback);
  }
}

void ScreenObjects::registerDialKnob(ScreenKnob * screenKnob, void (*changeCallback)(int16_t)) {
  if (dialKnobIndex < maxObjects) {
    screenKnob->tag = dialKnobIndex++;
    dialKnobs[screenKnob->tag] = DialKnob(&screenKnob->value, changeCallback);
  }
}

int ScreenObjects::updateScreen(uint8_t inp) {
  if (dataParser.update(inp) > 0) {
    return updateScreenInternal(dataParser.buf);
  }
  return 0;
}

int ScreenObjects::updateScreenInternal(uint8_t *dataFrame) {
  switch (dataFrame[2]) {
     case ScreenIDs::setupCMD:
      screenInit();
      break;
    case ScreenIDs::button:
      clickButton(dataFrame[3]);
      break;
    case ScreenIDs::knob:
      valTmp1 = ((0xFFFF & dataFrame[6]) << 8) | (dataFrame[5] & 0xFF);
      knobChanged(dataFrame[3], valTmp1);
      break;
    case ScreenIDs::toggleSwitch:
      updateSwitch(dataFrame[3], dataFrame[5] == 1);
      break;
    case ScreenIDs::seekBar:
      valTmp1 = ((0xFFFF & dataFrame[6]) << 8) | (dataFrame[5] & 0xFF);
      updateSeekBar(dataFrame[3], valTmp1);
      break;
    case ScreenIDs::joystick:
      valTmp1 = ((0xFFFF & dataFrame[6]) << 8) | (dataFrame[5] & 0xFF);
      valTmp2 = ((0xFFFF & dataFrame[8]) << 8) | (dataFrame[7] & 0xFF);
      updateJoystick(dataFrame[3], valTmp1, valTmp2);
      break;
    case ScreenIDs::colorPicker:
      valTmp1 = (dataFrame[5] & 0xFF);
      valTmp2 = (dataFrame[6] & 0xFF);
      valTmp3 = (dataFrame[7] & 0xFF);
      updateColorPicker(dataFrame[3], valTmp1, valTmp2, valTmp3);
      break;
    default:
      return 0;
  }
  return dataFrame[2];
}

void ScreenObjects::screenInit() {
  if (*setupCallback != NULL) {
    setupCallback();
  }
}

void ScreenObjects::registerScreenSetup(void (*_setupCallback)(void)){
  setupCallback = _setupCallback;
}

void ScreenObjects::knobChanged(int8_t tag, int val) {
  if (tag < maxObjects) {
    dialKnobs[tag].changed(val);
  }
}

void ScreenObjects::clickButton(uint8_t tag) {
  if (tag < maxObjects) {
    buttons[tag].clicked();
  }
}

void ScreenObjects::registerSwitch(ScreenSwitch * screenSwitch, void (*clickCallback)(bool)) {
  if (switchIndex < maxObjects) {
    screenSwitch->tag = switchIndex++;
    switchs[screenSwitch->tag] = Switch(&screenSwitch->switchValue, clickCallback);
  }
}

void ScreenObjects::updateSwitch(uint8_t tag, bool val) {
  if (tag < maxObjects) {
    switchs[tag].update(val);
  }
}

void ScreenObjects::registerSeekBar(ScreenSeekBar * screenSeekBar, void (*changeCallback)(int16_t)) {
  if (SeekBarIndex < maxObjects) {
    screenSeekBar->tag = SeekBarIndex++;
    seekBars[screenSeekBar->tag] = SeekBar(&screenSeekBar->seekValue, changeCallback);
  }
}

void ScreenObjects::updateSeekBar(uint8_t tag, int16_t val) {
  if (tag < maxObjects) {
    seekBars[tag].update(val);
  }
}

void ScreenObjects::registerJoystick(ScreenJoystick * screenJoystick, void (*changeCallback)(int16_t, int16_t)) {
  if (JoystickHandlerIndex < maxObjects) {
    screenJoystick->tag = JoystickHandlerIndex++;
    joystickHandlers[screenJoystick->tag] = JoystickHandler(&screenJoystick->sX, &screenJoystick->sY, changeCallback);
  }
}

void ScreenObjects::updateJoystick(uint8_t tag, int16_t valX, int16_t valY) {
  if (tag < maxObjects) {
    joystickHandlers[tag].update(valX, valY);
  }
}

void ScreenObjects::registerColorPicker(ScreenColorPicker * screenColorPicker, void (*clickCallback)(uint8_t, uint8_t, uint8_t)) {
  if (ColorPickerHandlerIndex < maxObjects) {
    screenColorPicker->tag = ColorPickerHandlerIndex++;
    colorPickerHandlers[screenColorPicker->tag] = ColorPickerHandler(&screenColorPicker->red, &screenColorPicker->green, &screenColorPicker->blue, clickCallback);
  }
}

void ScreenObjects::updateColorPicker(uint8_t tag, uint8_t r, uint8_t g, uint8_t b) {
  if (tag < maxObjects) {
    colorPickerHandlers[tag].update(r, g, b);
  }
}
