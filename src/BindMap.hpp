#ifndef __BINDMAP_HPP
#define __BINDMAP_HPP
#include "BindView.hpp"
#include "BindUtils.hpp"

/// This allows the user to manualy change the map zoom.
#define BIND_MAP_USER_ZOOM -1

/**
 * @brief Represents a Map Object for BindCanvas.
 *
 * The `BindMap` class is used to display and control a street map within the BindCanvas framework.
 * It allows users to show and interact with maps, including changing the map's location, orientation,
 * and zoom level. Users can manually control the map zoom or use predefined zoom levels.
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
 * To use a `BindMap` object, create an instance and configure its properties, including position,
 * dimensions, latitude, longitude, orientation, and zoom level. You can then add it to the BindCanvas
 * for rendering and interaction by calling the sync function.
 *
 * @attention Currently, the framework supports the creation of only one map object.
 * Additional support for multiple maps may be added in future updates.
 * @note The `BIND_MAP_USER_ZOOM` constant can be used to let the user manually change the map's zoom level.
 * You can also set predefined zoom levels as needed.
 */
class BindMap : public BindView
{

public:
    int16_t x;                   ///< X-coordinate position of the map.
    int16_t y;                   ///< Y-coordinate position of the map.
    uint8_t cmdId = 0;           ///< Command identifier for the map. See the notes for possible cmdId values.
    int16_t width = 100;         ///< Width of the map.
    int16_t height = 100;        ///< Height of the map.
    float lat = 0.0f;            ///< Latitude of the map's center.
    float lon = 0.0f;            ///< Longitude of the map's center.
    float mapOrientation = 0.0f; ///< Orientation angle of the map (in degrees).
    int8_t zoom = 1;             ///< Zoom level of the map.

    /**
     * @brief Get the serialized bytes of the `BindMap` object.
     *
     * This function serializes the `BindMap` object into a byte array, which can be sent to BindCanvas
     * for rendering and interaction.
     *
     * @param out Pointer to the output buffer where the serialized data will be stored.
     * @return The number of bytes written to the output buffer.
     */
    uint16_t getBytes(uint8_t *out) override
    {
        tag = 1; // Only one map for now! May extend it in future updates.
        offset = 0;
        copyAndOffset(out, &offset, &objID, sizeof(objID));
        copyAndOffset(out, &offset, &x, sizeof(x));
        copyAndOffset(out, &offset, &y, sizeof(y));
        copyAndOffset(out, &offset, &tag, sizeof(tag));
        copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
        copyAndOffset(out, &offset, &width, sizeof(width));
        copyAndOffset(out, &offset, &height, sizeof(height));
        copyAndOffset(out, &offset, &lat, sizeof(lat));
        copyAndOffset(out, &offset, &lon, sizeof(lon));
        copyAndOffset(out, &offset, &mapOrientation, sizeof(mapOrientation));
        copyAndOffset(out, &offset, &zoom, sizeof(zoom));
        return offset;
    }

private:
    uint8_t objID = BIND_ID_MAP_VIEW;
    uint16_t offset = 0;
};

#endif /* __BINDMAP_HPP */
