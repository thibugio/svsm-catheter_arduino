#pragma once
#ifndef _SPI_UTILS_H
#define _SPI_UTILS_H

/* *************** */
/* SPI definitions */
/* *************** */

#define START_DELAY 500     /* delay before first write to DAC */
#define DAC_ADC_DELAY 500   /* delay between write to DAC and read from ADC */
#define ADC_DAC_DELAY 500   /* delay between read from ADC and write to DAC */

#define DAC_SELECT  0b00000000    /* write to DAC A;          bit 15 */
#define INPUT_BUF   0b00000000    /* Vref input not buffered; bit 14 */
#define GAIN_SELECT 0b00100000    /* output gain = 1;         bit 13 */
#define PWR_DOWN    0b00010000    /* output power-down ctrl;  bit 12 */

/* initialize the SPI bus */
void SPI_init();

/*  read a 12-bit value from the MCP3201 ADC on a specified channel (1 through NCHANNELS) */
uint16_t ADC_read(int channel);

/*  write a 12-bit value to the MCP4921 DAC on a specified channel (1 through NCHANNELS) */
void DAC_write(int channel, uint16_t to_dac);

#endif