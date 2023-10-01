#ifndef __BINDVIEW_HPP
#define __BINDVIEW_HPP
#include <stdint.h>

#define BLACK 0xFF000000
#define DKGRAY 0xFF444444
#define GRAY 0xFF888888
#define LTGRAY 0xFFCCCCCC
#define WHITE 0xFFFFFFFF
#define RED 0xFFFF0000
#define GREEN 0xFF00FF00
#define BLUE 0xFF0000FF
#define YELLOW 0xFFFFFF00
#define CYAN 0xFF00FFFF
#define MAGENTA 0xFFFF00FF
#define UBUNTU 0xFF300A24
#define AVOCADO 0xFF95986B
#define TRANSPARENT 0
#define MAX_STRING_LENGTH_TERMINAL 64

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