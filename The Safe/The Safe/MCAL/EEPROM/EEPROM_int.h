/*
 * EEPROM_int.h
 *
 * Created: 07/10/2022 6:56:48 PM
 *  Author: Seif
 */ 


#ifndef EEPROM_INT_H_
#define EEPROM_INT_H_


// Check Error Status 
typedef enum 
{
 	EEPROM_OK,
	 EEPROM_NOK
}EEPROM_tenuErrorStatus;



EEPROM_tenuErrorStatus EEPROM_enuWriteData(u16 Copy_u16Address , u8 Copy_u8Data);

u8 EEPROM_u8ReadeData(u16 Copy_u16Address);
#endif /* EEPROM_INT_H_ */