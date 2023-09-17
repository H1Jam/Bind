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
  DataParser::sendFrame(frameTXBuffer, bufFrame, dLenght, stream);
}

void addChartdata(float chartData, ScreenChart *obj, Stream *stream) {
  dLenght = obj->getDataBytes(bufFrame, chartData);
  DataParser::sendFrame(frameTXBuffer, bufFrame, dLenght, stream);
}

void sendScreenStream(ScreenStream *obj, Stream *stream) {
  dLenght = obj->getBytes(bufFrame);
  DataParser::sendFrame(frameTXBuffer, bufFrame, dLenght, stream);
}


void Bind::setBindDevice(Stream *stream){
	bindStream = stream;
}

void Bind::sync(ScreenStream *obj) {
  if (bindStream !=NULL) {
    static int len = obj->getBytes(bufFrame);
    DataParser::sendFrame(frameTXBuffer, bufFrame, len, stream); 
  }
}

void Bind::bindButton(ScreenButton * screenButton, void (*clickCallback)(void)) {
  if (buttonIndex < maxObjects) {
    screenButton->tag = buttonIndex++;
    buttons[screenButton->tag] = Button(clickCallback);
  }
}

void Bind::bindDialKnob(ScreenKnob * screenKnob, void (*changeCallback)(int16_t)) {
  if (dialKnobIndex < maxObjects) {
    screenKnob->tag = dialKnobIndex++;
    dialKnobs[screenKnob->tag] = DialKnob(&screenKnob->value, changeCallback);
  }
}

int Bind::updateScreen(uint8_t inp) {
  if (dataParser.update(inp) > 0) {
    return updateScreenInternal(dataParser.buf);
  }
  return 0;
}

void Bind::updateScreen(Stream *stream) {
	while (stream->available()) {
		updateScreen(stream->read());
	}
}

int Bind::updateScreenInternal(uint8_t *dataFrame) {
  switch (dataFrame[2]) {
    case ScreenIDs::setupCMD:
	  valTmp1 = ((0xFFFF & dataFrame[4]) << 8) | (dataFrame[3] & 0xFF);
      valTmp2 = ((0xFFFF & dataFrame[6]) << 8) | (dataFrame[5] & 0xFF);
      screenInit(valTmp1, valTmp2);
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

void Bind::screenInit(int16_t w, int16_t h) {
  if (*setupCallback != NULL) {
    setupCallback(w, h);
	init = true;
  }
}

void Bind::bindScreenSetup(void (*_setupCallback)(int16_t, int16_t)){
  setupCallback = _setupCallback;
}

void Bind::knobChanged(int8_t tag, int val) {
  if (tag < maxObjects) {
    dialKnobs[tag].changed(val);
  }
}

void Bind::clickButton(uint8_t tag) {
  if (tag < maxObjects) {
    buttons[tag].clicked();
  }
}

void Bind::bindSwitch(ScreenSwitch * screenSwitch, void (*clickCallback)(bool)) {
  if (switchIndex < maxObjects) {
    screenSwitch->tag = switchIndex++;
    switchs[screenSwitch->tag] = Switch(&screenSwitch->switchValue, clickCallback);
  }
}

void Bind::updateSwitch(uint8_t tag, bool val) {
  if (tag < maxObjects) {
    switchs[tag].update(val);
  }
}

void Bind::bindSeekBar(ScreenSeekBar * screenSeekBar, void (*changeCallback)(int16_t)) {
  if (SeekBarIndex < maxObjects) {
    screenSeekBar->tag = SeekBarIndex++;
    seekBars[screenSeekBar->tag] = SeekBar(&screenSeekBar->seekValue, changeCallback);
  }
}

void Bind::updateSeekBar(uint8_t tag, int16_t val) {
  if (tag < maxObjects) {
    seekBars[tag].update(val);
  }
}

void Bind::bindJoystick(ScreenJoystick * screenJoystick, void (*changeCallback)(int16_t, int16_t)) {
  if (JoystickHandlerIndex < maxObjects) {
    screenJoystick->tag = JoystickHandlerIndex++;
    joystickHandlers[screenJoystick->tag] = JoystickHandler(&screenJoystick->sX, &screenJoystick->sY, changeCallback);
  }
}

void Bind::updateJoystick(uint8_t tag, int16_t valX, int16_t valY) {
  if (tag < maxObjects) {
    joystickHandlers[tag].update(valX, valY);
  }
}

void Bind::bindColorPicker(ScreenColorPicker * screenColorPicker, void (*clickCallback)(uint8_t, uint8_t, uint8_t)) {
  if (ColorPickerHandlerIndex < maxObjects) {
    screenColorPicker->tag = ColorPickerHandlerIndex++;
    colorPickerHandlers[screenColorPicker->tag] = ColorPickerHandler(&screenColorPicker->red, &screenColorPicker->green, &screenColorPicker->blue, clickCallback);
  }
}

void Bind::updateColorPicker(uint8_t tag, uint8_t r, uint8_t g, uint8_t b) {
  if (tag < maxObjects) {
    colorPickerHandlers[tag].update(r, g, b);
  }
}
