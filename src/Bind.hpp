#ifndef __BIND_H
#define __BIND_H
#include <stdint.h>
#include "Stream.h"
#include "DataProtocol.h"
#include "BindButton.hpp"
#include "BindDialKnob.hpp"
#include "BindSwitch.hpp"

#define maxObjects  8
#define MAX_SINK_OBJECTS  100
#define ADD_OR_REFRESH_CMD 0
#define REMOVE_CMD 1
#define DISABLE_CMD 2
#define ENABLE_CMD 3
#define HIDE_CMD 4
#define VISIBLE_CMD 5

class SeekBar {
  private:
    int16_t * value = NULL;
  public:
    SeekBar() {
      SeekBar(NULL);
    }
    SeekBar(int16_t *val) {
      value = val;
    }
    void update(int16_t val) {
      if (value != NULL) {
        *value = val;
      }
    }
};

class JoystickHandler {
  private:
    int16_t * valueX = NULL;
    int16_t * valueY = NULL;
  public:
    JoystickHandler() {
      JoystickHandler(NULL, NULL);
    }
    JoystickHandler(int16_t *valX, int16_t *valY) {
      valueX = valX;
      valueY = valY;
    }
    void update(int16_t valX, int16_t valY) {
      if (valueX != NULL && valueY != NULL) {
        *valueX = valX;
        *valueY = valY;
      }
    }
};

class ColorPickerHandler {
  private:
    void (*clickCallback)(uint8_t, uint8_t, uint8_t);
    uint8_t * red = NULL;
    uint8_t * green = NULL;
    uint8_t * blue = NULL;
  public:
    ColorPickerHandler() {
      ColorPickerHandler(NULL, NULL, NULL, NULL);
    }
    ColorPickerHandler(uint8_t *r, uint8_t *g, uint8_t *b, void (*_clickCallback)(uint8_t, uint8_t, uint8_t)) {
      red = r;
      green = g;
      blue = b;
	  clickCallback = _clickCallback;
    }
    void update(uint8_t r, uint8_t g, uint8_t b) {
      if (red != NULL && green != NULL && blue != NULL) {
        *red = r;
        *green = g;
        *blue = b;
      }
	  if (*clickCallback != NULL) {
        clickCallback(r, g ,b);
      }
    }
};


void copyAndOffset(uint8_t *out, uint16_t *offset, const void * source, size_t num);
class ScreenStream {
  public:
    virtual uint16_t getBytes(uint8_t *out) {};
    int16_t tag;
};

class ScreenStreamAutoTag : public ScreenStream {
  public:
    ScreenStreamAutoTag();
};

class ScreenTextLabel: public ScreenStreamAutoTag {
  private:
    uint8_t objID = ScreenIDs::label;
    uint16_t offset = 0;
    int strLength = 0;
    const char *str;
  public:
    void setlabel(const char *cstr) {
      str = cstr;
    }
    int16_t x;
    int16_t y;
    uint8_t cmdId = 0;
    int16_t fontSize;
    int32_t color;
    uint16_t getBytes(uint8_t *out) override {
      offset = 0;
      strLength = strlen(str);
      if (strLength > MAX_STRING_LENGTH_TERMINAL) {
        strLength = MAX_STRING_LENGTH_TERMINAL;
      }
      copyAndOffset(out, &offset, &objID, sizeof(objID));
      copyAndOffset(out, &offset, &x, sizeof(x));
      copyAndOffset(out, &offset, &y, sizeof(y));
      copyAndOffset(out, &offset, &tag, sizeof(tag));
      copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
      copyAndOffset(out, &offset, &fontSize, sizeof(fontSize));
      copyAndOffset(out, &offset, &color, sizeof(color));
      copyAndOffset(out, &offset, str, strLength);
      return offset;
    }
};

