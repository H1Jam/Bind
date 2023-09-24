#include "BindTerminal.hpp"

int16_t BindTerminal::tagIndex = 1;

BindTerminal::BindTerminal()
{
    this->tag = tagIndex++;
}
