#ifndef __BINDDSWITCH_H
#define __BINDDSWITCH_H
class Switch {
  private:
    bool * value = NULL;
	void (*clickCallback)(bool);
  public:
    Switch() {
      Switch(NULL, NULL);
    }
    Switch(bool *val, void (*_clickCallback)(bool)) {
      value = val;
	  clickCallback = _clickCallback;
    }
    void update(bool val) {
      if (value != NULL) {
        *value = val;
		}
	  if (*clickCallback != NULL) {
		  clickCallback(val);
		}
    }
};
#endif /* __BINDDSWITCH_H */
