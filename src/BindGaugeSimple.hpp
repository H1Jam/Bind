#ifndef __BINDGAUGESIMPLE_HPP
#define __BINDGAUGESIMPLE_HPP
#include "BindView.hpp"
#include "BindUtils.hpp"

/**
 * @brief BindGaugeSimple Class
 *
 * The `BindGaugeSimple` class is a part of the Bind framework for Arduino, designed to
 * create a simple gauge element that can be displayed and controlled on the BindCanvas Android app interface.
 *
 * \image html BindGaugeSimple.jpg "BindGaugeSimple"
 * This class allows you to define the properties of a gauge, including its position, size, value range,
 * current value, style, symmetry, color, and label. You can synchronize these properties with BindCanvas
 * to provide visual gauge displays in your Arduino projects.
 * 
 * @note Possible cmdId values for a BindView and corresponding effects:
 *  - BIND_ADD_OR_REFRESH_CMD: Adds the object to the canvas (screen) or refreshes the existing one.
 *	- BIND_DATA_ONLY_CMD: Refreshes the existing object without moving or resizing; updates data, such as text.
 *	- BIND_REMOVE_CMD: Removes the object from the canvas (screen).
 *	- BIND_DISABLE_CMD: Disables the object.
 *	- BIND_ENABLE_CMD: Enables the object.
 *	- BIND_HIDE_CMD: Hides the object.
 *	- BIND_VISIBLE_CMD: Restores the object's visibility.
 *
 * The gauge's properties can be customized by setting attributes such as the position (x and y coordinates),
 * dimensions (size), minimum and maximum values for the gauge, current value, style (e.g., arc, horizontal, or vertical),
 * whether it's symmetrical or not (center is zero), color, and label text.
 *
 * To use the `BindGaugeSimple` class effectively, you can create an instance, set its attributes,
 * and call `bind.sync(your_gauge)` to synchronize it with BindCanvas.
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
 * bind.sync(gauge);
 * ```
 * @note check the examples for more information.
 */
class BindGaugeSimple : public BindView
{

public:
    /**
     * @brief Constructor with a label parameter.
     *
     * Initializes a `BindGaugeSimple` object with a custom label text.
     *
     * @param cstr A pointer to the label text.
     */
    BindGaugeSimple(const char *cstr);

    /**
     * @brief Default constructor.
     *
     * Initializes a `BindGaugeSimple` object with a default label ("Gauge").
     */
    BindGaugeSimple():BindGaugeSimple("Gauge"){}

    int16_t x = 0;              ///< The x-coordinate position of the gauge on the screen.
    int16_t y = 0;              ///< The y-coordinate position of the gauge on the screen.
    uint8_t cmdId = 0;          ///< Command identifier to add or refresh the gauge. See the notes for possible cmdId values.
    int16_t dimSize = 200;      ///< The dimensions (size) of the gauge.
    int16_t minValue = 0;       ///< The minimum value for the gauge's value range.
    int16_t maxValue = 100;     ///< The maximum value for the gauge's value range.
    int16_t value = 0;          ///< The current value of the gauge.
    uint8_t style = 0;          ///< The style of the gauge (e.g., radial or linear).
    bool isSymmetrical = false; ///< Indicates whether the gauge is symmetrical or not.
    int32_t color;              ///< The color of the gauge.

    /**
     * @brief Set the label text.
     *
     * Allows setting a custom label text for the gauge.
     *
     * @param cstr A pointer to the label text.
     */
    void setLabel(const char *cstr)
    {
        str = cstr;
    }

    [[deprecated("Use setLabel instead")]]
    void setlabel(const char *cstr)
    {
        setLabel(cstr);
    }

    /**
     * @brief Serialize the gauge object into bytes.
     *
     * This function serializes the gauge object into a byte array, allowing it to be sent and displayed on BindCanvas.
     *
     * @param out A pointer to the byte array where the serialized data will be stored.
     * @return The offset representing the length of the serialized data.
     */
    uint16_t getBytes(uint8_t *out);

private:
    uint8_t objID = BIND_ID_GAUGE_SIMPLE; ///< The unique identifier for the simple gauge object.
    uint16_t offset = 0;                  ///< Offset used for byte serialization.
    int strLength = 0;                    ///< Length of the label text.
    const char *str;                      ///< Pointer to the label text.
    static int16_t tagIndex;
};

#endif /* __BINDGAUGESIMPLE_HPP */
