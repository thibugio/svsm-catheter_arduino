// serial_utils.h

#ifndef _SERIAL_UTILS_h
#define _SERIAL_UTILS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

void serial_init();

int serial_available(void);

void flush_bytes(int count);

void write_byte(uint8_t b);

void write_bytes(int nb, uint8_t bytes[]);

uint8_t read_byte(void);

#endif