class ScreenButton: public ScreenStream {
  private:
    uint8_t objID = ScreenIDs::button;
    uint16_t offset = 0;
    int strLength = 0;
    const char *str;
  public:
    int16_t x;
    int16_t y;
    uint8_t cmdId = 0;
    int16_t fontSize;
    int32_t color;
    int32_t backColor;
    void setlabel(const char *cstr) {
      str = cstr;
    }
    uint16_t getBytes(uint8_t *out) override {
      offset = 0;
      strLength = strlen(str);
      if (strLength > MAX_STRING_LENGTH_TERMINAL) {
        strLength = MAX_STRING_LENGTH_TERMINAL;
      }
      copyAndOffset(out, &offset, &objID, sizeof(objID));
      copyAndOffset(out, &offset, &x, sizeof(x));
      copyAndOffset(out, &offset, &y, sizeof(y));
      copyAndOffset(out, &offset, &tag, sizeof(tag));
      copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
      copyAndOffset(out, &offset, &fontSize, sizeof(fontSize));
      copyAndOffset(out, &offset, &color, sizeof(color));
      copyAndOffset(out, &offset, &backColor, sizeof(backColor));
      copyAndOffset(out, &offset, str, strLength);
      return offset;
    }
};

class ScreenKnob: public ScreenStream {
  private:
    uint8_t objID = ScreenIDs::knob;
    uint16_t offset = 0;
    int strLength = 0;
    const char *str;
  public:
    int16_t x;
    int16_t y;
    uint8_t cmdId = 0;
    int16_t dimSize;
    int16_t minValue;
    int16_t maxValue;
    int16_t value;
    void setlabel(const char *cstr) {
      str = cstr;
    }
    uint16_t getBytes(uint8_t *out) override {
      offset = 0;
      strLength = strlen(str);
      if (strLength > MAX_STRING_LENGTH_TERMINAL) {
        strLength = MAX_STRING_LENGTH_TERMINAL;
      }
      copyAndOffset(out, &offset, &objID, sizeof(objID));
      copyAndOffset(out, &offset, &x, sizeof(x));
      copyAndOffset(out, &offset, &y, sizeof(y));
      copyAndOffset(out, &offset, &tag, sizeof(tag));
      copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
      copyAndOffset(out, &offset, &dimSize, sizeof(dimSize));
      copyAndOffset(out, &offset, &minValue, sizeof(minValue));
      copyAndOffset(out, &offset, &maxValue, sizeof(maxValue));
      copyAndOffset(out, &offset, &value, sizeof(value));
      copyAndOffset(out, &offset, str, strLength);
      return offset;
    }
};

class ScreenGauge: public ScreenStreamAutoTag {
  private:
    uint8_t objID = ScreenIDs::gauge1;
    uint16_t offset = 0;
    int strLength = 0;
    const char *str;
  public:
    int16_t x;
    int16_t y;
    uint8_t cmdId = 0;
    int16_t dimSize = 100;
    float value = 0;
    float maxValue = 100.0f;
    uint8_t drawArc = 0;
    float arcGreenMaxVal = 0;
    float arcYellowMaxVal = 0;
    float arcRedMaxVal = 0;
    void setlabel(const char *cstr) {
      str = cstr;
    }
    uint16_t getBytes(uint8_t *out) override {
      offset = 0;
      strLength = strlen(str);
      if (strLength > MAX_STRING_LENGTH_TERMINAL) {
        strLength = MAX_STRING_LENGTH_TERMINAL;
      }
      copyAndOffset(out, &offset, &objID, 1);
      copyAndOffset(out, &offset, &x, sizeof(x));
      copyAndOffset(out, &offset, &y, sizeof(y));
      copyAndOffset(out, &offset, &tag, sizeof(tag));
      copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
      copyAndOffset(out, &offset, &dimSize, sizeof(dimSize));
      copyAndOffset(out, &offset, &value, sizeof(value));
      copyAndOffset(out, &offset, &maxValue, sizeof(maxValue));
      copyAndOffset(out, &offset, &drawArc, sizeof(drawArc));
      copyAndOffset(out, &offset, &arcGreenMaxVal, sizeof(arcGreenMaxVal));
      copyAndOffset(out, &offset, &arcYellowMaxVal, sizeof(arcYellowMaxVal));
      copyAndOffset(out, &offset, &arcRedMaxVal, sizeof(arcRedMaxVal));
      copyAndOffset(out, &offset, str, strLength);
      return offset;
    }
};

