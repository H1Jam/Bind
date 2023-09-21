#ifndef __BINDGAUGESIMPLE_HPP
#define __BINDGAUGESIMPLE_HPP
#include "BindViewAutoTag.hpp"
#include "BindUtils.hpp"

/**
 * @brief BindGaugeSimple Class
 *
 * The `BindGaugeSimple` class is a part of the Bind framework for Arduino, designed to
 * create a simple gauge element that can be displayed and controlled on the BindCanvas Android app interface.
 *
 * This class allows you to define the properties of a gauge, including its position, size, value range,
 * current value, style, symmetry, color, and label. You can synchronize these properties with BindCanvas
 * to provide visual gauge displays in your Arduino projects.
 *
 * The gauge's properties can be customized by setting attributes such as the position (x and y coordinates),
 * dimensions (size), minimum and maximum values for the gauge, current value, style (e.g., arc, horizontal, or vertical),
 * whether it's symmetrical or not (center is zero), color, and label text.
 *
 * To use the `BindGaugeSimple` class effectively, you can create an instance, set its attributes,
 * and call `bind.sync(&your_gauge)` to synchronize it with BindCanvas.
 *
 * Example usage:
 * ```cpp
 * BindGaugeSimple gauge("Temperature");
 * gauge.x = 30;
 * gauge.y = 100;
 * gauge.dimSize = 200;
 * gauge.minValue = 0;
 * gauge.maxValue = 100;
 * gauge.value = 75;
 * gauge.style = 0; // 0 = arc, 1 = horizontal, 2 = vertical.
 * gauge.isSymmetrical = true;
 * gauge.color = YELLOW;
 * gauge.cmdId = BIND_ADD_OR_REFRESH_CMD;
 * bind.sync(&gauge);
 * ```
 *@note check the examples for more information.
 */
class BindGaugeSimple : public BindViewAutoTag
{

public:
    /**
     * @brief Constructor with a label parameter.
     *
     * Initializes a `BindGaugeSimple` object with a custom label text.
     *
     * @param cstr A pointer to the label text.
     */
    BindGaugeSimple(const char *cstr)
    {
        setlabel(cstr);
    }

    /**
     * @brief Default constructor.
     *
     * Initializes a `BindGaugeSimple` object with a default label ("Gauge").
     */
    BindGaugeSimple()
    {
        setlabel("Gauge");
    }

    int16_t x = 0;              ///< The x-coordinate position of the gauge on the screen.
    int16_t y = 0;              ///< The y-coordinate position of the gauge on the screen.
    uint8_t cmdId = 0;          ///< Command identifier to add or refresh the gauge.
    int16_t dimSize = 200;      ///< The dimensions (size) of the gauge.
    int16_t minValue = 0;       ///< The minimum value for the gauge's value range.
    int16_t maxValue = 100;     ///< The maximum value for the gauge's value range.
    int16_t value = 0;          ///< The current value of the gauge.
    uint8_t style = 0;          ///< The style of the gauge (e.g., radial or linear).
    bool isSymmetrical = false; ///< Indicates whether the gauge is symmetrical or not.
    int32_t color;              ///< The color of the gauge.

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

private:
    uint8_t objID = BindIDs::gaugeSimple; ///< The unique identifier for the simple gauge object.
    uint16_t offset = 0;                  ///< Offset used for byte serialization.
    int strLength = 0;                    ///< Length of the label text.
    const char *str;                      ///< Pointer to the label text.
};

#endif /* __BINDGAUGESIMPLE_HPP */
