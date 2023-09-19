#ifndef __BINDTERMINAL_HPP
#define __BINDTERMINAL_HPP
#include "BindViewAutoTag.hpp"
#include "BindUtils.hpp"
class BindTerminal : public BindViewAutoTag
{
private:
    uint8_t objID = BindIDs::terminal;
    uint8_t dataID = BindIDs::terminalData;
    uint16_t offset = 0;
    int strLength = 0;

public:
    int16_t x = 0;
    int16_t y = 0;
    uint8_t cmdId = 0;
    int16_t width = 200;
    int16_t height = 100;
    int16_t textSize = 10;
    int32_t backColor = UBUNTU;
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
};
#endif /* __BINDTERMINAL_HPP */
