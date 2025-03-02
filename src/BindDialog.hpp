#ifndef __BINDDIALOG_HPP
#define __BINDDIALOG_HPP
#include "BindView.hpp"
#include "BindUtils.hpp"

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
    : dialogType(type), title(nullptr), message(nullptr), primaryButton("OK"), secondaryButton("Cancel"), resultText(nullptr)
    {
        this->tag = tagIndex++;
        setTitle("Confirmation");
        setMessage("Are you sure?");
        setPrimaryButton("OK");
        setSecondaryButton("Cancel");
        setTextResult("", 0);
    }

    ~BindDialog()
    {
        if (resultText != nullptr) {
            delete[] resultText;
        }
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
        this->callback = callback;
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
        this->callbackWithText = callback;
    }

    void invokeCallback(bool result, const char *text)
    {
        this->hasResult = true;
        this->accepted = result;

        if (dialogType == TEXT_INPUT || dialogType == PASSWORD_INPUT){
            setTextResult(text, strlen(text));
            if (callbackWithText != nullptr)
            {
                callbackWithText(result, text);
            }
        }

        if (callback != nullptr)
        {
            callback(result);
        }
        
    }

    void invokeCallback(bool result)
    {
        this->hasResult = true;
        this->accepted = result;
        if (callback != nullptr)
        {
            callback(result);
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
    const char* getResultText() const
    {
        if (resultText != nullptr) {
            return resultText;
        }else{
            return "";
        }
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
    uint8_t objID = BIND_ID_DIALOG;
    uint16_t offset = 0; ///< Offset for the byte array.
    int strLength = 0; ///< Length of the text string.
    const char *title; ///< Title text for the dialog
    const char *message; ///< Message text for the dialog
    const char *primaryButton = "OK"; ///< Primary button text for the dialog
    const char *secondaryButton = "Cancel"; ///< Secondary button text for the dialog
    DialogType dialogType; ///< Type of the dialog
    static int16_t tagIndex; ///< Tag index for the dialog.
    void (*callback)(bool) = nullptr;
    void (*callbackWithText)(bool, const char *) = nullptr;
    char *resultText = nullptr;

    void setTextResult(const char *cstr, int length)
    {
        if (cstr == resultText || length < 0) {
            return; // Handle self-assignment
        }
        
        // Allocate memory for the new text
        if (resultText != nullptr) {
            delete[] resultText;
        }
        resultText = new char[length + 1];
        strncpy(resultText, cstr, length);
        resultText[length] = '\0'; // Null-terminate the string
    }
};

#endif // __BINDDIALOG_HPP