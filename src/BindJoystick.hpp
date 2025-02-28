#ifndef __BINDJOYSTICK_HPP
#define __BINDJOYSTICK_HPP
#include "BindView.hpp"
#include "BindUtils.hpp"
/**
 * @brief BindJoystick Class
 *
 * \image html BindJoystick.jpg "BindJoystick"
 * The `BindJoystick` class is a part of the Bind framework for Arduino, designed to creat a
 * joystick element that can be displayed and controlled on the BindCanvas Android app interface.
 * 
 * @note The joystick ranges from -100 to 100 on both the X and Y axes.
 *
 * @note Possible cmdId values for a BindView and corresponding effects:
 *  - BIND_ADD_OR_REFRESH_CMD: Adds the object to the canvas (screen) or refreshes the existing one.
 *  - BIND_DATA_ONLY_CMD: Refreshes the existing object without moving or resizing; updates data, such as text.
 *  - BIND_REMOVE_CMD: Removes the object from the canvas (screen).
 *  - BIND_DISABLE_CMD: Disables the object.
 *  - BIND_ENABLE_CMD: Enables the object.
 *  - BIND_HIDE_CMD: Hides the object.
 *  - BIND_VISIBLE_CMD: Restores the object's visibility.
 *
 * This class allows you to define the properties of a joystick, including its position, size,
 * spring behavior, and more. You can synchronize these properties with BindCanvas to provide
 * joystick controls in your Arduino projects.
 *
 * @note To receive touch events and user interactions, you must regularly call `bind.sync()` in your main loop.
 *
 * To use the `BindJoystick` class effectively, you can
 * create an instance,
 * set the callback function,
 * set its attributes,
 * and call `bind.sync(your_joystick)` to synchronize it with BindCanvas.
 *
 * Example usage:
 * ```cpp
 * BindJoystick joystick;
 * ...
 * joystick.x = 30;
 * joystick.y = 100;
 * joystick.dimSize = 200;
 * joystick.springed = true;
 * joystick.cmdId = BIND_ADD_OR_REFRESH_CMD;
 * joystick.setCallback(joystick1_onChange);
 * bind.sync(joystick);
 * ...
 * void joystick1_onChange(int16_t x, int16_t y) {
 *  Serial.print("joystick1 has been changed, x:");
 *  Serial.print(x);
 *  Serial.print(" y:");
 *  Serial.println(y);
 * }
 * ```
 * @note check the examples for more information.
 *
 */
class BindJoystick : public BindView
{

public:
    BindJoystick()
    {
        this->tag = tagIndex++;
    }

    int16_t x = 0; ///< The x-coordinate position of the joystick on the screen.
    int16_t y = 0; ///< The y-coordinate position of the joystick on the screen.
    uint8_t cmdId = 0; ///< Command identifier to add or refresh the joystick. See the notes for possible cmdId values.
    int16_t dimSize = 200; ///< The dimensions (size) of the joystick.
    int16_t sX = 0; ///< The joystick's current X-axis position (internal).
    int16_t sY = 0; ///< The joystick's current Y-axis position (internal).
    bool springed = true; ///< Indicates whether the joystick returns to the center automatically when released.
    
    /**
     * @brief Set the Callback function for the joystick.
     * 
     * This callback function is called when the joystick is moved.
     * The signature of the callback function should be like:
     * @code {.cpp}
     * void callback(int16_t x, int16_t y)
     * @endcode
     * 
     * @param callback 
     */
    void setCallback(void (*callback)(int16_t, int16_t))
    {
        changeCallback = callback;
    }

    void invokeCallback(int16_t xIn, int16_t yIn)
    {
        this->sX = xIn;
        this->sY = yIn;
        if (changeCallback != nullptr)
        {
            changeCallback(xIn, yIn);
        }
    }

    /**
     * @brief Serialize the joystick object into bytes.
     *
     * This function serializes the joystick object into a byte array, allowing it to be sent and displayed on BindCanvas.
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
        copyAndOffset(out, &offset, &springed, sizeof(springed));
        return offset;
    }

private:
    uint8_t objID = BIND_ID_JOYSTICK;
    uint16_t offset = 0;
    static int16_t tagIndex;
    void (*changeCallback)(int16_t, int16_t) = nullptr;
};

#endif /* __BINDJOYSTICK_HPP */
