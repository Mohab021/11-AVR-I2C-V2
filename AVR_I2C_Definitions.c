#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "AVR_I2C_Declarations.h"

void TWI_Slave_Initialize(uint8_t Slave_Addr)
{
	TWAR = Slave_Addr; //TWI Address Register
}

void TWI_Slave_Match_ACK()
{
	uint8_t status =0x00;
	/*
	The slave device always needs to listen to the TWI bus
	to check whether it gets addressed by any Master
	When it is addressed, TWINT bit get set
	*/
	
	while( status != (0x60) ) //After getting addressed by the master, check if address matches
	//(if OK, then (ACK is returned and transmitted from Slave to Master)) & break the function (don't go through While again))
	{
		//this to check TWI Bus
		TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWEA); //Enable TWI, clear interrupt flag, Enable ACK generation
		while( !(TWCR & (1<<TWINT)) ) ; //Wait until TWI finish its current Event
		//here, Slave is addressed by the Master

		status = TWSR & (0xF8); //TWI status bits (high 5-bits of TWSR)
	}
}

uint8_t TWI_Slave_Read_Data()
{
	//this to check TWI Bus
	TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWEA); //Enable TWI, clear interrupt flag, Enable ACK generation
	while( !(TWCR & (1<<TWINT)) ) ; //Wait until TWI finish its current Event
	//here, Slave received data from the Master
	
	uint8_t status = TWSR & (0xF8); //TWI status bits (high 5-bits of TWSR)
	while( status != (0x80) ) ; //Wait until Data is received from the Master, ACK is returned and transmitted from Slave to Master
	
	uint8_t Data = TWDR;
	return Data; //Return received Data
}
