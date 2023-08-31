#ifndef __SLPACKER_H
#define __SLPACKER_H
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#define MAX_DATA_LENGHT  100

class SLPacker {
  private:
	enum SLSteps {
		UNDEF, 
		GET_CMD, 
		GET_DATA, 
		ESC_DATA
	};
    size_t bufIndex = 0;
    SLSteps slStep = UNDEF;
	static const uint8_t FEND = 0xC0;
	static const uint8_t FESC = 0xDB;
	static const uint8_t TFEND = 0xDC;
	static const uint8_t TFESC = 0xDD;
	static const uint8_t CMD_DATA = 0x00;
	void writeToRxBuf(uint8_t data);
	void resetState(uint8_t data);
	size_t dataHandler(uint8_t data);
	void escDataHandler(uint8_t data);
  public:
    uint8_t buf[MAX_DATA_LENGHT*2];
	size_t encode(uint8_t *writeBuffer, uint8_t const *readBuffer, size_t len);
	static size_t encode(uint8_t *readBuffer, size_t len);
    size_t decode(uint8_t data);
};

#endif /* __SLPACKER_H */