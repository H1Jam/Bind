#include "BindButtonHandler.hpp"
void ButtonHandler::clicked()
{
  if (*clickCallback != NULL)
  {
    clickCallback();
  }
}
ButtonHandler::ButtonHandler(void (*_clickCallback)(void))
{
  clickCallback = _clickCallback;
}
