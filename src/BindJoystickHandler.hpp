#ifndef __BINDJOYSTICKHANDLER_H
#define __BINDJOYSTICKHANDLER_H
#include "Stream.h"
// Todo: Move the implementations to the c file!
class JoystickHandler
{
private:
  int16_t *valueX = NULL;
  int16_t *valueY = NULL;
  void (*changeCallback)(int16_t, int16_t);

public:
  JoystickHandler()
  {
    JoystickHandler(NULL, NULL, NULL);
  }
  JoystickHandler(int16_t *valX, int16_t *valY, void (*_changeCallback)(int16_t, int16_t))
  {
    valueX = valX;
    valueY = valY;
    changeCallback = _changeCallback;
  }
  void update(int16_t valX, int16_t valY)
  {
    if (valueX != NULL && valueY != NULL)
    {
      *valueX = valX;
      *valueY = valY;
    }
    if (changeCallback != NULL)
    {
      changeCallback(valX, valY);
    }
  }
};
#endif /* __BINDJOYSTICKHANDLER_H */
