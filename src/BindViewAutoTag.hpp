#ifndef __BINDVIEWAUTOTAG_H
#define __BINDVIEWAUTOTAG_H
#include "BindView.h"
class BindViewAutoTag : public BindView
{
public:
    static int16_t tagIndex;
    BindViewAutoTag()
    {
        this->tag = tagIndex++;
    }
};
#endif /* __BINDVIEWAUTOTAG_H */
