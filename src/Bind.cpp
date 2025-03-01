#include "Bind.h"
#include "Arduino.h"
// Set the initial value of tagIndexes to 1.
int16_t BindSeekBar::tagIndex = 1;
int16_t BindSwitch::tagIndex = 1;
int16_t BindButton::tagIndex = 1;
int16_t BindKnob::tagIndex = 1;
int16_t BindJoystick::tagIndex = 1;
int16_t BindColorPicker::tagIndex = 1;
int16_t BindTextInput::tagIndex = 1;
int16_t BindGaugeSimple::tagIndex = 1;
int16_t BindTextLabel::tagIndex = 1;
int16_t BindTerminal::tagIndex = 1;
int16_t BindChart::tagIndex = 1;
int16_t BindAttitudeIndicator::tagIndex = 1;
int16_t BindGauge::tagIndex = 1;
int16_t BindGaugeCompact::tagIndex = 1;
int16_t BindHeadingIndicator::tagIndex = 1;
int16_t BindMapMarker::tagIndex = 1;
int16_t BindRectangle::tagIndex = 1;
int16_t BindDialog::tagIndex = 1;

bool Bind::init(Stream &stream, void (&_setupCallback)(int16_t, int16_t))
{
  return internalInit(&stream, &_setupCallback);
}

bool Bind::internalInit(Stream *stream, void (*_setupCallback)(int16_t, int16_t))
{
  if (stream != NULL && _setupCallback != NULL)
  {
    bindStream = stream;
    setupCallback = _setupCallback;
    return true;
  }
  else
  {
    return false;
  }
}

void Bind::sync(float chartData, BindChart &obj)
{
  if (bindStream != NULL)
  {
    dataLen = obj.getDataBytes(bufFrame, chartData);
    DataParser::sendFrame(frameTXBuffer, bufFrame, dataLen, bindStream);
  }
}

void Bind::sync(const char *str, int32_t textColor, bool autoScroll, bool newLine, bool bold, bool italic, BindTerminal &obj)
{
  if (bindStream != NULL)
  {
    dataLen = obj.getDataBytes(bufFrame, str, textColor, autoScroll, newLine, bold, italic);
    DataParser::sendFrame(frameTXBuffer, bufFrame, dataLen, bindStream);
  }
}

void Bind::sync(const char *str, BindTerminal &obj)
{
  sync(str, WHITE, true, true, false, false, obj);
}

void Bind::internalSync(BindView *obj)
{
  if (bindStream != NULL)
  {
    dataLen = obj->getBytes(bufFrame);
    DataParser::sendFrame(frameTXBuffer, bufFrame, dataLen, bindStream);
  }
}

void Bind::sync(BindView &obj)
{
  internalSync(&obj);
}

void Bind::sync(BindSwitch &obj)
{
  switchObjects[obj.tag] = &obj;
  internalSync(&obj);
}

void Bind::sync(BindButton &obj)
{
  buttonObjects[obj.tag] = &obj;
  internalSync(&obj);
}

void Bind::sync(BindKnob &obj)
{
  knobObjects[obj.tag] = &obj;
  internalSync(&obj);
}

void Bind::sync(BindSeekBar &obj)
{
  seekBarObjects[obj.tag] = &obj;
  internalSync(&obj);
}

void Bind::sync(BindJoystick &obj)
{
  joystickObjects[obj.tag] = &obj;
  internalSync(&obj);
}

void Bind::sync(BindColorPicker &obj)
{
  colorPickerObjects[obj.tag] = &obj;
  internalSync(&obj);
}

void Bind::sync(BindTextInput &obj)
{
  textInputObjects[obj.tag] = &obj;
  internalSync(&obj);
}

void Bind::sync(BindDialog &obj)
{
  obj.hasResult = false;
  dialogObjects[obj.tag] = &obj;
  internalSync(&obj);
}

void Bind::sync(const uint8_t *buffer, size_t size)
{
  while (size > 0)
  {
    updateScreen(*buffer++);
    size--;
  }
}

void Bind::sync()
{
  if (bindStream != NULL)
  {
    while (bindStream->available())
    {
      updateScreen(bindStream->read());
    }
  }
}

int Bind::updateScreen(uint8_t inp)
{
  if (dataParser.update(inp) > 0)
  {
    return updateScreenInternal(dataParser.buf);
  }
  return 0;
}

void Bind::updateScreen(Stream *stream)
{
  while (stream->available())
  {
    updateScreen(stream->read());
  }
}

