#ifndef __BINDVIEW_H
#define __BINDVIEW_H
#include <stdint.h>

static int32_t BLACK = 0xFF000000;
static int32_t DKGRAY = 0xFF444444;
static int32_t GRAY = 0xFF888888;
static int32_t LTGRAY = 0xFFCCCCCC;
static int32_t WHITE = 0xFFFFFFFF;
static int32_t RED = 0xFFFF0000;
static int32_t GREEN = 0xFF00FF00;
static int32_t BLUE = 0xFF0000FF;
static int32_t YELLOW = 0xFFFFFF00;
static int32_t CYAN = 0xFF00FFFF;
static int32_t MAGENTA = 0xFFFF00FF;
static int32_t UBUNTU = 0xFF300A24;
static int32_t AVOCADO = 0xFF95986B;
static int32_t TRANSPARENT = 0;

static int8_t SCREEN_ORIENTATION_UNSET = -2;
static int8_t SCREEN_ORIENTATION_UNSPECIFIED = -1;
static int8_t SCREEN_ORIENTATION_LANDSCAPE = 0;
static int8_t SCREEN_ORIENTATION_PORTRAIT = 1;
static int8_t SCREEN_ORIENTATION_USER = 2;
static int8_t SCREEN_ORIENTATION_BEHIND = 3;
static int8_t SCREEN_ORIENTATION_SENSOR = 4;
static int8_t SCREEN_ORIENTATION_NOSENSOR = 5;
static int8_t SCREEN_ORIENTATION_SENSOR_LANDSCAPE = 6;
static int8_t SCREEN_ORIENTATION_SENSOR_PORTRAIT = 7;
static int8_t SCREEN_ORIENTATION_REVERSE_LANDSCAPE = 8;
static int8_t SCREEN_ORIENTATION_REVERSE_PORTRAIT = 9;
static int8_t SCREEN_ORIENTATION_FULL_SENSOR = 10;
static int8_t SCREEN_ORIENTATION_USER_LANDSCAPE = 11;
static int8_t SCREEN_ORIENTATION_USER_PORTRAIT = 12;
static int8_t SCREEN_ORIENTATION_FULL_USER = 13;
static int8_t SCREEN_ORIENTATION_LOCKED = 14;

static uint8_t MAX_STRING_LENGTH = 32;
static uint8_t MAX_STRING_LENGTH_TERMINAL = 64;
#define RGB(r, g, b) ((int32_t)((uint8_t)(b)) | ((int32_t)(g) << 8) | (((int32_t)(uint8_t)(r)) << 16) | 0xFF000000)
#define RGBA(r, g, b, a) ((int32_t)((uint8_t)(b)) | ((int32_t)(g) << 8) | (((int32_t)(uint8_t)(r)) << 16) | ((int32_t)((uint8_t)(a)) << 24))

enum BindIDs : uint8_t
{
  setupCMD = 5,
  button,
  label,
  gauge1,
  gauge2,
  knob,
  mapView,
  mapMarker,
  toggleSwitch,
  seekBar,
  attitudeIndicator,
  headingIndicator,
  joystick,
  gaugeSimple,
  colorPicker,
  chart,
  chartData,
  rectangle,
  terminal,
  terminalData,
  Settings
};

enum Markers : uint8_t
{
  PinRed = 0,
  PinGreen,
  PinBlue,
  PinYellow,
  CarRed,
  CarGreen,
  CarBlue,
  CarYellow,
  PlaneRed,
  PlaneGreen,
  PlaneBlue,
  PlaneYellow
};


class BindView
{
public:
  /**
   * @brief Retrieves the bytes representing the BindView for synchronization.
   *
   * This function is used to gather the bytes that represent the BindView's properties for synchronization.
   * @note This function should not be called directly by users, Bind calls it internally.
   * 
   * @param out A pointer to the output buffer where the button data will be stored.
   * @return The number of bytes written to the output buffer.
   */
  virtual uint16_t getBytes(uint8_t *out) { return 0; };
  int16_t tag;
};

#endif /* __BINDVIEW_H */