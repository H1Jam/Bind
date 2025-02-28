#ifndef __BINDUTILS_H
#define __BINDUTILS_H
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "BindView.hpp"

#define RGB(r, g, b) ((int32_t)((uint8_t)(b)) | ((int32_t)(g) << 8) | (((int32_t)(uint8_t)(r)) << 16) | 0xFF000000)
#define RGBA(r, g, b, a) ((int32_t)((uint8_t)(b)) | ((int32_t)(g) << 8) | (((int32_t)(uint8_t)(r)) << 16) | ((int32_t)((uint8_t)(a)) << 24))
#define rgb(r, g, b) RGB(r, g, b) 
#define rgba(r, g, b, a) RGBA(r, g, b, a) 

#define BIND_ID_SETUP_CMD 5
#define BIND_ID_BUTTON 6
#define BIND_ID_LABEL 7
#define BIND_ID_GAUGE1 8
#define BIND_ID_GAUGE2 9
#define BIND_ID_KNOB 10
#define BIND_ID_MAP_VIEW 11
#define BIND_ID_MAP_MARKER 12
#define BIND_ID_TOGGLE_SWITCH 13
#define BIND_ID_SEEK_BAR 14
#define BIND_ID_ATTITUDE_INDICATOR 15
#define BIND_ID_HEADING_INDICATOR 16
#define BIND_ID_JOYSTICK 17
#define BIND_ID_GAUGE_SIMPLE 18
#define BIND_ID_COLOR_PICKER 19
#define BIND_ID_CHART 20
#define BIND_ID_CHART_DATA 21
#define BIND_ID_RECTANGLE 22
#define BIND_ID_TERMINAL 23
#define BIND_ID_TERMINAL_DATA 24
#define BIND_ID_SETTINGS 25
#define BIND_ID_TEXTINPUT 26
#define BIND_ID_DIALOG 27


#define MARKER_PIN_RED 0
#define MARKER_PIN_GREEN 1
#define MARKER_PIN_BLUE 2
#define MARKER_PIN_YELLOW 3
#define MARKER_CAR_RED 4
#define MARKER_CAR_GREEN 5
#define MARKER_CAR_BLUE 6
#define MARKER_CAR_YELLOW 7
#define MARKER_PLANE_RED 8
#define MARKER_PLANE_GREEN 9
#define MARKER_PLANE_BLUE 10
#define MARKER_PLANE_YELLOW 11

/*
 @brief TBA
*/
void copyAndOffset(uint8_t *out, uint16_t *offset, const void *source, size_t num);
void copyStringWithLength(uint8_t *out, uint16_t *offset, const char *str);
#endif /* __BINDUTILS_H */