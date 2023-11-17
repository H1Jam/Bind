#ifndef __BINDBUTTON_H
#define __BINDBUTTON_H
#include "BindView.hpp"
#include "BindUtils.hpp"

/**
 * @brief The BindButton class represents a button UI element for use with BindCanvas.
 *
 * BindButton is a class that defines a button UI element that can be used within BindCanvas-based
 * applications. It inherits from the BindView class and provides functionality to create and
 * customize buttons, including setting labels, positions, colors, and sizes.
 * @note Possible cmdId values for a BindView and corresponding effects:
 *  - BIND_ADD_OR_REFRESH_CMD: Adds the object to the canvas (screen) or refreshes the existing one.
 *	- BIND_DATA_ONLY_CMD: Refreshes the existing object without moving or resizing; updates data, such as text.
 *	- BIND_REMOVE_CMD: Removes the object from the canvas (screen).
 *	- BIND_DISABLE_CMD: Disables the object.
 *	- BIND_ENABLE_CMD: Enables the object.
 *	- BIND_HIDE_CMD: Hides the object.
 *	- BIND_VISIBLE_CMD: Restores the object's visibility.
 *
 * Buttons created with BindButton can be synchronized with BindCanvas through the Bind framework,
 * allowing interactive user interfaces to be built for various applications.
 * @note To receive touch events and user interactions, you must regularly call `bind.sync()` in your main loop.
 */
class BindButton : public BindView
{

public:
  /**
   * @brief Constructs a BindButton with a custom label.
   *
   * This constructor creates a BindButton with a custom text label.
   * The label can be used to define the button's text content.
   *
   * @param cstr A pointer to the character array representing the custom label for the button.
   */
  BindButton(const char *cstr)
  {
    setlabel(cstr);
  }

  BindButton()
  {
    setlabel("Button");
  }

  int16_t x;         ///< X-coordinate position of the button
  int16_t y;         ///< Y-coordinate position of the button
  uint8_t cmdId = 0; ///< Command ID for the button. See the notes for possible cmdId values.
  int16_t fontSize;  ///< Font size of the button's label
  int32_t textColor; ///< Text color of the button
  int32_t backColor; ///< Background color of the button

  /**
   * @brief Sets the label text for the button.
   *
   * This function allows you to set the text label for the button.
   * @note You need to sync the button, e.g. call bind.sync(bindButton).
   *
   * @param cstr A pointer to the character array representing the label text.
   */
  void setlabel(const char *cstr)
  {
    str = cstr;
  }

  /**
   * @brief Retrieves the bytes representing the button for synchronization.
   *
   * This function is used to gather the bytes that represent the button's properties for synchronization.
   * @note This function should not be called directly by users, Bind calls it internally.
   *
   * @param out A pointer to the output buffer where the button data will be stored.
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
    copyAndOffset(out, &offset, &textColor, sizeof(textColor));
    copyAndOffset(out, &offset, &backColor, sizeof(backColor));
    copyAndOffset(out, &offset, str, strLength);
    return offset;
  }

private:
  uint8_t objID = BIND_ID_BUTTON;
  uint16_t offset = 0;
  int strLength = 0;
  const char *str;
};
#endif /* __BINDBUTTON_H */