class ScreenGaugeCompact: public ScreenStreamAutoTag {
  private:
    uint8_t objID = ScreenIDs::gauge2;
    uint16_t offset = 0;
    int strLength = 0;
    const char *str;
  public:
    int16_t x;
    int16_t y;
    uint8_t cmdId = 0;
    int16_t dimSize = 100;
    float value = 0;
    float maxValue = 100.0f;
    uint8_t drawArc = 0;
    float arcGreenMaxVal = 0;
    float arcYellowMaxVal = 0;
    float arcRedMaxVal = 0;
    void setlabel(const char *cstr) {
      str = cstr;
    }
    uint16_t getBytes(uint8_t *out) override {
      offset = 0;
      strLength = strlen(str);
      if (strLength > MAX_STRING_LENGTH_TERMINAL) {
        strLength = MAX_STRING_LENGTH_TERMINAL;
      }
      copyAndOffset(out, &offset, &objID, sizeof(objID));
      copyAndOffset(out, &offset, &x, sizeof(x));
      copyAndOffset(out, &offset, &y, sizeof(y));
      copyAndOffset(out, &offset, &tag, sizeof(tag));
      copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
      copyAndOffset(out, &offset, &dimSize, sizeof(dimSize));
      copyAndOffset(out, &offset, &value, sizeof(value));
      copyAndOffset(out, &offset, &maxValue, sizeof(maxValue));
      copyAndOffset(out, &offset, &drawArc, sizeof(drawArc));
      copyAndOffset(out, &offset, &arcGreenMaxVal, sizeof(arcGreenMaxVal));
      copyAndOffset(out, &offset, &arcYellowMaxVal, sizeof(arcYellowMaxVal));
      copyAndOffset(out, &offset, &arcRedMaxVal, sizeof(arcRedMaxVal));
      copyAndOffset(out, &offset, str, strLength);
      return offset;
    }
};


class ScreenMap: public ScreenStreamAutoTag  {
  private:
    uint8_t objID = ScreenIDs::mapView;
    uint16_t offset = 0;
  public:
    int16_t x;
    int16_t y;
    uint8_t cmdId = 0;
    int16_t width = 100;
    int16_t height = 100;
    float lat = 0.0f;
    float lon = 0.0f;
    float mapOrientation = 0.0f;
    uint8_t zoom = 1;
    uint16_t getBytes(uint8_t *out) override {
      tag = 1; // Only one map for now! will extend it.
      offset = 0;
      copyAndOffset(out, &offset, &objID, sizeof(objID));
      copyAndOffset(out, &offset, &x, sizeof(x));
      copyAndOffset(out, &offset, &y, sizeof(y));
      copyAndOffset(out, &offset, &tag, sizeof(tag));
      copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
      copyAndOffset(out, &offset, &width, sizeof(width));
      copyAndOffset(out, &offset, &height, sizeof(height));
      copyAndOffset(out, &offset, &lat, sizeof(lat));
      copyAndOffset(out, &offset, &lon, sizeof(lon));
      copyAndOffset(out, &offset, &mapOrientation, sizeof(mapOrientation));
      copyAndOffset(out, &offset, &zoom, sizeof(zoom));
      return offset;
    }
};

class ScreenMapMarker: public ScreenStreamAutoTag  {
  private:
    uint8_t objID = ScreenIDs::mapMarker;
    uint16_t offset = 0;
  public:
    float lat = 0.0f;
    float lon = 0.0f;
    float rotation = 0.0f;
    uint8_t iconId = 0;
    uint8_t cmdId = 0;
    uint16_t getBytes(uint8_t *out) override {
      offset = 0;
      copyAndOffset(out, &offset, &objID, sizeof(objID));
      copyAndOffset(out, &offset, &tag, sizeof(tag));
      copyAndOffset(out, &offset, &lat, sizeof(lat));
      copyAndOffset(out, &offset, &lon, sizeof(lon));
      copyAndOffset(out, &offset, &rotation, sizeof(rotation));
      copyAndOffset(out, &offset, &iconId, sizeof(iconId));
      copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
      return offset;
    }
};

