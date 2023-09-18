#include "BindUtils.hpp"
#include <string.h>

void copyAndOffset(uint8_t *out, uint16_t *offset, const void *source, size_t num)
{
  memcpy(out + (*offset), source, num);
  *offset += num;
}
