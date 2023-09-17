#ifndef __BINDDIALKNOBHANDLER_H
#define __BINDDIALKNOBHANDLER_H
class DialKnobHandler
{
private:
  int16_t *value = NULL;
  void (*changeCallback)(int16_t);

public:
  DialKnobHandler()
  {
    DialKnobHandler(NULL, NULL);
  }
  DialKnobHandler(int16_t *val, void (*_changeCallback)(int16_t))
  {
    value = val;
    changeCallback = _changeCallback;
  }
  void changed(int16_t val);
};
#endif /* __BINDDIALKNOBHANDLER_H */s