class ScreenSwitch: public ScreenStream  {
  private:
    uint8_t objID = ScreenIDs::toggleSwitch;
    uint16_t offset = 0;
    int strLength = 0;
    const char *str;
  public:
    int16_t x;
    int16_t y;
    uint8_t cmdId = 0;
    bool switchValue;
    int16_t fontSize;
    int32_t textColor;
    void setlabel(const char *cstr) {
      str = cstr;
    }
    uint16_t getBytes(uint8_t *out) override {
      offset = 0;
      strLength = strlen(str);
      if (strLength > MAX_STRING_LENGTH_TERMINAL) {
        strLength = MAX_STRING_LENGTH_TERMINAL;
      }
      copyAndOffset(out, &offset, &objID, sizeof(objID));
      copyAndOffset(out, &offset, &x, 2);
      copyAndOffset(out, &offset, &y, 2);
      copyAndOffset(out, &offset, &tag, 2);
      copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
      copyAndOffset(out, &offset, &switchValue, sizeof(switchValue));
      copyAndOffset(out, &offset, &fontSize, sizeof(fontSize));
      copyAndOffset(out, &offset, &textColor, sizeof(textColor));
      copyAndOffset(out, &offset, str, strLength);
      return offset;
    }
};

class ScreenSeekBar: public ScreenStream  {
  private:
    uint8_t objID = ScreenIDs::seekBar;
    uint16_t offset = 0;
  public:
    int16_t x = 0;
    int16_t y = 0;
    uint8_t cmdId = 0;
    int16_t seekValue = 0;
    int16_t maxValue = 100;
    int16_t width = 200;
    uint16_t getBytes(uint8_t *out) override {
      offset = 0;
      copyAndOffset(out, &offset, &objID, sizeof(objID));
      copyAndOffset(out, &offset, &x, 2);
      copyAndOffset(out, &offset, &y, 2);
      copyAndOffset(out, &offset, &tag, 2);
      copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
      copyAndOffset(out, &offset, &seekValue, sizeof(seekValue));
      copyAndOffset(out, &offset, &maxValue, sizeof(maxValue));
      copyAndOffset(out, &offset, &width, sizeof(width));
      return offset;
    }
};

class ScreenAttitudeIndicator: public ScreenStreamAutoTag  {
  private:
    uint8_t objID = ScreenIDs::attitudeIndicator;
    uint16_t offset = 0;
  public:
    int16_t x = 0;
    int16_t y = 0;
    uint8_t cmdId = 0;
    int16_t dimSize = 200;
    float roll = 0.0f;
    float pitch = 0.0f;
    uint16_t getBytes(uint8_t *out) override {
      offset = 0;
      copyAndOffset(out, &offset, &objID, sizeof(objID));
      copyAndOffset(out, &offset, &x, sizeof(x));
      copyAndOffset(out, &offset, &y, sizeof(y));
      copyAndOffset(out, &offset, &tag, sizeof(tag));
      copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
      copyAndOffset(out, &offset, &dimSize, sizeof(dimSize));
      copyAndOffset(out, &offset, &roll, sizeof(roll));
      copyAndOffset(out, &offset, &pitch, sizeof(pitch));
      return offset;
    }
};

class ScreenHeadingIndicator: public ScreenStreamAutoTag  {
  private:
    uint8_t objID = ScreenIDs::headingIndicator;
    uint16_t offset = 0;
  public:
    int16_t x = 0;
    int16_t y = 0;
    uint8_t cmdId = 0;
    int16_t dimSize = 200;
    float heading = 0.0f;
    uint16_t getBytes(uint8_t *out) override {
      offset = 0;
      copyAndOffset(out, &offset, &objID, sizeof(objID));
      copyAndOffset(out, &offset, &x, sizeof(x));
      copyAndOffset(out, &offset, &y, sizeof(y));
      copyAndOffset(out, &offset, &tag, sizeof(tag));
      copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
      copyAndOffset(out, &offset, &dimSize, sizeof(dimSize));
      copyAndOffset(out, &offset, &heading, sizeof(heading));
      return offset;
    }
};

class ScreenJoystick: public ScreenStream  {
  private:
    uint8_t objID = ScreenIDs::joystick;
    uint16_t offset = 0;
  public:
    int16_t x = 0;
    int16_t y = 0;
    uint8_t cmdId = 0;
    int16_t dimSize = 200;
    int16_t sX = 0;
    int16_t sY = 0;
    bool springed = true;
    uint16_t getBytes(uint8_t *out) override {
      offset = 0;
      copyAndOffset(out, &offset, &objID, sizeof(objID));
      copyAndOffset(out, &offset, &x, sizeof(x));
      copyAndOffset(out, &offset, &y, sizeof(y));
      copyAndOffset(out, &offset, &tag, sizeof(tag));
      copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
      copyAndOffset(out, &offset, &dimSize, sizeof(dimSize));
      copyAndOffset(out, &offset, &springed, sizeof(springed));
      return offset;
    }
};

