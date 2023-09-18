#ifndef __BINDSEEKBARHANDLER_H
#define __BINDSEEKBARHANDLER_H
#include "Stream.h"
// TODO: Extract the class to a serprate .h and .c file! Now!
// TODO: Add the class summaries!
class SeekBarHandler
{
private:
  int16_t *value = NULL;
  void (*changeCallback)(int16_t);

public:
  SeekBarHandler()
  {
    SeekBarHandler(NULL, NULL);
  }
  SeekBarHandler(int16_t *val, void (*_changeCallback)(int16_t))
  {
    value = val;
    changeCallback = _changeCallback;
  }
  void update(int16_t val)
  {
    if (value != NULL)
    {
      *value = val;
    }
    if (changeCallback != NULL)
    {
      changeCallback(val);
    }
  }
};
#endif /* __BINDSEEKBARHANDLER_H */
