#ifndef __BINDCHART_HPP
#define __BINDCHART_HPP
#include "BindViewAutoTag.hpp"
#include "BindUtils.hpp"
class BindChart : public BindViewAutoTag
{
private:
    uint8_t objID = BindIDs::chart;
    uint8_t dataID = BindIDs::chartData;
    uint16_t offset = 0;

public:
    int16_t x = 0;
    int16_t y = 0;
    uint8_t cmdId = 0;
    int16_t width = 200;
    int16_t height = 100;
    int16_t maxY = 10;
    int16_t minY = -10;
    int16_t maxX = 20;
    bool autoSize = true;
    int32_t color = YELLOW;
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
        copyAndOffset(out, &offset, &maxY, sizeof(maxY));
        copyAndOffset(out, &offset, &minY, sizeof(minY));
        copyAndOffset(out, &offset, &maxX, sizeof(maxX));
        copyAndOffset(out, &offset, &autoSize, sizeof(autoSize));
        copyAndOffset(out, &offset, &color, sizeof(color));
        return offset;
    }
    uint16_t getDataBytes(uint8_t *out, float chartData)
    {
        offset = 0;
        copyAndOffset(out, &offset, &dataID, sizeof(dataID));
        copyAndOffset(out, &offset, &tag, sizeof(tag));
        copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
        copyAndOffset(out, &offset, &chartData, sizeof(chartData));
        copyAndOffset(out, &offset, &color, sizeof(color));
        return offset;
    }
};

#endif /* __BINDCHART_HPP */
