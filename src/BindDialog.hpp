#ifndef __BINDDIALOG_HPP
#define __BINDDIALOG_HPP
#include "BindView.hpp"
#include "BindUtils.hpp"
#define DIALOG_TEXT_BUFFER_SIZE 64
#if defined(__AVR__)
#include <avr/pgmspace.h>
const char DEFAULT_TITLE[] PROGMEM = "Confirmation";
const char DEFAULT_MESSAGE[] PROGMEM = "Are you sure?";
const char DEFAULT_OK[] PROGMEM = "OK";
const char DEFAULT_CANCEL[] PROGMEM = "Cancel";
#else
const char DEFAULT_TITLE[] = "Confirmation";
const char DEFAULT_MESSAGE[] = "Are you sure?";
const char DEFAULT_OK[] = "OK";
const char DEFAULT_CANCEL[] = "Cancel";
#endif
/**
 * @brief The type of dialog.
 * 
 * * TEXT_INPUT:      Dialog for text input.
 * * PASSWORD_INPUT:  Dialog for password-like input (concealed text).
 * * SINGLE_BUTTON:   Dialog that uses only a single button.
 * * DOUBLE_BUTTON:   Dialog with two buttons (primary + secondary).
 */
enum DialogType {
    TEXT_INPUT,
    PASSWORD_INPUT,
    NO_INPUT_TEXT,
};

/**
 * @brief BindDialog class represents a dialog box for use with BindCanvas app.
 * 
 * \image html BindDialog.jpg "BindDialog"
 * \image html Dialog_singleButton.jpg "BindDialog Single Button"
 * \image html DialogPassword.jpg "Password Dialog"
 * BindDialog defines a popup dialog that can be shown with one or two buttons,
 * optionally allowing text or password input. The user can set a title, message,
 * button labels, and a callback to handle interaction.
 *
 * Usage:
 * 1. Instantiate BindDialog with the desired DialogType.
 * 2. Set title, message, primaryButton, and optionally secondaryButton.
 * 3. Set a callback function for results (use setCallback(bool) or setCallback(bool, const char*) for text input).
 * 4. Call sync() to show the dialog on the screen.
 * @endcode
 */
class BindDialog : public BindView
{
public:

    BindDialog(DialogType type = NO_INPUT_TEXT)
    : dialogType(type), title(nullptr), message(nullptr), primaryButton("OK"), secondaryButton("Cancel")
    {
        this->tag = tagIndex++;
        #if defined(__AVR__)
        char buffer[16];
        strcpy_P(buffer, DEFAULT_TITLE);
        setTitle(buffer);
        strcpy_P(buffer, DEFAULT_MESSAGE);
        setMessage(buffer);
        strcpy_P(buffer, DEFAULT_OK);
        setPrimaryButton(buffer);
        strcpy_P(buffer, DEFAULT_CANCEL);
        setSecondaryButton(buffer);
        #else
        setTitle(DEFAULT_TITLE);
        setMessage(DEFAULT_MESSAGE);
        setPrimaryButton(DEFAULT_OK);
        setSecondaryButton(DEFAULT_CANCEL);
        #endif
    }

    /**
     * @brief Set the title text for the dialog.
     * 
     * @param cstr Title text for the dialog.
     */
    void setTitle(const char *cstr)
    {
        title = cstr;
    }

    /**
     * @brief Set the message text for the dialog.
     * 
     * @param cstr Message text for the dialog.
     */
    void setMessage(const char *cstr)
    {
        message = cstr;
    }

    /**
     * @brief Set the primary button text (e.g. "OK") for the dialog.
     * 
     * @param cstr Primary button text for the dialog.
     */
    void setPrimaryButton(const char *cstr)
    {
        primaryButton = cstr;
    }

    /**
     * @brief Set the secondary button text (e.g. "Cancel") for the dialog.
     * 
     * @param cstr Secondary button text for the dialog.
     */
    void setSecondaryButton(const char *cstr)
    {
        secondaryButton = cstr;
    }