class ScreenGaugeSimple: public ScreenStreamAutoTag  {
  private:
    uint8_t objID = ScreenIDs::gaugeSimple;
    uint16_t offset = 0;
    int strLength = 0;
    const char *str;
  public:
    int16_t x = 0;
    int16_t y = 0;
    uint8_t cmdId = 0;
    int16_t dimSize = 200;
    int16_t minValue = 0;
    int16_t maxValue = 100;
    int16_t value = 0;
    uint8_t style = 0;
    bool isSymmetrical = false;
    int32_t color;
    void setlabel(const char *cstr) {
      str = cstr;
    }
    uint16_t getBytes(uint8_t *out) override {
      offset = 0;
      strLength = strlen(str);
      if (strLength > MAX_STRING_LENGTH_TERMINAL) {
        strLength = MAX_STRING_LENGTH_TERMINAL;
      }
      copyAndOffset(out, &offset, &objID, sizeof(objID));
      copyAndOffset(out, &offset, &x, sizeof(x));
      copyAndOffset(out, &offset, &y, sizeof(y));
      copyAndOffset(out, &offset, &tag, sizeof(tag));
      copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
      copyAndOffset(out, &offset, &dimSize, sizeof(dimSize));
      copyAndOffset(out, &offset, &minValue, sizeof(minValue));
      copyAndOffset(out, &offset, &maxValue, sizeof(maxValue));
      copyAndOffset(out, &offset, &value, sizeof(value));
      copyAndOffset(out, &offset, &style, sizeof(style));
      copyAndOffset(out, &offset, &isSymmetrical, sizeof(isSymmetrical));
      copyAndOffset(out, &offset, &color, sizeof(color));
      copyAndOffset(out, &offset, str, strLength);
      return offset;
    }
};

class ScreenColorPicker: public ScreenStream  {
  private:
    uint8_t objID = ScreenIDs::colorPicker;
    uint16_t offset = 0;
  public:
    int16_t x = 0;
    int16_t y = 0;
    uint8_t cmdId = 0;
    int16_t dimSize = 200;
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    uint16_t getBytes(uint8_t *out) override {
      offset = 0;
      copyAndOffset(out, &offset, &objID, sizeof(objID));
      copyAndOffset(out, &offset, &x, sizeof(x));
      copyAndOffset(out, &offset, &y, sizeof(y));
      copyAndOffset(out, &offset, &tag, sizeof(tag));
      copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
      copyAndOffset(out, &offset, &dimSize, sizeof(dimSize));
      copyAndOffset(out, &offset, &red, sizeof(red));
      copyAndOffset(out, &offset, &green, sizeof(green));
      copyAndOffset(out, &offset, &blue, sizeof(blue));
      return offset;
    }
};

class ScreenChart: public ScreenStreamAutoTag  {
  private:
    uint8_t objID = ScreenIDs::chart;
    uint8_t dataID = ScreenIDs::chartData;
    uint16_t offset = 0;
  public:
    int16_t x = 0;
    int16_t y = 0;
    uint8_t cmdId = 0;
    int16_t width = 200;
    int16_t height = 100;
    int16_t maxY = 10;
    int16_t minY = -10;
    int16_t maxX = 20;
    bool autoSize = true;
    int32_t color = YELLOW;
    uint16_t getBytes(uint8_t *out) override {
      offset = 0;
      copyAndOffset(out, &offset, &objID, sizeof(objID));
      copyAndOffset(out, &offset, &x, sizeof(x));
      copyAndOffset(out, &offset, &y, sizeof(y));
      copyAndOffset(out, &offset, &tag, sizeof(tag));
      copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
      copyAndOffset(out, &offset, &width, sizeof(width));
      copyAndOffset(out, &offset, &height, sizeof(height));
      copyAndOffset(out, &offset, &maxY, sizeof(maxY));
      copyAndOffset(out, &offset, &minY, sizeof(minY));
      copyAndOffset(out, &offset, &maxX, sizeof(maxX));
      copyAndOffset(out, &offset, &autoSize, sizeof(autoSize));
      copyAndOffset(out, &offset, &color, sizeof(color));
      return offset;
    }
    uint16_t getDataBytes(uint8_t *out, float chartData) {
      offset = 0;
      copyAndOffset(out, &offset, &dataID, sizeof(dataID));
      copyAndOffset(out, &offset, &tag, sizeof(tag));
      copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
      copyAndOffset(out, &offset, &chartData, sizeof(chartData));
      copyAndOffset(out, &offset, &color, sizeof(color));
      return offset;
    }
};

