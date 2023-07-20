#include "Bind.hpp"
void DialKnob::changed(int16_t val) {
  if (value != NULL) {
    *value = val;
  }
}
