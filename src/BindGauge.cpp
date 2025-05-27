#include "BindGauge.hpp"

// int16_t BindGauge::tagIndex = 1;

BindGauge::BindGauge(const char *cstr)
{
    this->tag = tagIndex++;
    setLabel(cstr);
}
