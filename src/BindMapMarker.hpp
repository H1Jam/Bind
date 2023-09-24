#ifndef __BINDMAPMARKER_HPP
#define __BINDMAPMARKER_HPP
#include "BindView.hpp"
#include "BindUtils.hpp"
/**
 * @brief Represents a marker to be used in BindMap (street map) within BindCanvas.
 *
 * This class defines a marker object that can be placed on a BindMap, which is displayed
 * within the BindCanvas framework. Markers can represent points of interest or specific
 * locations on the map. You can chose the icons from several predefined icons
 * includind pins, cars, planes from Markers, for example Markers::PinRed or Markers::CarBlue.
 * Visit Markers enum in BindView.h for more markers.
 */
class BindMapMarker : public BindView
{
public:
    BindMapMarker();
    float lat = 0.0f;                 ///< Latitude coordinate of the marker's position.
    float lon = 0.0f;                 ///< Longitude coordinate of the marker's position.
    float rotation = 0.0f;            ///< Rotation angle of the marker (in degrees).
    uint8_t scale = 100;              ///< Scale factor for the marker's size.
    uint8_t iconId = MARKER_PIN_RED; ///< Identifier for the marker's icon. Visit Markers enum in BindView.h
    uint8_t cmdId = 0;                ///< Command identifier.

    /**
     * @brief Serializes the marker data into a byte array.
     *
     * This function serializes the marker's properties into a byte array for communication
     * and rendering within the BindCanvas framework.
     *
     * @param out Pointer to the output byte array.
     * @return The offset within the byte array after serialization.
     */
    uint16_t getBytes(uint8_t *out) override
    {
        offset = 0;
        copyAndOffset(out, &offset, &objID, sizeof(objID));
        copyAndOffset(out, &offset, &tag, sizeof(tag));
        copyAndOffset(out, &offset, &lat, sizeof(lat));
        copyAndOffset(out, &offset, &lon, sizeof(lon));
        copyAndOffset(out, &offset, &rotation, sizeof(rotation));
        copyAndOffset(out, &offset, &iconId, sizeof(iconId));
        copyAndOffset(out, &offset, &scale, sizeof(scale));
        copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
        return offset;
    }

private:
    uint8_t objID = BIND_ID_MAP_MARKER; ///< Unique identifier for map markers.
    uint16_t offset = 0;                ///< Offset for byte data serialization.
    static int16_t tagIndex;
};

#endif /* __BINDMAPMARKER_HPP */
