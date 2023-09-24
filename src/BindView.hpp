#ifndef __BINDVIEW_HPP
#define __BINDVIEW_HPP
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

static uint8_t MAX_STRING_LENGTH = 32;
static uint8_t MAX_STRING_LENGTH_TERMINAL = 64;

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

#endif /* __BINDVIEW_HPP */