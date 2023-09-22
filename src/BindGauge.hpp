#ifndef __BINDGAUGE_HPP
#define __BINDGAUGE_HPP
#include "BindViewAutoTag.hpp"
#include "BindUtils.hpp"
// TODO: Extract each class to a serprate .h and .c file! Now!
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

    /**
     * @brief Constructs a BindGauge with a default label.
     *
     * This constructor creates a BindGauge with a default label of "Gauge."
     * You can customize the label later using the 'setLabel' function.
     */
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

#endif /* __BINDGAUGE_HPP */