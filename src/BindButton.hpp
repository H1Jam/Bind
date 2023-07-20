#ifndef __BINDBUTTON_H
#define __BINDBUTTON_H
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
#endif /* __BINDBUTTON_H */