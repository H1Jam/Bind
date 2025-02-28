#include "BindUtils.hpp"
#include <string.h>

void copyAndOffset(uint8_t *out, uint16_t *offset, const void *source, size_t num)
{
  memcpy(out + (*offset), source, num);
  *offset += num;
}

void copyStringWithLength(uint8_t *out, uint16_t *offset, const char *str)
{
    uint8_t length = strlen(str);
    if (length > MAX_STRING_LENGTH_TERMINAL)
    {
        length = MAX_STRING_LENGTH_TERMINAL;
    }
    out[(*offset)++] = length;
    if (length > 0)
    {
        copyAndOffset(out, offset, str, length);
    }
}
