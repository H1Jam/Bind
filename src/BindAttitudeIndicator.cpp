#include "BindAttitudeIndicator.hpp"

int16_t BindAttitudeIndicator::tagIndex = 1;

BindAttitudeIndicator::BindAttitudeIndicator()
{
    this->tag = tagIndex++;
}
