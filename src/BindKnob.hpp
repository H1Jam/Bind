#ifndef __BINDKNOB_H
#define __BINDKNOB_H
#include "BindView.hpp"
#include "BindUtils.hpp"
// TODO: Extract the class to a serprate .h and .c file! Now!
/**
 * @brief The BindKnob class represents a knob UI element for use with BindCanvas.
 *
 * BindKnob is a class that defines a knob UI element that can be used within BindCanvas-based
 * applications. It inherits from the BindView class and provides functionality to create and
 * customize knobs, including setting labels, positions, dimensions, value ranges, and current values.
 *
 * Knobs created with BindKnob can be synchronized with BindCanvas through the Bind framework,
 * allowing interactive user interfaces to be built for various applications.
 *
 * @note To use BindKnob effectively, you can set various properties such as the label, position,
 * dimensions, value range (minimum and maximum), and the current knob value.
 */
class BindKnob : public BindView
{

public:
  /**
   * @brief Constructs a BindKnob with a custom label.
   *
   * This constructor creates a BindKnob with a custom text label.
   * The label can be used to define the knob's label or description.
   *
   * @param cstr A pointer to the character array representing the custom label for the knob.
   */
  BindKnob(const char *cstr)
  {
    setlabel(cstr);
  }

  /**
   * @brief Constructs a BindKnob with a default label.
   *
   * This constructor creates a BindKnob with a default label of "Knob."
   * You can customize the label later using the 'setLabel' function.
   */
  BindKnob() : BindKnob("Knob"){}

  int16_t x;         ///< X-coordinate position of the knob
  int16_t y;         ///< Y-coordinate position of the knob
  uint8_t cmdId = 0; ///< Command ID for the knob
  int16_t dimSize;   ///< Dimensions or size of the knob
  int16_t minValue;  ///< Minimum value of the knob's range
  int16_t maxValue;  ///< Maximum value of the knob's range
  int16_t value;     ///< Current value of the knob

  /**
   * @brief Sets the label text for the knob.
   *
   * This function allows you to set the text label for the knob, providing additional information
   * or description for the knob's purpose.
   * @note You need to sync the knob, e.g. call bind.sync(bindKnob).
   *
   * @param cstr A pointer to the character array representing the label text.
   */
  void setlabel(const char *cstr)
  {
    str = cstr;
  }

  /**
   * @brief Retrieves the bytes representing the knob for synchronization.
   *
   * This function is used to gather the bytes that represent the knob's properties for synchronization.
   * @note The user does not need to call this function, Bind calls it internally.
   *
   * @param out A pointer to the output buffer where the knob data will be stored.
   * @return The number of bytes written to the output buffer.
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
    copyAndOffset(out, &offset, &minValue, sizeof(minValue));
    copyAndOffset(out, &offset, &maxValue, sizeof(maxValue));
    copyAndOffset(out, &offset, &value, sizeof(value));
    copyAndOffset(out, &offset, str, strLength);
    return offset;
  }

private:
  uint8_t objID = BIND_ID_KNOB;
  uint16_t offset = 0;
  int strLength = 0;
  const char *str;
};
#endif /* __BINDKNOB_H */