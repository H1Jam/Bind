#ifndef __BINDBUTTON_H
#define __BINDBUTTON_H
#include "BindView.hpp"
#include "BindUtils.hpp"

/**
 * @brief The BindButton class represents a button UI element for use with BindCanvas.
 *
 * \image html BindButton.jpg "BindButton"
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
    setLabel(cstr);
    this->tag = tagIndex++;
  }

  BindButton()
  {
    setLabel("Button");
    this->tag = tagIndex++;
  }

  int16_t x;         ///< X-coordinate position of the button
  int16_t y;         ///< Y-coordinate position of the button
  uint8_t cmdId = 0; ///< Command ID for the button. See the notes for possible cmdId values.
  int16_t fontSize = 16;  ///< Font size of the button's label
  int32_t textColor = WHITE; ///< Text color of the button
  int32_t backColor = BLUE; ///< Background color of the button

  [[deprecated("Use setLabel instead")]]
  void setlabel(const char *cstr)
  {
    setLabel(cstr);
  }

  /**
   * @brief Sets the callback function for the button.
   *
   * This function allows you to set a callback function for the button.
   * The callback function is invoked when the button is clicked.
   * @note You need to sync the button, e.g. call bind.sync(bindButton).
   *
   * @param callback A pointer to the callback function.
   */
  void setLabel(const char *cstr)
  {
    str = cstr;
  }


  /**
   * @brief Set the press callback function for the button.
   * 
   * This callback function is called when the button is pressed.
   * The signature of the callback function should be like:backColor
   * @code {.cpp}
   * void callback()
   * @endcode
   * 
   * @param callback 
   */
  void setCallback(void (*callback)(void))
  {
    clickCallback = callback;
  }

  void invokeCallback()
  {
    if (clickCallback != nullptr)
    {
      clickCallback();
    }
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
  static int16_t tagIndex;
  void (*clickCallback)(void) = nullptr;
};
#endif /* __BINDBUTTON_H */