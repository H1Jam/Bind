#ifndef __BINDDIALKNOBHANDLER_H
#define __BINDDIALKNOBHANDLER_H
#include "Stream.h" // for NULL
// TODO: Add the class summaries!
class DialKnobHandler
{
private:
  int16_t *value = NULL;
  void (*changeCallback)(int16_t);

public:
  DialKnobHandler();
  DialKnobHandler(int16_t *val, void (*_changeCallback)(int16_t));
  void changed(int16_t val);
};
#endif /* __BINDDIALKNOBHANDLER_H */