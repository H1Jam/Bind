#include "BindTextLabel.hpp"

// int16_t BindTextLabel::tagIndex = 1;

BindTextLabel::BindTextLabel(const char *cstr)
{
    this->tag = tagIndex++;
    setlabel(cstr);
}
