#ifndef __BINDSEEKBAR_HPP
#define __BINDSEEKBAR_HPP
#include "BindView.h"
#include "BindUtils.hpp"
/**
 * @brief Represents a SeekBar object in the Bind framework.
 *
 * The `BindSeekBar` class defines a SeekBar object that can be used in the Bind framework.
 * SeekBars are typically used to select a value within a specified range by dragging a slider.
 * This class provides methods to configure SeekBars on the screen.
 */
class BindSeekBar : public BindView
{

public:
    int16_t x;              ///< X-coordinate position of the SeekBar.
    int16_t y;              ///< Y-coordinate position of the SeekBar.
    uint8_t cmdId = 0;      ///< Command identifier.
    int16_t seekValue = 0;  ///< Current value selected on the SeekBar.
    int16_t maxValue = 100; ///< Maximum value of the SeekBar.
    int16_t width = 200;    ///< Width of the SeekBar.

    /**
     * @brief Serialize the SeekBar data into a byte array.
     *
     * This function serializes the SeekBar's properties and data into a byte array for communication
     * with the Bind framework.
     * @note This function should not be called directly by users, Bind calls it internally.
     *
     * @param out A pointer to the output byte array.
     * @return The number of bytes written to the output array.
     */
    uint16_t getBytes(uint8_t *out) override
    {
        offset = 0;
        copyAndOffset(out, &offset, &objID, sizeof(objID));
        copyAndOffset(out, &offset, &x, 2);
        copyAndOffset(out, &offset, &y, 2);
        copyAndOffset(out, &offset, &tag, 2);
        copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
        copyAndOffset(out, &offset, &seekValue, sizeof(seekValue));
        copyAndOffset(out, &offset, &maxValue, sizeof(maxValue));
        copyAndOffset(out, &offset, &width, sizeof(width));
        return offset;
    }

private:
    uint8_t objID = BindIDs::seekBar; ///< Unique identifier for the SeekBar.
    uint16_t offset = 0;              ///< Offset for serialization.
};

#endif /* __BINDSEEKBAR_HPP */
