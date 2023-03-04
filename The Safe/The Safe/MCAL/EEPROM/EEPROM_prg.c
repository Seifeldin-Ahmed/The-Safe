/*
 * EEPROM_prg.c
 *
 * Created: 07/10/2022 6:57:02 PM
 *  Author: Dell
 */ 

#include "../../LIB/STD_Types.h"
#include "EEPROM_prv.h"
#include "EEPROM_int.h"



EEPROM_tenuErrorStatus EEPROM_enuWriteData(u16 Copy_u16Address , u8 Copy_u8Data)
{
	EEPROM_tenuErrorStatus Local_enuErrorStatus = EEPROM_OK;
	
	if( Copy_u8Data > 255)
	{
		Local_enuErrorStatus = EEPROM_NOK;
	}
	else 
	{
	
		// Set up Address Register 
		EEPROM_u16_EEARL_REG = Copy_u16Address;
		
		// Set Up Data Register
		EEPROM_u8_EEDR_REG = Copy_u8Data ; 
		
		// Write one to the EEMWE
		EEPROM_u8_EECR_REG |= (1<<2);
		
		// Start EEPROM Write by Setting EEWE to 1 
		EEPROM_u8_EECR_REG |= (1<<1);
		
		// Polling on the flag (wait for the write operation to be completed )
			while((EEPROM_u8_EECR_REG >> 1 & 1) == 1);
	}
	return Local_enuErrorStatus;
}

u8 EEPROM_u8ReadeData(u16 Copy_u16Address)
{

				// Set up Address Register
				EEPROM_u16_EEARL_REG = Copy_u16Address;
				
				// Start EEPROM Read by Setting EERE to 1
				EEPROM_u8_EECR_REG |= (1<<0);
				
				// Reading Operation takes only one cycle so it's not neccessry to polling on the flag
				return EEPROM_u8_EEDR_REG;
	
}