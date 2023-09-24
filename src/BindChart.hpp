#ifndef __BINDCHART_HPP
#define __BINDCHART_HPP
#include "BindView.hpp"
#include "BindUtils.hpp"

/**
 * @brief Represents a customizable chart element for BindCanvas.
 *
 * The `BindChart` class provides the capability to create and display customizable charts within a BindCanvas interface.
 * Users can define various attributes of the chart, such as its position, size, color, data ranges, and more.
 * Additionally, users can dynamically update the chart data using the `bind.sync([float chartData], &myChart)` function.
 *
 * Example usage:
 * - Create a `BindChart` object to represent the chart element.
 * - Configure the chart's position, dimensions, color, and data ranges.
 * - Optionally, set the chart to automatically adjust its size based on data.
 * - Synchronize the chart with the BindCanvas using `bind.sync(&myChart)`.
 * - Update the chart's data in real-time using the `bind.sync(136.36f, &myChart)` function.
 *
 */
class BindChart : public BindView
{

public:
    BindChart();
    int16_t x = 0;          ///< X-coordinate position of the chart.
    int16_t y = 0;          ///< Y-coordinate position of the chart.
    uint8_t cmdId = 0;      ///< Command ID for the chart.
    int16_t width = 200;    ///< Width of the chart.
    int16_t height = 100;   ///< Height of the chart.
    int16_t maxY = 10;      ///< Maximum Y-axis value of the chart.
    int16_t minY = -10;     ///< Minimum Y-axis value of the chart.
    int16_t maxX = 20;      ///< Maximum X-axis value of the chart.
    bool autoSize = true;   ///< Flag to enable auto-sizing based on data.
    int32_t color = YELLOW; ///< Color of the chart.

    /**
     * @brief Generates and returns the byte data representing the chart configuration.
     *
     * This function is meant for internal use by the Bind framework and should not be called directly by users.
     * It serializes the chart configuration properties into a byte array for communication with BindCanvas.
     *
     * @param out Pointer to the output byte array.
     * @return The number of bytes written to the output array.
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
        copyAndOffset(out, &offset, &maxY, sizeof(maxY));
        copyAndOffset(out, &offset, &minY, sizeof(minY));
        copyAndOffset(out, &offset, &maxX, sizeof(maxX));
        copyAndOffset(out, &offset, &autoSize, sizeof(autoSize));
        copyAndOffset(out, &offset, &color, sizeof(color));
        return offset;
    }

    /**
     * @brief Generates and returns the byte data representing chart data.
     *
     * This function is meant for internal use by the Bind framework and should not be called directly by users.
     * It serializes the chart data properties into a byte array for communication with BindCanvas.
     *
     * @param out Pointer to the output byte array.
     * @param chartData The data to be added to the chart.
     * @return The number of bytes written to the output array.
     */
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

private:
    uint8_t objID = BIND_ID_CHART;
    uint8_t dataID = BIND_ID_CHART_DATA;
    uint16_t offset = 0;
    static int16_t tagIndex;
};

#endif /* __BINDCHART_HPP */
