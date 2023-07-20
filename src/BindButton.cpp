#include "Bind.hpp"
void Button::clicked() {
  if (*clickCallback != NULL) {
    clickCallback();
  }
}
