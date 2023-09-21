#ifndef __BINDCOLORPICKER_HPP
#define __BINDCOLORPICKER_HPP
#include "BindView.h"
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
 *
 * Additionally, you should regularly call `bind.sync()` in your main loop to ensure that the color picker
 * reflects the user interactions and properly calls the colorPicker callback
 *
 * Example usage:
 * ```cpp
 * BindColorPicker colorPicker;
 * // in your Setup() function"
 * 
 * colorPicker.x = 30;
 * colorPicker.y = 100;
 * colorPicker.dimSize = 200;
 * colorPicker.red = 255;
 * colorPicker.green = 0;
 * colorPicker.blue = 0;
 * colorPicker.cmdId = BIND_ADD_OR_REFRESH_CMD;
 * bind.sync(&colorPicker);
 * ```
 *
 * @see BindView
 * @see BindCanvas
 */
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

#endif /* __BINDCOLORPICKER_HPP */
