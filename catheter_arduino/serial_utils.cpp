#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "serial_utils.h"

/* **************** */
/* Serial functions */
/* **************** */

/* start serial connection for Atmega2560 */
void serial_init() {
#ifdef DUE
	//set millisecond timeout so commands can be entered
	SerialUSB.setTimeout(100);
	SerialUSB.begin(9600);
	//while (! SerialUSB); // Wait untilSerial is ready - Leonardo
#else
	Serial.setTimeout(100);
	Serial.begin(9600);
#endif
}

int serial_available(void) {
#ifdef DUE
	return SerialUSB.available();
#else
	return Serial.available();
#endif
}

void flush_bytes(int count) {
	int i;
	for (i = 0; i<count; i++) {
#ifdef DUE
		SerialUSB.read();
#else
		Serial.read();
#endif
	}
}

void write_byte(uint8_t b) {
#ifdef DUE
	SerialUSB.write(b);
#else
	Serial.write(b);
#endif
}

void write_bytes(int nb, uint8_t bytes[]) {
	int i;
	for (i = 0; i<nb; i++) {
		write_byte(bytes[i]);
	}
}

uint8_t read_byte(void) {
#ifdef DUE
	return (uint8_t)(SerialUSB.read());
#else
	return (uint8_t)(Serial.read());
#endif  
}