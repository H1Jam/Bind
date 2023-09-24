#ifndef __BINDATTITUDEINDICATOR_HPP
#define __BINDATTITUDEINDICATOR_HPP
#include "BindView.hpp"
#include "BindUtils.hpp"
/**
 * @brief Represents an attitude indicator UI element in the Bind framework.
 *
 * The `BindAttitudeIndicator` class enables the creation of an attitude indicator within your Arduino projects.
 * This UI element visually displays the roll and pitch of a vehicle or object, providing valuable information about its orientation.
 * You can customize the appearance and behavior of the attitude indicator, such as its position, size, and orientation values.
 *
 * Example usage:
 * - Create an attitude indicator with specific settings.
 * - Set its position and dimensions on the screen.
 * - Configure the roll and pitch values to visualize the object's orientation.
 * - Synchronize the attitude indicator with the Bind framework using `bind.sync(&myIndicator)` when you need to refresh the values.
 *
 */
class BindAttitudeIndicator : public BindView
{

public:
    int16_t x = 0; ///< X-coordinate position of the attitude indicator.
    int16_t y = 0; ///< Y-coordinate position of the attitude indicator.
    uint8_t cmdId = 0;
    int16_t dimSize = 200; ///< Dimension size of the attitude indicator.
    float roll = 0.0f;     ///< Roll angle value for orientation.
    float pitch = 0.0f;    ///< Pitch angle value for orientation.

    /**
     * @brief Generates and returns the byte data representing the attitude indicator configuration.
     *
     * This function is meant for internal use by the Bind framework and should not be called directly by users.
     * It serializes the attitude indicator's properties into a byte array for communication with the Bind framework.
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
        copyAndOffset(out, &offset, &roll, sizeof(roll));
        copyAndOffset(out, &offset, &pitch, sizeof(pitch));
        return offset;
    }

private:
    uint8_t objID = BindIDs::attitudeIndicator;
    uint16_t offset = 0;
    static int16_t tagIndex;
};

#endif /* __BINDATTITUDEINDICATOR_HPP */
