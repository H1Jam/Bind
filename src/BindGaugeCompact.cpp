#include "BindGaugeCompact.hpp"

int16_t BindGaugeCompact::tagIndex = 1;

BindGaugeCompact::BindGaugeCompact(const char *cstr)
{
    this->tag = tagIndex++;
    setlabel(cstr);
}