    /**
     * @brief Set the callback function for the dialog.
     * 
     * The callback function is called when the user interacts with the dialog.
     * The result of the user interaction is passed to the callback function as a boolean parameter.
     * If the user clicks the primary button, the result is true. If the user clicks the secondary button,
     * the result is false.
     * The callback function should have the following signature:
     * @code
     * void callback(bool result)
     * @endcode
     * 
     * @param callback Callback function for the dialog.
     */
    void setCallback(void (*callback)(bool))
    {
        this->callback.simple = callback;
        isTextCallback = false;
    }

    /** 
     * @brief Set the callback function for the dialog with text input.
     * 
     * The callback function is called when the user interacts with the dialog.
     * The result of the user interaction is passed to the callback function as a boolean parameter.
     * If the user clicks the primary (submit) button, the result is true. 
     * If the user clicks outside the dialog or the secondary (cancel) button,
     * the result will be false.
     * Additionally, the text input by the user is passed as a parameter (*text).
     * The callback function should have the following signature:
     * @code
     * void callback(bool result, const char *text)
     * @endcode
     * 
     * @param callback Callback function for the dialog with text input.
     */
    void setCallback(void (*callback)(bool, const char *))
    {
        this->callback.withText = callback;
        isTextCallback = true;
    }

    void invokeCallback(bool result, const char *text)
    {
        this->hasResult = true;
        this->accepted = result;

        if ((dialogType == TEXT_INPUT || dialogType == PASSWORD_INPUT) && isTextCallback){
            setTextResult(text, strlen(text));
            if (callback.withText != nullptr)
            {
                callback.withText(result, text);
                return;
            }
        }else{
            if (callback.simple != nullptr)
            {
                callback.simple(result);
            }
        }
        
    }

    void invokeCallback(bool result)
    {
        this->hasResult = true;
        this->accepted = result;
        if (dialogType == NO_INPUT_TEXT && callback.simple != nullptr){
            callback.simple(result);
        }
    }

    /**
     * @brief Get the result text entered by the user.
     * 
     * This function returns the text entered by the user in the dialog.
     * If no text was entered, it returns an empty string.
     * 
     * @return const char* The result text entered by the user.
     */
    const char* getResultText() const {
        return resultTextBuffer; // Always return the buffer
    }

    uint16_t getBytes(uint8_t *out) override
    {
        offset = 0;
        uint8_t dialogTypeU = (uint8_t)dialogType;
        copyAndOffset(out, &offset, &objID, sizeof(objID));
        copyAndOffset(out, &offset, &tag, sizeof(tag));
        copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
        copyAndOffset(out, &offset, &dialogTypeU, sizeof(dialogTypeU));
        copyAndOffset(out, &offset, &singleButton, sizeof(singleButton));

        copyStringWithLength(out, &offset, title);
        copyStringWithLength(out, &offset, message);
        copyStringWithLength(out, &offset, primaryButton);
        copyStringWithLength(out, &offset, secondaryButton);
        
        return offset;
    }

    uint8_t cmdId = 0; ///< Command ID for the dialog. See the notes for possible cmdId values.
    bool accepted = false; ///< Result of the user interaction with the dialog.
    bool hasResult = false; ///< Flag to indicate if the dialog has a result. The resets to false after each sync.
    bool singleButton = false; ///< Flag to indicate if the dialog has a single button.

private:
    char resultTextBuffer[DIALOG_TEXT_BUFFER_SIZE];
    uint8_t objID = BIND_ID_DIALOG;
    uint16_t offset = 0; ///< Offset for the byte array.
    int strLength = 0; ///< Length of the text string.
    const char *title; ///< Title text for the dialog
    const char *message; ///< Message text for the dialog
    const char *primaryButton = "OK"; ///< Primary button text for the dialog
    const char *secondaryButton = "Cancel"; ///< Secondary button text for the dialog
    DialogType dialogType; ///< Type of the dialog
    static int16_t tagIndex; ///< Tag index for the dialog.
    typedef union {
        void (*simple)(bool);
        void (*withText)(bool, const char *);
    } DialogCallback;
    DialogCallback callback;
    bool isTextCallback = false;

    void setTextResult(const char *cstr, int length) {
        length = min(length, DIALOG_TEXT_BUFFER_SIZE - 1);
        strncpy(resultTextBuffer, cstr, length);
        resultTextBuffer[length] = '\0';
    }
};

#endif // __BINDDIALOG_HPP