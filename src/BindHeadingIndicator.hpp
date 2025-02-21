#ifndef __BINDHEADINGINDICATOR_HPP
#define __BINDHEADINGINDICATOR_HPP
#include "BindView.hpp"
#include "BindUtils.hpp"

/**
 * @brief Represents a heading indicator for BindCanvas.
 *
 * \image html BindHeadingIndicator.jpg "BindHeadingIndicator"
 * The `BindHeadingIndicator` class is designed to create and display a heading indicator element
 * within a BindCanvas screen. This element allows users to visualize and monitor a vehicle or an object's heading.
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
 *
 */
class BindHeadingIndicator : public BindView
{

public:
    BindHeadingIndicator();
    int16_t x = 0;         ///< X-coordinate position of the heading indicator.
    int16_t y = 0;         ///< Y-coordinate position of the heading indicator.
    uint8_t cmdId = 0;     ///< Command ID for the heading indicator. See the notes for possible cmdId values.
    int16_t dimSize = 200; ///< Size dimension of the heading indicator (Width = Height).
    float heading = 0.0f;  ///< Current heading value.

    /**
     * @brief Generates and returns the byte data representing the heading indicator configuration.
     *
     * This function is meant for internal use by the Bind framework and should not be called directly by users.
     * It serializes the heading indicator's configuration properties into a byte array for communication with BindCanvas.
     *
     * @param out Pointer to the output byte array.
     * @return The number of bytes written to the output array.
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
        copyAndOffset(out, &offset, &heading, sizeof(heading));
        return offset;
    }

private:
    uint8_t objID = BIND_ID_HEADING_INDICATOR;
    uint16_t offset = 0;
    static int16_t tagIndex;
};

#endif /* __BINDHEADINGINDICATOR_HPP */
