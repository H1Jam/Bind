#ifndef __BINDWIDGETS_H
#define __BINDWIDGETS_H
#include "BindView.h"
#include "BindViewAutoTag.hpp"
#include "BindUtils.hpp"
// TODO: Extract each class to a serprate .h and .c file! Now!
// TODO: Add the class summaries!

/**
 * @brief The BindGauge class represents a gauge UI element for use with BindCanvas.
 *
 * BindGauge is a class that defines a gauge UI element that can be used within BindCanvas-based
 * applications. It inherits from the BindViewAutoTag class and provides functionality to create and
 * customize gauges, including setting positions, dimensions, value ranges, and appearance.
 *
 * Gauges created with BindGauge can be synchronized with BindCanvas through the Bind framework, allowing
 * real-time updates of gauge values and visual styles in various applications.
 *
 * @note To use BindGauge effectively, you can set various properties such as position, dimensions,
 * value range, appearance, and label.
 */
class BindGauge : public BindViewAutoTag
{
public:
  /**
   * @brief Constructs a BindGauge with a custom label.
   *
   * This constructor creates a BindGauge with a custom label provided as 'cstr.'
   * The label can be used to define the text content of the gauge.
   *
   * @param cstr A pointer to the character array representing the custom label for the gauge.
   */
  BindGauge(const char *cstr)
  {
    setlabel(cstr);
  }
  BindGauge()
  {
    setlabel("Gauge");
  }

  int16_t x;                 ///< X-coordinate position of the gauge
  int16_t y;                 ///< Y-coordinate position of the gauge
  uint8_t cmdId = 0;         ///< Command ID for the gauge
  int16_t dimSize = 100;     ///< Size of the gauge (Width = height)
  float value = 0;           ///< Current value of the gauge
  float maxValue = 100.0f;   ///< Maximum value of the gauge
  uint8_t drawArc = 0;       ///< Indicates whether to draw the gauge arc
  float arcGreenMaxVal = 0;  ///< Maximum value for the green arc section
  float arcYellowMaxVal = 0; ///< Maximum value for the yellow arc section
  float arcRedMaxVal = 0;    ///< Maximum value for the red arc section

  /**
   * @brief Sets the label text for the gauge.
   *
   * This function allows you to set the label text for the gauge UI element, providing additional context
   * or description for the gauge.
   *
   * @param cstr A pointer to the character array representing the label text.
   */
  void setlabel(const char *cstr)
  {
    str = cstr;
  }

