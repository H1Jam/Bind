#ifndef __BINDTERMINAL_HPP
#define __BINDTERMINAL_HPP
#include "BindView.hpp"
#include "BindUtils.hpp"

/**
 * @brief Represents a terminal display for BindCanvas.
 *
 * \image html BindTerminal.jpg "BindTerminal"
 * The `BindTerminal` class is designed to create and display a terminal-like text interface
 * within a BindCanvas UI. This terminal can be used for displaying text data, log messages,
 * or other textual information and provides various customization options.
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
 * @see the example folder for more information.
 */
class BindTerminal : public BindView
{

public:
    BindTerminal();
    int16_t x = 0;              ///< X-coordinate position of the terminal.
    int16_t y = 0;              ///< Y-coordinate position of the terminal.
    uint8_t cmdId = 0;          ///< Command ID for the terminal. See the notes for possible cmdId values.
    int16_t width = 200;        ///< Width of the terminal.
    int16_t height = 100;       ///< Height of the terminal.
    int16_t textSize = 10;      ///< Text size of the displayed text.
    int32_t backColor = UBUNTU; ///< Background color of the terminal.

    /**
     * @brief Generates and returns the byte data representing the terminal's configuration.
     *
     * This function is meant for internal use by the Bind framework and should not be called directly by users.
     * It serializes the terminal's configuration properties into a byte array for communication with BindCanvas.
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
        copyAndOffset(out, &offset, &width, sizeof(width));
        copyAndOffset(out, &offset, &height, sizeof(height));
        copyAndOffset(out, &offset, &textSize, sizeof(textSize));
        copyAndOffset(out, &offset, &backColor, sizeof(backColor));
        return offset;
    }
    
    /**
     * @brief Generates and returns the byte data representing text to be displayed in the terminal.
     *
     * Use this method to send text data to the terminal for display. It serializes the text properties
     * including color, formatting, and scrolling behavior into a byte array.
     *
     * @param out Pointer to the output byte array.
     * @param str The text data to be displayed.
     * @param textColor The color of the text.
     * @param autoScroll Whether the terminal should automatically scroll to show new text.
     * @param newLine Whether a new line should be added after the text.
     * @param bold Whether the text should be displayed in bold.
     * @param italic Whether the text should be displayed in italic.
     * @return The number of bytes written to the output array.
     */
    uint16_t getDataBytes(uint8_t *out, const char *str, int32_t textColor, bool autoScroll, bool newLine, bool bold, bool italic)
    {
        offset = 0;
        strLength = strlen(str);
        if (strLength > MAX_STRING_LENGTH_TERMINAL)
        {
            strLength = MAX_STRING_LENGTH_TERMINAL;
        }
        copyAndOffset(out, &offset, &dataID, sizeof(dataID));
        copyAndOffset(out, &offset, &tag, sizeof(tag));
        copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
        copyAndOffset(out, &offset, &textColor, sizeof(textColor));
        copyAndOffset(out, &offset, &newLine, sizeof(newLine));
        copyAndOffset(out, &offset, &bold, sizeof(bold));
        copyAndOffset(out, &offset, &italic, sizeof(italic));
        copyAndOffset(out, &offset, &autoScroll, sizeof(autoScroll));
        copyAndOffset(out, &offset, str, strLength);
        return offset;
    }

private:
    uint8_t objID = BIND_ID_TERMINAL;
    uint8_t dataID = BIND_ID_TERMINAL_DATA;
    uint16_t offset = 0;
    int strLength = 0;
    static int16_t tagIndex;
};
#endif /* __BINDTERMINAL_HPP */