class ScreenRectangle: public ScreenStreamAutoTag  {
  private:
    uint8_t objID = ScreenIDs::rectangle;
    uint16_t offset = 0;
  public:
    int16_t x = 0;
    int16_t y = 0;
    uint8_t cmdId = 0;
    int16_t width = 200;
    int16_t height = 100;
    int32_t fillColor = BLACK;
    int32_t strokeColor = YELLOW;
    int16_t strokeWidth = 10;
    int16_t cornersRadius = 10;
    uint16_t getBytes(uint8_t *out) override {
      offset = 0;
      copyAndOffset(out, &offset, &objID, sizeof(objID));
      copyAndOffset(out, &offset, &x, sizeof(x));
      copyAndOffset(out, &offset, &y, sizeof(y));
      copyAndOffset(out, &offset, &tag, sizeof(tag));
      copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
      copyAndOffset(out, &offset, &width, sizeof(width));
      copyAndOffset(out, &offset, &height, sizeof(height));
      copyAndOffset(out, &offset, &fillColor, sizeof(fillColor));
      copyAndOffset(out, &offset, &strokeColor, sizeof(strokeColor));
      copyAndOffset(out, &offset, &strokeWidth, sizeof(strokeWidth));
      copyAndOffset(out, &offset, &cornersRadius, sizeof(cornersRadius));
      return offset;
    }
};

class ScreenTerminal: public ScreenStreamAutoTag  {
  private:
    uint8_t objID = ScreenIDs::terminal;
    uint8_t dataID = ScreenIDs::terminalData;
    uint16_t offset = 0;
    int strLength = 0;
  public:
    int16_t x = 0;
    int16_t y = 0;
    uint8_t cmdId = 0;
    int16_t width = 200;
    int16_t height = 100;
    int16_t textSize = 10;
    int32_t backColor = UBUNTU;
    uint16_t getBytes(uint8_t *out) override {
      offset = 0;
      copyAndOffset(out, &offset, &objID, sizeof(objID));
      copyAndOffset(out, &offset, &x, sizeof(x));
      copyAndOffset(out, &offset, &y, sizeof(y));
      copyAndOffset(out, &offset, &tag, sizeof(tag));
      copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
      copyAndOffset(out, &offset, &width, sizeof(width));
      copyAndOffset(out, &offset, &height, sizeof(height));
      copyAndOffset(out, &offset, &textSize, sizeof(textSize));
      copyAndOffset(out, &offset, &backColor, sizeof(backColor));
      return offset;
    }
    uint16_t getDataBytes(uint8_t *out, const char *str, int32_t textColor, bool autoScroll, bool newLine, bool bold, bool italic) {
      offset = 0;
      strLength = strlen(str);
      if (strLength > MAX_STRING_LENGTH_TERMINAL) {
        strLength = MAX_STRING_LENGTH_TERMINAL;
      }
      copyAndOffset(out, &offset, &dataID, sizeof(dataID));
      copyAndOffset(out, &offset, &tag, sizeof(tag));
      copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
      copyAndOffset(out, &offset, &textColor, sizeof(textColor));
      copyAndOffset(out, &offset, &newLine, sizeof(newLine));
      copyAndOffset(out, &offset, &bold, sizeof(bold));
      copyAndOffset(out, &offset, &italic, sizeof(italic));
      copyAndOffset(out, &offset, &autoScroll, sizeof(autoScroll));
      copyAndOffset(out, &offset, str, strLength);
      return offset;
    }
};

