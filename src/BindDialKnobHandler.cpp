#include "BindDialKnobHandler.hpp"
void DialKnobHandler::changed(int16_t val) {
  if (value != NULL) {
    *value = val;
  }
  if (changeCallback != NULL) {
	  changeCallback(val);
  }
}
