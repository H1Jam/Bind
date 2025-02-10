#ifndef __BINDJOYSTICKHANDLER_H
#define __BINDJOYSTICKHANDLER_H
#include "Stream.h"
#include "BindJoystick.hpp"
// TODO: Extract the class to a serprate .h and .c file! Now!
// TODO: Add the class summaries!
class JoystickHandler
{
private:
  BindJoystick *screenJoystick = NULL;
  void (*changeCallback)(int16_t, int16_t) = NULL;

public:

  JoystickHandler(BindJoystick *_screenJoystick = NULL, void (*_changeCallback)(int16_t, int16_t) = NULL)
  {
    this->screenJoystick = _screenJoystick;
    this->changeCallback = _changeCallback;
  }

  void update(int16_t valX, int16_t valY)
  {
    if (this->screenJoystick != NULL)
    {
      this->screenJoystick->sX = valX;
      this->screenJoystick->sY = valY;
    }
    if (this->changeCallback != NULL)
    {
      this->changeCallback(valX, valY);
    }
  }
};

#endif /* __BINDJOYSTICKHANDLER_H */
