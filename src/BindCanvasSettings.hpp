#ifndef __BINDCANVASSETTINGS_HPP
#define __BINDCANVASSETTINGS_HPP
#include "BindView.h"
#include "BindUtils.hpp"

class BindCanvasSettings : public BindView
{
private:
    uint8_t objID = BindIDs::Settings;
    uint16_t offset = 0;
    int strLength = 0;
    const char *str;

public:
    BindCanvasSettings()
    {
        setlabel("BindApp");
    }
    int8_t screenOrientation = 0;
    int32_t backColor;
    int32_t actionBarColor;
    bool resetScreen = false;
    void setlabel(const char *cstr)
    {
        str = cstr;
    }

    uint16_t getBytes(uint8_t *out, int8_t _screenOrientation, int32_t _backColor, int32_t _actionBarColor, const char *cstr)
    {
        screenOrientation = _screenOrientation;
        backColor = _backColor;
        actionBarColor = _actionBarColor;
        str = cstr;
        return getBytes(out);
    }

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
};
#endif /* __BINDCANVASSETTINGS_HPP */
