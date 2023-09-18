#ifndef __BINDBUTTONHANDLER_H
#define __BINDBUTTONHANDLER_H
#include "Stream.h"
// TODO: Add the class summaries!
class ButtonHandler
{
private:
  void (*clickCallback)(void);

public:
  ButtonHandler()
  {
    clickCallback = NULL;
  }
  ButtonHandler(void (*_clickCallback)(void));
  void clicked();
};
#endif /* __BINDBUTTONHANDLER_H */