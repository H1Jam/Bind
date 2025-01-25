#include "BindTextInput.hpp"

BindTextInput::BindTextInput(int16_t x, int16_t y, int16_t tag, uint8_t cmdId, const char *text, const char *hint, int16_t fontSize, int32_t textColor, int32_t backColor, uint8_t widthChars, bool numberOnly)
    : x(x), y(y), cmdId(cmdId), fontSize(fontSize), textColor(textColor), backColor(backColor), widthChars(widthChars), numberOnly(numberOnly)
{
    setText(text);
    setHint(hint);
}

BindTextInput::BindTextInput()
{
    setText("");
    setHint("");
}

uint16_t BindTextInput::getBytes(uint8_t *out)
{
    offset = 0;
    strLength = strlen(text);
    if (strLength > MAX_STRING_LENGTH_TERMINAL)
    {
        strLength = MAX_STRING_LENGTH_TERMINAL;
    }
    copyAndOffset(out, &offset, &objID, sizeof(objID));
    copyAndOffset(out, &offset, &x, sizeof(x));
    copyAndOffset(out, &offset, &y, sizeof(y));
    copyAndOffset(out, &offset, &tag, sizeof(tag));
    copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
    copyAndOffset(out, &offset, &fontSize, sizeof(fontSize));
    copyAndOffset(out, &offset, &textColor, sizeof(textColor));
    copyAndOffset(out, &offset, &backColor, sizeof(backColor));
    copyAndOffset(out, &offset, &widthChars, sizeof(widthChars));
    copyAndOffset(out, &offset, &numberOnly, sizeof(numberOnly));
    copyAndOffset(out, &offset, text, strLength);
    // add a 0 byte to terminate the string
    copyAndOffset(out, &offset, "\0", 1);
    strLength = strlen(hint);
    if (strLength > MAX_STRING_LENGTH_TERMINAL)
    {
        strLength = MAX_STRING_LENGTH_TERMINAL;
    }
    copyAndOffset(out, &offset, hint, strLength);
    // add a 0 byte to terminate the string
    copyAndOffset(out, &offset, "\0", 1);
    return offset;
}
