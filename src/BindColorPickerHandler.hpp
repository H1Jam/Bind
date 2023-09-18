#ifndef __BINDCOLORPICKERHANDLER_H
#define __BINDCOLORPICKERHANDLER_H
#include "Stream.h"
// TODO: Extract the class to a serprate .h and .c file! Now!
// TODO: Add the class summaries!
class ColorPickerHandler
{
private:
  void (*clickCallback)(uint8_t, uint8_t, uint8_t);
  uint8_t *red = NULL;
  uint8_t *green = NULL;
  uint8_t *blue = NULL;

public:
  ColorPickerHandler()
  {
    ColorPickerHandler(NULL, NULL, NULL, NULL);
  }
  ColorPickerHandler(uint8_t *r, uint8_t *g, uint8_t *b, void (*_clickCallback)(uint8_t, uint8_t, uint8_t))
  {
    red = r;
    green = g;
    blue = b;
    clickCallback = _clickCallback;
  }
  void update(uint8_t r, uint8_t g, uint8_t b)
  {
    if (red != NULL && green != NULL && blue != NULL)
    {
      *red = r;
      *green = g;
      *blue = b;
    }
    if (*clickCallback != NULL)
    {
      clickCallback(r, g, b);
    }
  }
};
#endif /* __BINDCOLORPICKERHANDLER_H */