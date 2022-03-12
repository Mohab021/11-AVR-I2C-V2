
#ifndef AVR_I2C_DECLARATIONS_H_
#define AVR_I2C_DECLARATIONS_H_

void TWI_Slave_Initialize(uint8_t Slave_Addr);
void TWI_Slave_Match_ACK();
uint8_t TWI_Slave_Read_Data();

#endif /* AVR_I2C_DECLARATIONS_H_ */