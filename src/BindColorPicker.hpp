#ifndef __BINDCOLORPICKER_HPP
#define __BINDCOLORPICKER_HPP
#include "BindView.hpp"
#include "BindUtils.hpp"

/**
 * @brief BindColorPicker Class
 *
 * The `BindColorPicker` class is part of the Bind framework for Arduino, designed to facilitate
 * the creation of interactive user interface elements. Specifically, it represents a color picker
 * element that can be displayed and controlled on the BindCanvas Android app interface.
 *
 * This class allows you to define a color picker's properties, including its position, size, and
 * the initial RGB color values. You can synchronize these properties with BindCanvas to provide a
 * visual color selection component in your Arduino projects.
 *
 * To use the `BindColorPicker` class effectively, you can set its attributes such as the
 * position (x and y coordinates), dimensions (size), and initial color (red, green, and blue values).
 * The `cmdId` parameter specifies whether to add the color picker to the BindCanvas or refresh
 * an existing one.
 * @note: Possible cmdId values for a BindView and corresponding effects:
 *  - BIND_ADD_OR_REFRESH_CMD: Adds the object to the canvas (screen) or refreshes the existing one.
 *	- BIND_DATA_ONLY_CMD: Refreshes the existing object without moving or resizing; updates data, such as text.
 *	- BIND_REMOVE_CMD: Removes the object from the canvas (screen).
 *	- BIND_DISABLE_CMD: Disables the object.
 *	- BIND_ENABLE_CMD: Enables the object.
 *	- BIND_HIDE_CMD: Hides the object.
 *	- BIND_VISIBLE_CMD: Restores the object's visibility.
 *
 * Additionally, you should regularly call `bind.sync()` in your main loop to ensure that the color picker
 * reflects the user interactions and properly calls the colorPicker callback
 *
 * Example usage:
 * ```cpp
 *      BindColorPicker colorPicker;
 * - in your Setup() function:
 * bind.join(&colorPicker, &colorPicker_changed);
 * - colorPicker_changed is callback function like this:
 * void colorPicker_changed(uint8_t red, uint8_t green, uint8_t blue)
 * - and in the onConnection() callback:
 * colorPicker.x = 30;
 * colorPicker.y = 100;
 * colorPicker.dimSize = 200;
 * colorPicker.red = 255;
 * colorPicker.green = 0;
 * colorPicker.blue = 0;
 * colorPicker.cmdId = BIND_ADD_OR_REFRESH_CMD;
 * bind.sync(&colorPicker);
 * ```
 * @note check the BindColorPicker examples for more information.
 */
class BindColorPicker : public BindView
{

public:
    int16_t x = 0;         ///< The x-coordinate position of the color picker on the screen.
    int16_t y = 0;         ///< The y-coordinate position of the color picker on the screen.
    uint8_t cmdId = 0;     ///< Command identifier to add or refresh the color picker. See the notes for possible cmdId values.
    int16_t dimSize = 200; ///< The dimensions (size) of the color picker.
    uint8_t red = 0;       ///< The initial value for the red component of the selected color (0-255).
    uint8_t green = 0;     ///< The initial value for the green component of the selected color (0-255).
    uint8_t blue = 0;      ///< The initial value for the blue component of the selected color (0-255).

    /**
     * @brief Serialize the color picker object into bytes.
     *
     * This function serializes the color picker object into a byte array, allowing it to be sent and displayed on BindCanvas.
     *
     * @param out A pointer to the byte array where the serialized data will be stored.
     * @return The offset representing the length of the serialized data.
     */
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

private:
    uint8_t objID = BIND_ID_COLOR_PICKER;
    uint16_t offset = 0;
};

#endif /* __BINDCOLORPICKER_HPP */
