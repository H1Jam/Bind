#ifndef __BINDDIALKNOB_H
#define __BINDDIALKNOB_H
class DialKnob {
  private:
    int16_t * value = NULL;
  public:
    DialKnob() {
      DialKnob(NULL);
    }
    DialKnob(int16_t *val) {
      value = val;
    }
    void changed(int16_t val);
};
#endif /* __BINDDIALKNOB_H */