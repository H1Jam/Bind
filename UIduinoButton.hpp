#ifndef __UIDUINOBUTTON_H
#define __UIDUINOBUTTON_H
class Button {
  private:
    void (*clickCallback)(void);
  public:
    Button() {
      clickCallback = NULL;
    }
    Button(void (*_clickCallback)(void)) {
      clickCallback = _clickCallback;
    }
    void clicked();
};
#endif /* __UIDUINOBUTTON_H */