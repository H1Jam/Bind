#ifndef __BINDSWITCH_HPP
#define __BINDSWITCH_HPP
#include "BindView.hpp"
#include "BindUtils.hpp"
/**
 * @brief Represents a toggle switch UI element in the Bind framework.
 *
 * \image html BindSwitch.jpg "BindSwitch"
 * The `BindSwitch` class allows you to create toggle switch UI elements within your Arduino projects to be shown in BindCanvas.
 * You can customize the appearance and behavior of the switch, such as its position, label text, size, and colors.
 * Users can interact with the switch to toggle its state, and you can capture and respond to these state changes.
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
 * Example usage:
 * - Create a toggle switch with specific settings.
 * - Set its position, label, and appearance properties.
 * - Register a callback function to handle state changes when users interact with the switch: `mySwitchObj.setCallback(mySwitchCallback)`.
 * - Synchronize the switch with the Bind framework using `bind.sync(mySwitchObj)` to enable user interactions.
 *
 * Note: To receive touch events and user interactions, you must regularly call `bind.sync()` in your main loop.
 *
 * @see Bind for more information on using Bind UI elements.
 */
class BindSwitch : public BindView
{
public:
    /**
     * @brief Constructor to create a `BindSwitch` with a custom label.
     *
     * @param cstr The label text for the toggle switch.
     */
    BindSwitch(const char *cstr)
    {
        this->tag = tagIndex++;
        setLabel(cstr);
        this->changeCallback = nullptr;
    }

    /**
     * @brief Default constructor to create a `BindSwitch` with a default label ("Switch").
     */
    BindSwitch()
    {
        this->tag = tagIndex++;
        // add a default label for the switch  + "SW-[tag]" so like "Switch_1"
        char label[20];
        sprintf(label, "SW-%d", this->tag);
        setLabel(label);
        this->changeCallback = nullptr;
    }

    int16_t x; ///< X-coordinate position of the toggle switch.
    int16_t y; ///< Y-coordinate position of the toggle switch.
    uint8_t cmdId = 0; ///< Command identifier. See the notes for possible cmdId values.
    bool value;  ///< The current state (ON/OFF) of the toggle switch.
    int16_t fontSize;  ///< Font size for the switch label.
    int32_t textColor; ///< Text color for the switch label.

    /**
     * @brief Sets the label text for the toggle switch.
     *
     * @param cstr The label text for the toggle switch.
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
     * @brief Set the Callback function for the toggle switch.
     * 
     * This callback function is called when the toggle switch value is changed.
     * The signature of the callback function should be like:
     * @code {.cpp}
     * void callback(bool value)
     * @endcode
     * 
     * @param callback 
     */
    void setCallback(void (*callback)(bool))
    {
        this->changeCallback = callback;
    }

    void invokeCallback(bool val)
    {
        this->value = val;
        if (this->changeCallback != nullptr)
        {
            this->changeCallback(val);
        }
    }
    
    /**
     * @brief Generates and returns the byte data representing the toggle switch configuration.
     *
     * This function is meant for internal use by the Bind framework and should not be called directly by users.
     * It serializes the toggle switch's properties into a byte array for communication with the Bind framework.
     *
     * @param out Pointer to the output byte array.
     * @return The number of bytes written to the output array.
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
        copyAndOffset(out, &offset, &x, 2);
        copyAndOffset(out, &offset, &y, 2);
        copyAndOffset(out, &offset, &tag, 2);
        copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
        copyAndOffset(out, &offset, &value, sizeof(value));
        copyAndOffset(out, &offset, &fontSize, sizeof(fontSize));
        copyAndOffset(out, &offset, &textColor, sizeof(textColor));
        copyAndOffset(out, &offset, str, strLength);
        return offset;
    }

private:
    uint8_t objID = BIND_ID_TOGGLE_SWITCH;
    uint16_t offset = 0;
    int strLength = 0;
    const char *str;
    void (*changeCallback)(bool) = nullptr;
    static int16_t tagIndex;
};

#endif /* __BINDSWITCH_HPP */
