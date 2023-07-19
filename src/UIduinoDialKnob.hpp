#ifndef __UIDUINODIALKNOB_H
#define __UIDUINODIALKNOB_H
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
#endif /* __UIDUINODIALKNOB_H */