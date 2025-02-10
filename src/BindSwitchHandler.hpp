#ifndef __BINDSWITCHHANDLER_H
#define __BINDSWITCHHANDLER_H
#include "Stream.h"
#include "BindSwitch.hpp"
// TODO: Extract the class to a serprate .h and .c file! Now!
// TODO: Add the class summaries!
class SwitchHandler
{
private:
  BindSwitch *screenSwitch = NULL;
  void (*clickCallback)(bool);

public:
  SwitchHandler()
  {
    SwitchHandler(NULL, NULL);
  }

  SwitchHandler(void (*_clickCallback)(bool), BindSwitch *_screenSwitch = NULL)
  {
    this->screenSwitch = _screenSwitch;
    clickCallback = _clickCallback;
  }

  void update(bool val)
  {
    if (this->screenSwitch != NULL)
    {
      this->screenSwitch->switchValue = val;
    }
    if (*clickCallback != NULL)
    {
      clickCallback(val);
    }
  }
};

#endif /* __BINDSWITCHHANDLER_H */
