#include "SLPacker.hpp"

size_t SLPacker::encode(uint8_t *writeBuffer, uint8_t const *readBuffer, size_t len){
	size_t read_index = 0;
	size_t write_index = 0;
	writeBuffer[write_index++] = FEND;
	writeBuffer[write_index++] = CMD_DATA;
	while(read_index < len){
		switch (readBuffer[read_index++]) {
			case FEND:
				writeBuffer[write_index++] = FESC;
				writeBuffer[write_index++] = TFEND;
				break;
			case FESC:
				writeBuffer[write_index++] = FESC;
				writeBuffer[write_index++] = TFESC;
				break;
			default:
				writeBuffer[write_index++] = readBuffer[read_index-1];
		}
	}
	writeBuffer[write_index++] = FEND;
	return write_index;
}

size_t SLPacker::encode(uint8_t *readBuffer, size_t len){
	size_t read_index = 0;
	size_t write_index = 0;
	memmove(readBuffer+2,readBuffer,len);
	readBuffer[write_index++] = FEND;
	readBuffer[write_index++] = CMD_DATA;
	while(read_index < len){
	    read_index++;
		switch (readBuffer[write_index]) {
			case FEND:
			    memmove(readBuffer+write_index+2,readBuffer+write_index+1,len-read_index);
				readBuffer[write_index++] = FESC;
				readBuffer[write_index++] = TFEND;
				break;
			case FESC:
			    memmove(readBuffer+write_index+2,readBuffer+write_index+1,len-read_index);
				readBuffer[write_index++] = FESC;
				readBuffer[write_index++] = TFESC;
				break;
 			default:
 				write_index++;
		}
	}
	readBuffer[write_index++] = FEND;
	return write_index;
}
	
size_t SLPacker::decode(uint8_t data){
	switch (slStep) {
		case UNDEF:
			if (data == FEND)
				slStep = GET_CMD;
			break;
		case GET_CMD:
			if (data == CMD_DATA) {
				slStep = GET_DATA;
				memset(buf, 0, sizeof(buf));
				bufIndex =0;
			}else{
				resetState(data);
			}
			break;
		case GET_DATA:
			return dataHandler(data);
			break;
		case ESC_DATA:
			escDataHandler(data);
			break;
	}
	return 0;
}

void SLPacker::writeToRxBuf(uint8_t data){
	if (bufIndex < sizeof(buf)){
		buf[bufIndex++] = data;
	}else{
		resetState(data);
	}
}

void SLPacker::resetState(uint8_t data){
	memset(buf, 0, sizeof(buf));
	bufIndex =0;
	slStep = UNDEF;
	if (data == FEND) {
		decode(data);
	}
}

size_t SLPacker::dataHandler(uint8_t data){
	switch (data) {
		case FESC:
			slStep = ESC_DATA;
			break;
		case FEND:
			slStep = UNDEF;
			return bufIndex;
			break;
		default:
			writeToRxBuf(data);
	}
	return 0;
}

void SLPacker::escDataHandler(uint8_t data){
	switch (data) {
		case TFESC:
			writeToRxBuf(FESC);
			slStep = GET_DATA;
			break;
		case TFEND:
			writeToRxBuf(FEND);
			slStep = GET_DATA;
			break;
		default:
			resetState(data);
	}
}
