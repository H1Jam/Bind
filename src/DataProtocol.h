#ifndef __DATAPROTOCOL_H
#define __DATAPROTOCOL_H
#include <stdint.h>
#include <string.h>
#define MAX_DATA_LENGHT  100
static uint8_t VERSIONID = 0;

static int32_t BLACK       = 0xFF000000;
static int32_t DKGRAY      = 0xFF444444;
static int32_t GRAY        = 0xFF888888;
static int32_t LTGRAY      = 0xFFCCCCCC;
static int32_t WHITE       = 0xFFFFFFFF;
static int32_t RED         = 0xFFFF0000;
static int32_t GREEN       = 0xFF00FF00;
static int32_t BLUE        = 0xFF0000FF;
static int32_t YELLOW      = 0xFFFFFF00;
static int32_t CYAN        = 0xFF00FFFF;
static int32_t MAGENTA     = 0xFFFF00FF;
static int32_t UBUNTU     = 0xFF300A24;
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
uint8_t const dataHeader[3] = {199, 201, 176};
enum DataDirection {toAndroid, fromAndroid};

enum ScreenIDs : uint8_t {
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

enum MarkerIcons : uint8_t {
PinRed,
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

int sendFrame(uint8_t *destBuffer, uint8_t const *buffer, size_t len);
bool checkCRC(uint8_t const *buffer, size_t len);
class DataParser {
  private:
    uint8_t dataIn[3] = {0, 0, 0};
    int bufIndex = 0;
    int dataStep = 0;
    int dataLength = 0;
  public:
    uint8_t buf[MAX_DATA_LENGHT];
    int update(uint8_t inp);
};

#endif /* __DATAPROTOCOL_H */
