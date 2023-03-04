/*
 * EEPROM_prv.h
 *
 * Created: 07/10/2022 6:57:58 PM
 *  Author: Dell
 */ 


#ifndef EEPROM_PRV_H_
#define EEPROM_PRV_H_


#define EEPROM_u8_EEDR_REG      (*(volatile u8*)0x3D)  // Data Register

#define EEPROM_u8_EECR_REG      (*(volatile u8*)0x3C)  // Control Register

#define EEPROM_u16_EEARL_REG    (*(volatile u16*)0x3E)       // Address Register


#endif /* EEPROM_PRV_H_ */