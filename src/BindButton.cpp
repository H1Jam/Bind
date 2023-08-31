#include "BindButton.hpp"
void Button::clicked() {
  if (*clickCallback != NULL) {
    clickCallback();
  }
}
