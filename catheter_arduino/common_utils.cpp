#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <stdint.h>
#include <stdlib.h>

#include "common_defs.h"
#include "common_utils.h"


/* return the (4 bit) command value associated with a particular state */
uint8_t compactCmdVal(int poll, int en, int update, int dir) {
	unsigned int cmd = 0;
	if (poll)   cmd |= (1 << POL_B);
	if (en)     cmd |= (1 << ENA_B);
	if (update) cmd |= (1 << UPD_B);
	if (dir)    cmd |= (1 << DIR_B);
	return cmd;
}

/* return the state associated with a particular (4 bit) command value */
void expandCmdVal(uint8_t cmdVal, int * poll, int * en, int * update, int * dir) {
	*poll = (cmdVal >> POL_B) & 1;
	*en = (cmdVal >> ENA_B) & 1;
	*update = (cmdVal >> UPD_B) & 1;
	*dir = (cmdVal >> DIR_B) & 1;
}

/* calculate 8-bit fletcher checksum using blocksize=4 */
uint8_t fletcher8(int len, uint8_t data[]) {
	uint8_t sum1 = 0, sum2 = 0;
	int i;
	for (i = 0; i<len; i++) {
		sum1 += (data[i] >> 4);   //first 4 bits
		sum2 += sum1;

		sum1 += (data[i] & 15);   //last 4 bits
		sum2 += sum1;

		sum1 %= 15;   //modulo 15
		sum2 %= 15;
	}
	sum1 %= 15;
	sum2 %= 15;

	return ((sum2 & 15) << 4) + (sum1 & 15);
}