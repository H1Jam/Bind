#ifndef __BINDRECTANGLE_HPP
#define __BINDRECTANGLE_HPP
#include "BindViewAutoTag.hpp"
#include "BindUtils.hpp"
/**
 * @brief Represents a Rectangle Object for BindCanvas.
 *
 * The `BindRectangle` class defines a rectangular object that can be displayed and manipulated
 * on a BindCanvas screen. This object can be used for various purposes, such as drawing shapes,
 * creating backgrounds, or framing other elements. It allows you to control its dimensions, position,
 * fill color, stroke color, stroke width, and corner radius.
 *
 * To use a `BindRectangle` object, you can create an instance and configure its properties,
 * then add it to the BindCanvas using the sync functions.
 *
 * @note This class is typically used to group objects in a zone.
 */
class BindRectangle : public BindViewAutoTag
{
public:
    int16_t x = 0;                ///< X-coordinate position of the rectangle.
    int16_t y = 0;                ///< Y-coordinate position of the rectangle.
    uint8_t cmdId = 0;            ///< Command identifier for the rectangle.
    int16_t width = 200;          ///< Width of the rectangle.
    int16_t height = 100;         ///< Height of the rectangle.
    int32_t fillColor = BLACK;    ///< Fill color of the rectangle.
    int32_t strokeColor = YELLOW; ///< Stroke color of the rectangle.
    int16_t strokeWidth = 10;     ///< Stroke width of the rectangle.
    int16_t cornersRadius = 10;   ///< Radius of the rectangle's rounded corners.

    /**
     * @brief Get the serialized bytes of the `BindRectangle` object.
     *
     * This function serializes the `BindRectangle` object into a byte array, which can be
     * sent to BindCanvas for rendering and interaction.
     *
     * @param out Pointer to the output buffer where the serialized data will be stored.
     * @return The number of bytes written to the output buffer.
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
        copyAndOffset(out, &offset, &fillColor, sizeof(fillColor));
        copyAndOffset(out, &offset, &strokeColor, sizeof(strokeColor));
        copyAndOffset(out, &offset, &strokeWidth, sizeof(strokeWidth));
        copyAndOffset(out, &offset, &cornersRadius, sizeof(cornersRadius));
        return offset;
    }

private:
    uint8_t objID = BindIDs::rectangle;
    uint16_t offset = 0;
};

#endif /* __BINDRECTANGLE_HPP */