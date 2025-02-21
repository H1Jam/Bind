#ifndef __BINDTEXTINPUT_H
#define __BINDTEXTINPUT_H

#include "BindView.hpp"
#include "BindUtils.hpp"
#include "Arduino.h"
/**
 * @brief The BindTextInput class represents a text input UI element for use with BindCanvas.
 *
 * \image html BindTextInput.jpg "BindTextInput"
 * BindTextInput is a class that defines a text input UI element that can be used within BindCanvas-based
 * applications. It inherits from the BindView class and provides functionality to create and
 * customize text inputs, including setting text, hint, positions, font size, text color, and background color.
 */
class BindTextInput : public BindView
{
public:
    /**
     * @brief Constructs a BindTextInput with default properties.
     *
     * This constructor creates a BindTextInput with default properties.
     */
    BindTextInput();
    /**
     * @brief Constructs a BindTextInput with custom properties.
     *
     * This constructor creates a BindTextInput with custom properties provided as parameters.
     *
     * @param x X-coordinate position of the text input.
     * @param y Y-coordinate position of the text input.
     * @param tag Tag identifier for the text input.
     * @param cmdId Command ID for the text input.
     * @param text Initial text content of the text input.
     * @param hint Hint text for the text input.
     * @param fontSize Font size for the text input.
     * @param textColor Text color for the text input.
     * @param backColor Background color for the text input.
     * @param widthChars Width of the text input in characters.
     * @param numberOnly Whether the text input should accept only numbers.
     */
    BindTextInput(int16_t x, int16_t y, uint8_t cmdId, const char *text, const char *hint, int16_t fontSize, int32_t textColor = 0, int32_t backColor = 0, uint8_t widthChars = 0, bool numberOnly = false);

    void setCallback(void (*callback)(const char *, uint8_t))
    {
        changeCallback = callback;
    }

    void invokeCallback(const char *val, uint8_t length)
    {
        setText(val, length);
        if (changeCallback != nullptr)
        {
            changeCallback(val, length);
        }
    }

    /**
     * @brief Sets the text content for the text input.
     *
     * This function allows you to set the text content for the text input UI element.
     *
     * @param cstr A pointer to the character array representing the text content.
     */
    void setText(const char *cstr)
    {
        setText(cstr, strlen(cstr));
    }

    void setText(const char *cstr, int length)
    {
        if (cstr == text || length < 0) {
            return; // Handle self-assignment
        }
        
        // Allocate memory for the new text
        if (text != nullptr) {
            delete[] text;
        }
        text = new char[length + 1];
        strncpy(text, cstr, length);
        text[length] = '\0'; // Null-terminate the string
        strLength = length;
    }

    /**
     * @brief Sets the hint text for the text input.
     *
     * This function allows you to set the hint text for the text input UI element.
     *
     * @param cstr A pointer to the character array representing the hint text.
     */
    void setHint(const char *cstr)
    {
        hint = cstr;
    }

    const char* getText() const
    {
        return text;
    }

    /**
     * @brief Retrieves the bytes representing the text input for synchronization.
     *
     * This function is used to gather the bytes that represent the text input's properties for synchronization.
     *
     * @param out A pointer to the output buffer where the text input data will be stored.
     * @return The number of bytes written to the output buffer.
     */
    uint16_t getBytes(uint8_t *out) override;

    int16_t x; ///< X-coordinate position of the text input.
    int16_t y; ///< Y-coordinate position of the text input.
    uint8_t cmdId; ///< Command ID for the text input.
    int16_t fontSize = 18; ///< Font size for the text input.
    int32_t textColor = WHITE; ///< Text color for the text input.
    int32_t backColor = TRANSPARENT; ///< Background color for the text input.
    uint8_t widthChars; ///< Width of the text input in characters.
    bool numberOnly = false;
    char *text = nullptr; ///< Text content of the text input.
    

private:
    uint8_t objID = BIND_ID_TEXTINPUT; ///< Object ID for the text input.
    uint16_t offset = 0; ///< Offset for the byte array.
    int strLength = 0; ///< Length of the text string.
    const char *hint; ///< Hint text for the text input
    static int16_t tagIndex; ///< Tag index for the text input.
    void (*changeCallback)(const char *, uint8_t) = nullptr;
};

#endif /* __BINDTEXTINPUT_H */