class ScreenSettings: public ScreenStream  {
  private:
    uint8_t objID = ScreenIDs::Settings;
    uint16_t offset = 0;
    int strLength = 0;
    const char *str;
  public:
    int8_t screenOrientation = 0;
    int32_t backColor;
    int32_t actionBarColor;
    bool resetScreen = false;
    void setlabel(const char *cstr) {
      str = cstr;
    }

    uint16_t getBytes(uint8_t *out, int8_t _screenOrientation, int32_t _backColor, int32_t _actionBarColor, const char *cstr) {
      screenOrientation = _screenOrientation;
      backColor = _backColor;
      actionBarColor = _actionBarColor;
      str = cstr;
      return getBytes(out);
    }

    uint16_t getBytes(uint8_t *out) override {
      offset = 0;
      strLength = strlen(str);
      if (strLength > MAX_STRING_LENGTH_TERMINAL) {
        strLength = MAX_STRING_LENGTH_TERMINAL;
      }
      copyAndOffset(out, &offset, &objID, sizeof(objID));
      copyAndOffset(out, &offset, &screenOrientation, sizeof(screenOrientation));
      copyAndOffset(out, &offset, &backColor, sizeof(backColor));
      copyAndOffset(out, &offset, &actionBarColor, sizeof(actionBarColor));
      copyAndOffset(out, &offset, &resetScreen, sizeof(resetScreen));
      copyAndOffset(out, &offset, str, strLength);
      resetScreen = false;
      return offset;
    }
};


class ScreenObjects {
  private:
    int16_t valTmp1 = 0;
    int16_t valTmp2 = 0;
    int16_t valTmp3 = 0;
    DataParser dataParser;
    Button* buttons;
    DialKnob* dialKnobs;
    Switch *switchs;
    SeekBar *seekBars;
    JoystickHandler *joystickHandlers;
    ColorPickerHandler *colorPickerHandlers;
    uint8_t buttonIndex = 1;
    uint8_t dialKnobIndex = 1;
    uint8_t switchIndex = 1;
    uint8_t DialKnobIndex = 1;
    uint8_t SeekBarIndex = 1;
    uint8_t JoystickHandlerIndex = 1;
    uint8_t ColorPickerHandlerIndex = 1;
    void (*setupCallback)(void);
    void screenInit();
  public:
    ScreenObjects() {
      setupCallback = NULL;
      buttons = new Button[maxObjects];
      dialKnobs = new DialKnob[maxObjects];
      switchs = new Switch[maxObjects];
      seekBars = new SeekBar[maxObjects];
      joystickHandlers = new JoystickHandler[maxObjects];
      colorPickerHandlers = new ColorPickerHandler[maxObjects];
      dialKnobIndex = 1;
      buttonIndex = 1;
    }
    void registerScreenSetup(void (*_setupCallback)(void));
    void registerButton(ScreenButton *screenButton, void (*_clickCallback)(void));
    void registerDialKnob(ScreenKnob *screenKnob, void (*_changeCallback)(int16_t));
    int updateScreen(uint8_t inp);
    int updateScreenInternal(uint8_t *dataFrame);
    void knobChanged(int8_t tag, int val);
    void clickButton(uint8_t tag);
    void registerSwitch(ScreenSwitch *screenSwitch, void (*_clickCallback)(bool));
    void updateSwitch(uint8_t tag, bool val);
    void registerSeekBar(ScreenSeekBar *screenSeekBar);
    void updateSeekBar(uint8_t tag, int16_t val);
    void registerJoystick(ScreenJoystick *screenJoystick);
    void updateJoystick(uint8_t tag, int16_t valX, int16_t valY);
    void registerColorPicker(ScreenColorPicker *screenColorPicker, void (*_clickCallback)(uint8_t, uint8_t, uint8_t));
    void updateColorPicker(uint8_t tag, uint8_t r, uint8_t g, uint8_t b);
};

void sendScreenStream(ScreenStream *obj, Stream *stream);
void addChartdata(float chartData, ScreenChart *obj, Stream *stream);
void ScreenTerminalPrint(const char *str, int32_t textColor, bool autoScroll, bool newLine, bool bold, bool italic, ScreenTerminal *obj, Stream *stream);
void ScreenTerminalPrint(const char *str, ScreenTerminal *obj, Stream *stream);
void ScreenTerminalPrintln(const char *str, ScreenTerminal *obj, Stream *stream);

#endif /* __BIND_H */
