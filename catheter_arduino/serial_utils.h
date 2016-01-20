#pragma once
#ifndef _SERIAL_UTILS_H
#define _SERIAL_UTILS_H

void serial_init();

int serial_available(void);

void flush_bytes(int count);

void write_byte(uint8_t b);

void write_bytes(int nb, uint8_t bytes[]);

uint8_t read_byte(void);

#endif

