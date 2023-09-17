#ifndef __BINDVIEW_H
#define __BINDVIEW_H
#include <stdint.h>
class BindView
{
public:
  virtual uint16_t getBytes(uint8_t *out) { return 0; };
  int16_t tag;
};

#endif /* __BINDVIEW_H */