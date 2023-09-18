#include "BindDialKnobHandler.hpp"
// TODO: Add the class summaries!
void DialKnobHandler::changed(int16_t val)
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

DialKnobHandler::DialKnobHandler()
{
  DialKnobHandler(NULL, NULL);
}

DialKnobHandler::DialKnobHandler(int16_t *val, void (*_changeCallback)(int16_t))
{
  value = val;
  changeCallback = _changeCallback;
}
