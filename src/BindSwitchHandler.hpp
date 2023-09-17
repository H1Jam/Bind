#ifndef __BINDSWITCHHANDLER_H
#define __BINDSWITCHHANDLER_H
class SwitchHandler
{
private:
  bool *value = NULL;
  void (*clickCallback)(bool);

public:
  SwitchHandler()
  {
    SwitchHandler(NULL, NULL);
  }
  SwitchHandler(bool *val, void (*_clickCallback)(bool))
  {
    value = val;
    clickCallback = _clickCallback;
  }
  void update(bool val)
  {
    if (value != NULL)
    {
      *value = val;
    }
    if (*clickCallback != NULL)
    {
      clickCallback(val);
    }
  }
};
#endif /* __BINDSWITCHHANDLER_H */
