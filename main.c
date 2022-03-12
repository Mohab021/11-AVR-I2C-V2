
// This program for Slave

#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "AVR_Ports.h"
#include "AVR_LCD_Declarations.h"
#include "AVR_I2C_Declarations.h"

int main(void)
{
	uint8_t x;
	
	LCD_Initialize();
	TWI_Slave_Initialize(0x20);
	
	_delay_ms(10);
	LCD_Print("SLAVE: ");
	_delay_ms(10);
	
	while(1)
	{
		TWI_Slave_Match_ACK(); //keep checking TWI Bus until address from Master is matched, then Read data in the next line
		_delay_ms(10);
		x = TWI_Slave_Read_Data(); //This line never executed until the upper match_ack line is done first 
		LCD_Out(x);
		_delay_ms(10);
	}
}
