#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <SPI.h>

#include "common_defs.h"
#include "arduino_defs.h"
#include "spi_utils.h"

/* ******************* */
/* spi pin definitions */
/* ******************* */

// dac and adc pins
int ADC_CS_pins[NCHANNELS] = { 8,9,10,11,12,13 };
int DAC_CS_pins[NCHANNELS] = { 2,3,4,5,6,7 };
int DAC_LDAC_pins[NCHANNELS] = { 46,47,48,49,50,51 };


/* ************* */
/* SPI functions */
/* ************* */

/* initialize the SPI bus */
void SPI_init() {

    // initial SPI pins for DAC and ADC
    for (int i = 0; i < NCHANNELS; i++) {
        pinMode(ADC_CS_pins[i], OUTPUT);
        pinMode(DAC_CS_pins[i], OUTPUT);
        pinMode(DAC_LDAC_pins[i], OUTPUT);

        digitalWrite(ADC_CS_pins[i], !CS_EN);
        digitalWrite(DAC_CS_pins[i], !CS_EN);
        digitalWrite(DAC_LDAC_pins[i], LOW);
    }
    
	SPI.begin();
#ifdef DUE
	SPI.setClockDivider(SPI_CLOCK_DIV4);    /* 20 MHz (due is 88, mega2560 is 16) */
#endif
	SPI.setBitOrder(MSBFIRST);

	for (int i = 0; i <= NCHANNELS; i++) {
		DAC_write(i, (uint16_t)(DAC_RES - 1));
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
	delay(50);
	digitalWrite(DAC_CS_pins[channel - 1], CS_EN);
	byte dataMSB = highByte(to_dac);
	byte dataLSB = lowByte(to_dac);

	dataMSB &= 0b00001111;
	dataMSB = dataMSB | DAC_SELECT | INPUT_BUF | GAIN_SELECT | PWR_DOWN;
	SPI.transfer(dataMSB);
	SPI.transfer(dataLSB);

	digitalWrite(DAC_CS_pins[channel - 1], !CS_EN);
	delay(50);
}


