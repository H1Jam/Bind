#ifndef __BINDUTILS_H
#define __BINDUTILS_H
#include <stdint.h>
#include <stddef.h>
#include "BindView.h"
/*
 @brief TBA
*/
void copyAndOffset(uint8_t *out, uint16_t *offset, const void *source, size_t num);

#endif /* __BINDUTILS_H */