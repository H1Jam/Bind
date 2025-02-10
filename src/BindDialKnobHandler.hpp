#ifndef __BINDDIALKNOBHANDLER_H
#define __BINDDIALKNOBHANDLER_H
#include "Stream.h" // for NULL
#include "BindKnob.hpp"
// TODO: Add the class summaries!
class DialKnobHandler
{
private:
  BindKnob *screenKnob = NULL;
  void (*changeCallback)(int16_t) = NULL;

public:
  DialKnobHandler(BindKnob *screenKnob = NULL, void (*_changeCallback)(int16_t) = NULL);
  void changed(int16_t val);
};
#endif /* __BINDDIALKNOBHANDLER_H */