#pragma once
#ifndef _COMMON_UTILS_H
#define _COMMON_UTILS_H

/* book-keeping for each channel */
struct channelStatus {
	int enable;
	int dir;
	uint16_t DAC_val;
	uint16_t ADC_val;
};

/* brief representation of a channel command */
struct channelCmd {
	uint8_t addr4;
	uint8_t cmd4;
	uint16_t data12;
	//uint8_t chksum4;
};

/* brief representation of a serial packet */
struct serialPacket {
	uint8_t ok1;
	uint8_t index3;
	uint8_t cmdCnt4;
	uint8_t reserved5;
	//uint8_t chksum8;
	struct channelCmd cmds[];
};

/* return the (4 bit) command value associated with a particular state */
uint8_t compactCmdVal(int poll, int en, int update, int dir);

/* return the state associated with a particular (4 bit) command value */
void expandCmdVal(uint8_t cmdVal, int * poll, int * en, int * update, int * dir);

/* calculate 8-bit fletcher checksum using blocksize=4 */
uint8_t fletcher8(int len, uint8_t data[]);

#endif