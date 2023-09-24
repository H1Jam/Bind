#include "BindMapMarker.hpp"

int16_t BindMapMarker::tagIndex = 1;

BindMapMarker::BindMapMarker()
{
    this->tag = tagIndex++;
}
