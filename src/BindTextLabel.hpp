#ifndef __BINDTEXTLABEL_H
#define __BINDTEXTLABEL_H
#include "BindView.hpp"
#include "BindUtils.hpp"
// TODO: Extract the class to a serprate .h and .c file! Now!
/**
 * @brief The BindTextLabel class represents a text label UI element for use with BindCanvas.
 *
 * BindTextLabel is a class that defines a text label UI element that can be used within BindCanvas-based
 * applications. It inherits from the BindView class and provides functionality to create and
 * customize text labels, including setting labels, positions, font size, and text color.
 *
 * Text labels created with BindTextLabel can be synchronized with BindCanvas through the Bind framework,
 * allowing dynamic text content to be displayed in various applications.
 *
 * @note To use BindTextLabel effectively, you can set various properties such as the label, position,
 * font size, and text color.
 */
class BindTextLabel : public BindView
{

public:
  /**
   * @brief Constructs a BindTextLabel with a custom label.
   *
   * This constructor creates a BindTextLabel with a custom text label provided as 'cstr.'
   * The label can be used to define the text content of the label.
   *
   * @param cstr A pointer to the character array representing the custom label for the text label.
   */
  BindTextLabel(const char *cstr)
  {
    setlabel(cstr);
  }

  /**
   * @brief Constructs a BindTextLabel with a default label.
   *
   * This constructor creates a BindTextLabel with a default label of "TextLabel."
   * You can customize the label later using the 'setLabel' function.
   */
  BindTextLabel()
  {
    setlabel("TextLabel");
  }

  /**
   * @brief Sets the label text for the text label.
   *
   * This function allows you to set the text label for the text label UI element, providing the content
   * to be displayed.
   *
   * @param cstr A pointer to the character array representing the label text.
   */
  void setlabel(const char *cstr)
  {
    str = cstr;
  }

  int16_t x;          ///< X-coordinate position of the text label
  int16_t y;          ///< Y-coordinate position of the text label
  uint8_t cmdId = 0;  ///< Command ID for the text label
  int16_t fontSize;   ///< Font size for the text label
  int32_t color;      ///< Text color for the text label

  /**
   * @brief Retrieves the bytes representing the text label for synchronization.
   *
   * This function is used to gather the bytes that represent the text label's properties for synchronization.
   *
   * @param out A pointer to the output buffer where the text label data will be stored.
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
    copyAndOffset(out, &offset, &fontSize, sizeof(fontSize));
    copyAndOffset(out, &offset, &color, sizeof(color));
    copyAndOffset(out, &offset, str, strLength);
    return offset;
  }

private:
  uint8_t objID = BindIDs::label;
  uint16_t offset = 0;
  int strLength = 0;
  const char *str;
  static int16_t tagIndex;
};

#endif /* __BINDTEXTLABEL_H */