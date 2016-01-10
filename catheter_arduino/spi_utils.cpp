// 
// 
// 

#include "spi_utils.h"

/* ************* */
/* SPI functions */
/* ************* */

/* initialize the SPI bus */
void SPI_init() {
	SPI.begin();
#ifdef DUE
	SPI.setClockDivider(SPI_CLOCK_DIV4);    /* 20 MHz (due is 88, mega2560 is 16) */
#endif
	SPI.setBitOrder(MSBFIRST);

	for (int i = 0; i <= NCHANNELS; i++) {
		DAC_write(i, (uint16_t)4095);
	}
}

/*  read a 12-bit value from the MCP3201 ADC on a specified channel (1 through NCHANNELS) */
uint16_t ADC_read(int channel) {
	digitalWrite(ADC_CS_pins[channel - 1], CS_EN);
	byte b1 = SPI.transfer(0x00);
	byte b2 = SPI.transfer(0x00);
	digitalWrite(ADC_CS_pins[channel - 1], !CS_EN);
	uint16_t ret = ((b1 << 8) | b2) >> 1;   //combine the bytes and get rid of blank first bit
	return ret;
}

/*  write a 12-bit value to the MCP4921 DAC on a specified channel (1 through NCHANNELS) */
void DAC_write(int channel, uint16_t to_dac) {

	//    for (int i=0; i<NCHANNELS; i++) {
	//      delay(50);
	//      digitalWrite(DAC_CS_pins[i], CS_EN);
	//    }
	delay(50);
	digitalWrite(DAC_CS_pins[channel - 1], CS_EN);
	byte dataMSB = highByte(to_dac);
	byte dataLSB = lowByte(to_dac);
	//    byte dataMSB = highByte(2500);
	//    byte dataLSB = lowByte(2500);
	dataMSB &= 0b00001111;
	dataMSB = dataMSB | DAC_SELECT | INPUT_BUF | GAIN_SELECT | PWR_DOWN;
	SPI.transfer(dataMSB);
	SPI.transfer(dataLSB);
	//    for (int i=0; i<NCHANNELS; i++) {
	//      delay(50);
	//      digitalWrite(DAC_CS_pins[i], !CS_EN);
	//    }
	digitalWrite(DAC_CS_pins[channel - 1], !CS_EN);
	delay(50);

	//    write_byte((12 << 4) + (packetIndex & 15));
	//    //dac res is 12-bits; 6 bits in each byte
	//    byte hb = highByte(to_dac);
	//    byte lb = lowByte(to_dac);
	//    write_byte(((hb & 15) << 2) + ((lb & 192) >> 6)); //'00'+ bits 11 downto 6
	//    write_byte(lb & 63); //'00' + bits 5 downto 0
}


