#ifndef __BINDGAUGECOMPACT_HPP
#define __BINDGAUGECOMPACT_HPP
#include "BindViewAutoTag.hpp"
#include "BindUtils.hpp"
// TODO: Extract each class to a serprate .h and .c file! Now!

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

#endif /* __BINDGAUGECOMPACT_HPP */
