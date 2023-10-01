#include "Bind.hpp"

bool Bind::init(Stream *stream, void (*_setupCallback)(int16_t, int16_t))
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

void Bind::sync(float chartData, BindChart *obj)
{
  if (bindStream != NULL)
  {
    dataLen = obj->getDataBytes(bufFrame, chartData);
    DataParser::sendFrame(frameTXBuffer, bufFrame, dataLen, bindStream);
  }
}

void Bind::sync(const char *str, int32_t textColor, bool autoScroll, bool newLine, bool bold, bool italic, BindTerminal *obj)
{
  if (bindStream != NULL)
  {
    dataLen = obj->getDataBytes(bufFrame, str, textColor, autoScroll, newLine, bold, italic);
    DataParser::sendFrame(frameTXBuffer, bufFrame, dataLen, bindStream);
  }
}

void Bind::sync(const char *str, BindTerminal *obj)
{
  sync(str, WHITE, true, true, false, false, obj);
}

void Bind::sync(BindView *obj)
{
  if (bindStream != NULL)
  {
    dataLen = obj->getBytes(bufFrame);
    DataParser::sendFrame(frameTXBuffer, bufFrame, dataLen, bindStream);
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

void Bind::join(BindButton *screenButton, void (*clickCallback)(void))
{
  if (buttonIndex < MAX_HANDLERS)
  {
    screenButton->tag = buttonIndex++;
    buttons[screenButton->tag] = ButtonHandler(clickCallback);
  }
}

void Bind::join(BindKnob *screenKnob, void (*changeCallback)(int16_t))
{
  if (dialKnobIndex < MAX_HANDLERS)
  {
    screenKnob->tag = dialKnobIndex++;
    dialKnobHandlers[screenKnob->tag] = DialKnobHandler(&screenKnob->value, changeCallback);
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
  default:
    return 0;
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
  if (tag < MAX_HANDLERS)
  {
    dialKnobHandlers[tag].changed(val);
  }
}

void Bind::clickButton(uint8_t tag)
{
  if (tag < MAX_HANDLERS)
  {
    buttons[tag].clicked();
  }
}

void Bind::join(BindSwitch *screenSwitch, void (*clickCallback)(bool))
{
  if (switchIndex < MAX_HANDLERS)
  {
    screenSwitch->tag = switchIndex++;
    switchHandlers[screenSwitch->tag] = SwitchHandler(&screenSwitch->switchValue, clickCallback);
  }
}

void Bind::updateSwitch(uint8_t tag, bool val)
{
  if (tag < MAX_HANDLERS)
  {
    switchHandlers[tag].update(val);
  }
}

void Bind::join(BindSeekBar *screenSeekBar, void (*changeCallback)(int16_t))
{
  if (seekBarIndex < MAX_HANDLERS)
  {
    screenSeekBar->tag = seekBarIndex++;
    seekBarHandlers[screenSeekBar->tag] = SeekBarHandler(&screenSeekBar->seekValue, changeCallback);
  }
}

void Bind::updateSeekBar(uint8_t tag, int16_t val)
{
  if (tag < MAX_HANDLERS)
  {
    seekBarHandlers[tag].update(val);
  }
}

void Bind::join(BindJoystick *screenJoystick, void (*changeCallback)(int16_t, int16_t))
{
  if (joystickHandlerIndex < MAX_HANDLERS)
  {
    screenJoystick->tag = joystickHandlerIndex++;
    joystickHandlers[screenJoystick->tag] = JoystickHandler(&screenJoystick->sX, &screenJoystick->sY, changeCallback);
  }
}

void Bind::updateJoystick(uint8_t tag, int16_t valX, int16_t valY)
{
  if (tag < MAX_HANDLERS)
  {
    joystickHandlers[tag].update(valX, valY);
  }
}

void Bind::join(BindColorPicker *screenColorPicker, void (*clickCallback)(uint8_t, uint8_t, uint8_t))
{
  if (colorPickerHandlerIndex < MAX_HANDLERS)
  {
    screenColorPicker->tag = colorPickerHandlerIndex++;
    colorPickerHandlers[screenColorPicker->tag] = ColorPickerHandler(&screenColorPicker->red, &screenColorPicker->green, &screenColorPicker->blue, clickCallback);
  }
}

void Bind::updateColorPicker(uint8_t tag, uint8_t r, uint8_t g, uint8_t b)
{
  if (tag < MAX_HANDLERS)
  {
    colorPickerHandlers[tag].update(r, g, b);
  }
}