int Bind::updateScreenInternal(uint8_t *dataFrame)
{
  if ((millis() - lastMs) < 5)
  {
#ifdef DEBUG_MSG
    Serial.println("\nToo fast!\n");
#endif
    delay(5);
  }
  lastMs = millis();
  uint8_t textLength = 0;
  switch (dataFrame[2])
  {
  case BIND_ID_SETUP_CMD:
    valTmp1 = ((0xFFFF & dataFrame[4]) << 8) | (dataFrame[3] & 0xFF);
    valTmp2 = ((0xFFFF & dataFrame[6]) << 8) | (dataFrame[5] & 0xFF);
    screenInit(valTmp1, valTmp2);
    break;
  case BIND_ID_BUTTON:
    clickButton(dataFrame[3]);
    break;
  case BIND_ID_KNOB:
    valTmp1 = ((0xFFFF & dataFrame[6]) << 8) | (dataFrame[5] & 0xFF);
    knobChanged(dataFrame[3], valTmp1);
    break;
  case BIND_ID_TOGGLE_SWITCH:
    updateSwitch(dataFrame[3], dataFrame[5] == 1);
    break;
  case BIND_ID_SEEK_BAR:
    valTmp1 = ((0xFFFF & dataFrame[6]) << 8) | (dataFrame[5] & 0xFF);
    updateSeekBar(dataFrame[3], valTmp1);
    break;
  case BIND_ID_JOYSTICK:
    valTmp1 = ((0xFFFF & dataFrame[6]) << 8) | (dataFrame[5] & 0xFF);
    valTmp2 = ((0xFFFF & dataFrame[8]) << 8) | (dataFrame[7] & 0xFF);
    updateJoystick(dataFrame[3], valTmp1, valTmp2);
    break;
  case BIND_ID_COLOR_PICKER:
    valTmp1 = (dataFrame[5] & 0xFF);
    valTmp2 = (dataFrame[6] & 0xFF);
    valTmp3 = (dataFrame[7] & 0xFF);
    updateColorPicker(dataFrame[3], valTmp1, valTmp2, valTmp3);
    break;
  case BIND_ID_TEXTINPUT:
    updateTextInput(dataFrame[3], (const char *)&dataFrame[6], dataFrame[5]);
    break;
  case BIND_ID_DIALOG:
    dialogResult(dataFrame[3], dataFrame[5] == 1, (const char *)&dataFrame[7], dataFrame[6]);
    break;
  default:
    return 0;
    break;
  }
  return dataFrame[2];
}

void Bind::screenInit(int16_t w, int16_t h)
{
  if (*setupCallback != NULL)
  {
    setupCallback(w, h);
    isInitialized = true;
  }
}

void Bind::knobChanged(int8_t tag, int val)
{
  if (tag < MAX_HANDLERS && knobObjects[tag] != nullptr)
  {
    knobObjects[tag]->invokeCallback(val);
  }

}

void Bind::clickButton(uint8_t tag)
{
  if (tag < MAX_HANDLERS && buttonObjects[tag] != nullptr)
  {
    buttonObjects[tag]->invokeCallback();
  }
}

void Bind::updateSwitch(uint8_t tag, bool val)
{
  if (tag < MAX_HANDLERS && switchObjects[tag] != nullptr)
  {
    switchObjects[tag]->invokeCallback(val);
  }
}

void Bind::updateSeekBar(uint8_t tag, int16_t val)
{
  if (tag < MAX_HANDLERS && seekBarObjects[tag] != nullptr)
  {
    seekBarObjects[tag]->invokeCallback(val);
  }
}

void Bind::updateJoystick(uint8_t tag, int16_t valX, int16_t valY)
{
  if (tag < MAX_HANDLERS && joystickObjects[tag] != nullptr)
  {
    joystickObjects[tag]->invokeCallback(valX, valY);
  }
}

void Bind::updateColorPicker(uint8_t tag, uint8_t r, uint8_t g, uint8_t b)
{
  if (tag < MAX_HANDLERS && colorPickerObjects[tag] != nullptr)
  {
    colorPickerObjects[tag]->invokeCallback(r, g, b);
  }
}

void Bind::updateTextInput(uint8_t tag, const char *val, uint8_t length)
{
  if (tag < MAX_HANDLERS && textInputObjects[tag] != nullptr)
  {
    char value[length +1];
    strncpy((char*)value, val, length);
    value[length] = '\0';
    textInputObjects[tag]->invokeCallback(value, length);
  }
}

void Bind::dialogResult(uint8_t tag, bool result, const char *text, uint8_t length)
{

#ifdef DEBUG_MSG
    Serial.print("Bind::dialogResult");
    Serial.print(tag);
    Serial.print(" ");
    Serial.println(result);
#endif

  if (tag < MAX_HANDLERS && dialogObjects[tag] != nullptr)
  {
    char value[length +1];
    strncpy((char*)value, text, length);
    value[length] = '\0';
    dialogObjects[tag]->invokeCallback(result, value);
  }
}
