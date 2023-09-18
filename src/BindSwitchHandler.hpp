#ifndef __BINDSWITCHHANDLER_H
#define __BINDSWITCHHANDLER_H
#include "Stream.h"
// TODO: Extract the class to a serprate .h and .c file! Now!
// TODO: Add the class summaries!
class SwitchHandler
{
private:
  bool *value = NULL;
  void (*clickCallback)(bool);

public:
  SwitchHandler()
  {
    SwitchHandler(NULL, NULL);
  }
  SwitchHandler(bool *val, void (*_clickCallback)(bool))
  {
    value = val;
    clickCallback = _clickCallback;
  }
  void update(bool val)
  {
    if (value != NULL)
    {
      *value = val;
    }
    if (*clickCallback != NULL)
    {
      clickCallback(val);
    }
  }
};
#endif /* __BINDSWITCHHANDLER_H */
