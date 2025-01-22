#ifndef __BINDTEXTINPUTHANDLER_H
#define __BINDTEXTINPUTHANDLER_H

#include "Stream.h"

class TextInputHandler
{
private:
    void (*changeCallback)(const char *, uint8_t);
public:
    TextInputHandler()
    {
        TextInputHandler(NULL);
    }
    TextInputHandler(void (*_changeCallback)(const char *, uint8_t))
    {
        changeCallback = _changeCallback;
    }
    void update(const char *val, uint8_t length)
    {
        // if (value != NULL)
        // {
        //     strncpy((char*)value, val, length);
        //     ((char*)value)[length] = '\0'; // Null-terminate the string
        // }
        if (*changeCallback != NULL)
        {
            changeCallback(val, length);
        }
    }
};

#endif /* __BINDTEXTINPUTHANDLER_H */