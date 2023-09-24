#include "BindRectangle.hpp"

int16_t BindRectangle::tagIndex = 1;

BindRectangle::BindRectangle()
{
    this->tag = tagIndex++;
}