  /**
   * @brief Serializes gauge properties into a byte array for synchronization.
   *
   * The 'getBytes' function serializes the properties of the BindGauge object into a byte array, which is used
   * internally by the Bind framework for synchronization with BindCanvas. This function should not be called
   * directly by users.
   *
   * @param out A pointer to the byte array where serialized data is stored.
   * @return The offset within the byte array where serialization ends.
   */
  uint16_t getBytes(uint8_t *out) override
  {
    offset = 0;
    strLength = strlen(str);
    if (strLength > MAX_STRING_LENGTH_TERMINAL)
    {
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

private:
  uint8_t objID = BindIDs::gauge1;
  uint16_t offset = 0;
  int strLength = 0;
  const char *str;
};

/**
 * @brief Represents a compact gauge view for the BindCanvas framework.
 *
 * The BindGaugeCompact class is used to create compact gauge views that can be displayed
 * on the BindCanvas screen. These gauges provide visual feedback for values within a specified range.
 * Users can customize the gauge appearance, label, and value range.
 *
 * This class inherits from BindViewAutoTag, allowing it to be managed by the BindCanvas framework.
 * It includes functionality for setting properties such as position, dimensions, current value, maximum value,
 * and color options. The getBytes function is used for data synchronization with BindCanvas.
 *
 * Example usage:
 * @code
 * // Create a BindGaugeCompact object with a label
 * BindGaugeCompact gauge("My Gauge");// Global
 * ....
 * gauge.x = 50;
 * gauge.y = 50;
 * gauge.value = 75.0f;
 * gauge.maxValue = 100.0f;
 *
 * // Bind the gauge to the canvas and display it
 * bind.sync(&gauge);
 * @endcode
 */
class BindGaugeCompact : public BindViewAutoTag
{

public:
  /**
   * @brief Constructs a BindGaugeCompact object with a custom label.
   *
   * @param cstr The label to display on the gauge.
   */
  BindGaugeCompact(const char *cstr)
  {
    setlabel(cstr);
  }

  /**
   * @brief Constructs a BindGaugeCompact object with a default label.
   */
  BindGaugeCompact()
  {
    setlabel("Gauge");
  }

  int16_t x;                 ///< The x-coordinate position of the gauge on the canvas.
  int16_t y;                 ///< The y-coordinate position of the gauge on the canvas.
  uint8_t cmdId = 0;         ///< The command ID associated with the gauge.
  int16_t dimSize = 100;     ///< The dimensions (size) of the gauge.
  float value = 0;           ///< The current value of the gauge.
  float maxValue = 100.0f;   ///< The maximum value that the gauge can represent.
  uint8_t drawArc = 0;       ///< Indicates whether to draw an arc for the gauge. 0=False, 1=True.
  float arcGreenMaxVal = 0;  ///< The maximum value for the green arc section.
  float arcYellowMaxVal = 0; ///< The maximum value for the yellow arc section.
  float arcRedMaxVal = 0;    ///< The maximum value for the red arc section.

  /**
   * @brief Sets the label to be displayed on the gauge.
   *
   * @param cstr The label text.
   */
  void setlabel(const char *cstr)
  {
    str = cstr;
  }

  /**
   * @brief Gets the bytes representing the BindGaugeCompact object for data synchronization.
   *
   * This function generates a byte representation of the BindGaugeCompact object, including its properties,
   * and stores it in the provided buffer for data transmission and synchronization with the BindCanvas screen.
   *
   * @param out A pointer to the buffer where the byte data will be stored.
   * @return The number of bytes written to the buffer.
   */
  uint16_t getBytes(uint8_t *out) override
  {
    offset = 0;
    strLength = strlen(str);
    if (strLength > MAX_STRING_LENGTH_TERMINAL)
    {
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

private:
  uint8_t objID = BindIDs::gauge2;
  uint16_t offset = 0;
  int strLength = 0;
  const char *str;
};

// This allows the user to manualy change the map zoom.
#define BIND_MAP_USER_ZOOM -1
class BindMap : public BindViewAutoTag
{
private:
  uint8_t objID = BindIDs::mapView;
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
  int8_t zoom = 1;
  uint16_t getBytes(uint8_t *out) override
  {
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

class BindMapMarker : public BindViewAutoTag
{
private:
  uint8_t objID = BindIDs::mapMarker;
  uint16_t offset = 0;

public:
  float lat = 0.0f;
  float lon = 0.0f;
  float rotation = 0.0f;
  uint8_t scale = 100;
  MarkerIcons iconId = MarkerIcons::PinRed;
  uint8_t cmdId = 0;
  uint16_t getBytes(uint8_t *out) override
  {
    offset = 0;
    copyAndOffset(out, &offset, &objID, sizeof(objID));
    copyAndOffset(out, &offset, &tag, sizeof(tag));
    copyAndOffset(out, &offset, &lat, sizeof(lat));
    copyAndOffset(out, &offset, &lon, sizeof(lon));
    copyAndOffset(out, &offset, &rotation, sizeof(rotation));
    copyAndOffset(out, &offset, &iconId, sizeof(iconId));
    copyAndOffset(out, &offset, &scale, sizeof(scale));
    copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
    return offset;
  }
};

class BindSwitch : public BindView
{
private:
  uint8_t objID = BindIDs::toggleSwitch;
  uint16_t offset = 0;
  int strLength = 0;
  const char *str;

public:
  BindSwitch(const char *cstr)
  {
    setlabel(cstr);
  }
  BindSwitch()
  {
    setlabel("Switch");
  }
  int16_t x;
  int16_t y;
  uint8_t cmdId = 0;
  bool switchValue;
  int16_t fontSize;
  int32_t textColor;
  void setlabel(const char *cstr)
  {
    str = cstr;
  }
  uint16_t getBytes(uint8_t *out) override
  {
    offset = 0;
    strLength = strlen(str);
    if (strLength > MAX_STRING_LENGTH_TERMINAL)
    {
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

class BindSeekBar : public BindView
{
private:
  uint8_t objID = BindIDs::seekBar;
  uint16_t offset = 0;

public:
  int16_t x = 0;
  int16_t y = 0;
  uint8_t cmdId = 0;
  int16_t seekValue = 0;
  int16_t maxValue = 100;
  int16_t width = 200;
  uint16_t getBytes(uint8_t *out) override
  {
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

class BindAttitudeIndicator : public BindViewAutoTag
{
private:
  uint8_t objID = BindIDs::attitudeIndicator;
  uint16_t offset = 0;

public:
  int16_t x = 0;
  int16_t y = 0;
  uint8_t cmdId = 0;
  int16_t dimSize = 200;
  float roll = 0.0f;
  float pitch = 0.0f;
  uint16_t getBytes(uint8_t *out) override
  {
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

class BindHeadingIndicator : public BindViewAutoTag
{
private:
  uint8_t objID = BindIDs::headingIndicator;
  uint16_t offset = 0;

public:
  int16_t x = 0;
  int16_t y = 0;
  uint8_t cmdId = 0;
  int16_t dimSize = 200;
  float heading = 0.0f;
  uint16_t getBytes(uint8_t *out) override
  {
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

class BindJoystick : public BindView
{
private:
  uint8_t objID = BindIDs::joystick;
  uint16_t offset = 0;

public:
  int16_t x = 0;
  int16_t y = 0;
  uint8_t cmdId = 0;
  int16_t dimSize = 200;
  int16_t sX = 0;
  int16_t sY = 0;
  bool springed = true;
  uint16_t getBytes(uint8_t *out) override
  {
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

class BindGaugeSimple : public BindViewAutoTag
{
private:
  uint8_t objID = BindIDs::gaugeSimple;
  uint16_t offset = 0;
  int strLength = 0;
  const char *str;

public:
  BindGaugeSimple(const char *cstr)
  {
    setlabel(cstr);
  }
  BindGaugeSimple()
  {
    setlabel("Gauge");
  }
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
  void setlabel(const char *cstr)
  {
    str = cstr;
  }
  uint16_t getBytes(uint8_t *out) override
  {
    offset = 0;
    strLength = strlen(str);
    if (strLength > MAX_STRING_LENGTH_TERMINAL)
    {
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

class BindColorPicker : public BindView
{
private:
  uint8_t objID = BindIDs::colorPicker;
  uint16_t offset = 0;

public:
  int16_t x = 0;
  int16_t y = 0;
  uint8_t cmdId = 0;
  int16_t dimSize = 200;
  uint8_t red = 0;
  uint8_t green = 0;
  uint8_t blue = 0;
  uint16_t getBytes(uint8_t *out) override
  {
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

class BindChart : public BindViewAutoTag
{
private:
  uint8_t objID = BindIDs::chart;
  uint8_t dataID = BindIDs::chartData;
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
  uint16_t getBytes(uint8_t *out) override
  {
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
  uint16_t getDataBytes(uint8_t *out, float chartData)
  {
    offset = 0;
    copyAndOffset(out, &offset, &dataID, sizeof(dataID));
    copyAndOffset(out, &offset, &tag, sizeof(tag));
    copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
    copyAndOffset(out, &offset, &chartData, sizeof(chartData));
    copyAndOffset(out, &offset, &color, sizeof(color));
    return offset;
  }
};

class BindRectangle : public BindViewAutoTag
{
private:
  uint8_t objID = BindIDs::rectangle;
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
  uint16_t getBytes(uint8_t *out) override
  {
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

class BindTerminal : public BindViewAutoTag
{
private:
  uint8_t objID = BindIDs::terminal;
  uint8_t dataID = BindIDs::terminalData;
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
  uint16_t getBytes(uint8_t *out) override
  {
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
  uint16_t getDataBytes(uint8_t *out, const char *str, int32_t textColor, bool autoScroll, bool newLine, bool bold, bool italic)
  {
    offset = 0;
    strLength = strlen(str);
    if (strLength > MAX_STRING_LENGTH_TERMINAL)
    {
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

class BindCanvasSettings : public BindView
{
private:
  uint8_t objID = BindIDs::Settings;
  uint16_t offset = 0;
  int strLength = 0;
  const char *str;

public:
  BindCanvasSettings()
  {
    setlabel("BindApp");
  }
  int8_t screenOrientation = 0;
  int32_t backColor;
  int32_t actionBarColor;
  bool resetScreen = false;
  void setlabel(const char *cstr)
  {
    str = cstr;
  }

  uint16_t getBytes(uint8_t *out, int8_t _screenOrientation, int32_t _backColor, int32_t _actionBarColor, const char *cstr)
  {
    screenOrientation = _screenOrientation;
    backColor = _backColor;
    actionBarColor = _actionBarColor;
    str = cstr;
    return getBytes(out);
  }

  uint16_t getBytes(uint8_t *out) override
  {
    offset = 0;
    strLength = strlen(str);
    if (strLength > MAX_STRING_LENGTH_TERMINAL)
    {
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
#endif /* __BINDWIDGETS_H */
