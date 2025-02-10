#ifndef __BINDSEEKBARHANDLER_H
#define __BINDSEEKBARHANDLER_H
#include "Stream.h"
#include "BindSeekBar.hpp"
// TODO: Extract the class to a serprate .h and .c file! Now!
// TODO: Add the class summaries!
class SeekBarHandler
{
private:
BindSeekBar *screenSeekBar = NULL;
void (*changeCallback)(int16_t) = NULL;

public:

  SeekBarHandler(BindSeekBar *_screenSeekBar = NULL, void (*_changeCallback)(int16_t) = NULL)
  {
    this->screenSeekBar = _screenSeekBar;
    this->changeCallback = _changeCallback;
  }

  void update(int16_t val)
  {
    if (this->screenSeekBar != NULL)
    {
      this->screenSeekBar->seekValue = val;
    }
    if (this->changeCallback != NULL)
    {
      this->changeCallback(val);
    }
  }
};
#endif /* __BINDSEEKBARHANDLER_H */
