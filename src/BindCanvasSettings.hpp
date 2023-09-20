#ifndef __BINDCANVASSETTINGS_HPP
#define __BINDCANVASSETTINGS_HPP
#include "BindView.h"
#include "BindUtils.hpp"
/**
 * @brief Represents the configuration settings for a BindCanvas application screen.
 *
 * The `BindCanvasSettings` class is used to configure various settings for a BindCanvas application screen.
 * These settings include screen orientation, background color, action bar color, and the option to reset the screen.
 * Users can customize these settings to tailor the appearance and behavior of their BindCanvas application.
 *
 * Example usage:
 * - Create a `BindCanvasSettings` object to specify screen configuration.
 * - Set screen orientation, background color, and action bar color as needed.
 * - Optionally, enable the screen reset feature to restore the default state (will remove all BindViews).
 * - Use the `bind.sync(&myScreenSettings)` function to apply the settings.
 *
 * @see Bind for creating Bind UI elements
 * @attention the app label has been removed for now but may return in future thus kept it here.
 *
 */
class BindCanvasSettings : public BindView
{
public:
    /**
     * @brief Constructs a `BindCanvasSettings` object with default label "BindApp."
     */
    BindCanvasSettings()
    {
        setlabel("BindApp");
    }

    int8_t screenOrientation = 0; ///< Screen orientation value.
    int32_t backColor;            ///< Background color in 32-bit format.
    int32_t actionBarColor;       ///< Action bar color in 32-bit format.
    bool resetScreen = false;     ///< Flag to reset the screen.

    /**
     * @brief Sets the label for the BindCanvas application screen.
     * @attention the app label has been removed for now but may return in future thus kept it here.
     *
     * @param cstr The label text for the screen.
     */
    void setlabel(const char *cstr)
    {
        str = cstr;
    }

    /**
     * @brief Generates and returns the byte data representing the screen configuration.
     *
     * This function is meant for internal use by the Bind framework and should not be called directly by users.
     * It serializes the screen configuration properties into a byte array for communication with the Bind framework.
     *
     * @param out Pointer to the output byte array.
     * @param _screenOrientation The screen orientation value.
     * @param _backColor The background color in 32-bit format.
     * @param _actionBarColor The action bar color in 32-bit format.
     * @param cstr The label text for the screen.
     * @return The number of bytes written to the output array.
     */
    uint16_t getBytes(uint8_t *out, int8_t _screenOrientation, int32_t _backColor, int32_t _actionBarColor, const char *cstr)
    {
        screenOrientation = _screenOrientation;
        backColor = _backColor;
        actionBarColor = _actionBarColor;
        str = cstr;
        return getBytes(out);
    }

    /**
     * @brief Generates and returns the byte data representing the screen configuration.
     *
     * This function is meant for internal use by the Bind framework and should not be called directly by users.
     * It serializes the screen configuration properties into a byte array for communication with the Bind framework.
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
        copyAndOffset(out, &offset, &screenOrientation, sizeof(screenOrientation));
        copyAndOffset(out, &offset, &backColor, sizeof(backColor));
        copyAndOffset(out, &offset, &actionBarColor, sizeof(actionBarColor));
        copyAndOffset(out, &offset, &resetScreen, sizeof(resetScreen));
        copyAndOffset(out, &offset, str, strLength);
        resetScreen = false;
        return offset;
    }

private:
    uint8_t objID = BindIDs::Settings; ///< Object ID for Bind settings.
    uint16_t offset = 0;
    int strLength = 0;
    const char *str;
};
#endif /* __BINDCANVASSETTINGS_HPP */
