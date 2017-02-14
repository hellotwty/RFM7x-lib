#include <avr/io.h>
//#include "spi_xmega.h"

void spi_init(void)
{
	PORTC.DIRSET = PIN5_bm | PIN7_bm; // sck , mosi
	
	PORTC.PIN6CTRL = PORT_OPC_PULLUP_gc; // pullup miso
	
	SPIC.CTRL = SPI_ENABLE_bm | SPI_MASTER_bm | SPI_MODE_0_gc | SPI_PRESCALER_DIV4_gc;
}

uint8_t spi_xfer(uint8_t dat) // spi on PORTC in this case
{
	SPIC.DATA = dat;
	while(!(SPIC.STATUS & (1<<7)));

	return SPIC.DATA;	
}

// internally used alias for spi function (to not force name for generic spi transfer functions)
uint8_t rfm7x_xfer_spi(uint8_t dat) __attribute__ ((alias ("spi_xfer"))); 

// void spi_reg_write(uint8_t reg, uint8_t dat)
// {
// 	spi_xfer(reg);
// 	spi_xfer(dat);
// }
// 
// uint8_t spi_reg_read(uint8_t reg)
// {
// 	uint8_t tmp;
// 	
// 	spi_xfer(reg);
// 	tmp = spi_xfer(0);  
// 	
// 	return tmp; // spi_xfer(spi_xfer(reg))
// }

// void spi_reg_buff_write(uint8_t reg, uint8_t *buff, uint8_t len)
// {
// 	spi_xfer(reg);
// 	
// 	for(uint8_t i=0; i<len; i++)
// 		spi_xfer(buff[i]);
// }

void spi_buff_write(uint8_t *buff, uint8_t len)
{
	for(uint8_t i=0; i<len; i++)
		spi_xfer(buff[i]);
}

uint8_t rfm7x_buff_write(uint8_t dat) __attribute__ ((alias ("spi_buff_write")));

// void spi_reg_buff_read(uint8_t reg, uint8_t *buff, uint8_t len)
// {
// 	spi_xfer(reg);
// 	
// 	for(uint8_t i=0; i<len; i++)
// 		buff[i] = spi_xfer(0);
// }

void spi_buff_read(uint8_t *buff, uint8_t len)
{
	for(uint8_t i=0; i<len; i++)
		buff[i] = spi_xfer(0);
}

uint8_t rfm7x_buff_read(uint8_t dat) __attribute__ ((alias ("spi_buff_read")));