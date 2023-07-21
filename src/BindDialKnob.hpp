#ifndef __BINDDIALKNOB_H
#define __BINDDIALKNOB_H
class DialKnob {
  private:
    int16_t * value = NULL;
	void (*changeCallback)(int16_t);
  public:
    DialKnob() {
      DialKnob(NULL, NULL);
    }
    DialKnob(int16_t *val, void (*_changeCallback)(int16_t)) {
      value = val;
	  changeCallback =_changeCallback;
    }
    void changed(int16_t val);
};
#endif /* __BINDDIALKNOB_H */