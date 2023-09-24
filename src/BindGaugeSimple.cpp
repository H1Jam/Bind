#include "BindGaugeSimple.hpp"

int16_t BindGaugeSimple::tagIndex = 1;

BindGaugeSimple::BindGaugeSimple(const char *cstr)
{
    this->tag = tagIndex++;
    setlabel(cstr);
}
