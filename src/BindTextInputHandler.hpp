#ifndef __BINDTEXTINPUTHANDLER_H
#define __BINDTEXTINPUTHANDLER_H

#include "Stream.h"
#include "BindTextInput.hpp"

class TextInputHandler
{
private:
    void (*changeCallback)(const char *, uint8_t) = NULL;
    BindTextInput* obj = NULL;
public:
    TextInputHandler()
    {
        TextInputHandler(NULL);
    }
    TextInputHandler(void (*_changeCallback)(const char *, uint8_t), BindTextInput* bindTextInput = NULL)
    {
        changeCallback = _changeCallback;
        obj = bindTextInput;
    }

    void update(const char *val, uint8_t length)
    {
        if (obj != NULL)
        {
            obj->setText(val, length);
        }

        if (*changeCallback != NULL && val != NULL && length >= 0)
        {
            char value[length + 1];
            strncpy((char*)value, val, length);
            changeCallback(value, length);
        }
    }
};

#endif /* __BINDTEXTINPUTHANDLER_H */