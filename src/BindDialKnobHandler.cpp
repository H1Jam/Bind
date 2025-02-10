#include "BindDialKnobHandler.hpp"
// TODO: Add the class summaries!
void DialKnobHandler::changed(int16_t val)
{
  if (this->screenKnob != NULL)
  {
    this->screenKnob->value = val;
  }
  if (this->changeCallback != NULL)
  {
    this->changeCallback(val);
  }
}

DialKnobHandler::DialKnobHandler(BindKnob *screenKnob, void (*_changeCallback)(int16_t))
{
  this->screenKnob = screenKnob;
  this->changeCallback = _changeCallback;
}
