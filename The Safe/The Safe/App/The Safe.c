/*
 * main.c
 *
 * Created: 22/09/2022 7:53:40 PM
 *  Author: SEIFElDIN AHMED ISMAIL
 */
#define F_CPU 8000000UL
#include <util/delay.h>
#include "../LIB/STD_Types.h"
#include "../HAL/PORT/PORT_int.h"
#include "../MCAL/EEPROM/EEPROM_int.h"
#include "../HAL/LCD/LCD_int.h"
#include "../HAL/Keypad/KEYPAD_int.h"
#define EEPROM_Status_Flag        0x20
#define EEPROM_PASSWORD_LOCATION1 0x21
#define EEPROM_PASSWORD_LOCATION2 0x22
#define EEPROM_PASSWORD_LOCATION3 0x23
#define EEPROM_PASSWORD_LOCATION4 0x24
#define First_Use                 0XFF
#define Entered_The_Safe          0x00
#define Max_Tries                 2
int main(void)
{     
	
  PORT_vidInit();
  LCD_VidInit();
   u8 Local_au8Password[4];
   u8 Local_u8Flag = 0;
   u8 Local_u8ReadPassword=KEYPAD_u8_NOTPRESSED;
   u8 Local_u8Tries = Max_Tries;
   u8 i ;

    if(EEPROM_u8ReadeData(EEPROM_Status_Flag)==First_Use) // to check if its the first time to use the safe
    {
	    LCD_enuSendString("Set Password:");
	    for( i =0; i<=3 ; i++)
	    {
		    
		    do
		    {
			    KEYPAD_enuGetPressedKey(&Local_u8ReadPassword);
			    
		    } while (Local_u8ReadPassword == KEYPAD_u8_NOTPRESSED);
		    
		    LCD_enuGoTo(1,i);
		    LCD_enuSendCharacter(Local_u8ReadPassword);
		    _delay_ms(500);
			 LCD_enuGoTo(1,i);
		    LCD_enuSendCharacter('*');
		    EEPROM_enuWriteData(EEPROM_PASSWORD_LOCATION1+i,Local_u8ReadPassword);
	    }
	    EEPROM_enuWriteData(EEPROM_Status_Flag,Entered_The_Safe); // set the flag to 0
    }
    
    
    while(Local_u8Flag == 0)
    {
	    LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
	    
		Local_u8ReadPassword=KEYPAD_u8_NOTPRESSED;
	    LCD_enuSendString("1- Login");
		LCD_enuGoTo(1,0);
		LCD_enuSendString("2- Reset");
		do
		{
			KEYPAD_enuGetPressedKey(&Local_u8ReadPassword);
			
		} while (Local_u8ReadPassword == KEYPAD_u8_NOTPRESSED);
		_delay_ms(240);
		if(Local_u8ReadPassword == '1')
	   {  
		    LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
			LCD_enuSendString("Check Password:");
	      	   for( i =0 ; i<=3 ; i++)
	      	   {
		      	   do
		      	   {
			      	   KEYPAD_enuGetPressedKey(&Local_au8Password[i]);
		      	   } while (Local_au8Password[i]==KEYPAD_u8_NOTPRESSED);
		    
	           	     LCD_enuGoTo(1,i);
	           	     LCD_enuSendCharacter(Local_au8Password[i]);
					 _delay_ms(500);
					   LCD_enuGoTo(1,i);
	        	    LCD_enuSendCharacter('*');
	             }
	            
	            if((EEPROM_u8ReadeData(EEPROM_PASSWORD_LOCATION1)==Local_au8Password[0]) &&  (EEPROM_u8ReadeData(EEPROM_PASSWORD_LOCATION2)==Local_au8Password[1]) && (EEPROM_u8ReadeData(EEPROM_PASSWORD_LOCATION3)==Local_au8Password[2]) && (EEPROM_u8ReadeData(EEPROM_PASSWORD_LOCATION4)==Local_au8Password[3]) )
	            {
		            LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
		            LCD_enuSendString("Right Password");
		            LCD_enuGoTo(1,0);
		            LCD_enuSendString("Safe Opened");
		            Local_u8Flag=1;
	            }
	            else
	            {
		              Local_u8Tries--;
		       		if(Local_u8Tries>0)
	         	       {   
	       	         	  LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
	       	              LCD_enuSendString("Wrong Password");
	       	              _delay_ms(1000);
	       	              LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
	             	      LCD_enuSendString("Tries Left:");
	             	      LCD_enuSendCharacter(Local_u8Tries+48);
	             	      _delay_ms(1000);
	            	   }
	       	         else
	       	           {
	       		           LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
	       		           LCD_enuSendString("Wrong Password");
	       		           LCD_enuGoTo(1,0);
	       		           LCD_enuSendString("Safe Closed");
	       		           Local_u8Flag=1;
	       	           }			  
	           }
		  }
		  else if(Local_u8ReadPassword == '2')	
		  {
			   LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
			     LCD_enuSendString("old Password:");
				    for( i =0 ; i<=3 ; i++)
				    {
					    do
					    {
						    KEYPAD_enuGetPressedKey(&Local_au8Password[i]);
					    } while (Local_au8Password[i]==KEYPAD_u8_NOTPRESSED);
					    
					    LCD_enuGoTo(1,i);
					    LCD_enuSendCharacter(Local_au8Password[i]);
					    _delay_ms(500);
					    LCD_enuGoTo(1,i);
					    LCD_enuSendCharacter('*');
				    }
				 
				 
				   if((EEPROM_u8ReadeData(EEPROM_PASSWORD_LOCATION1)==Local_au8Password[0]) &&  (EEPROM_u8ReadeData(EEPROM_PASSWORD_LOCATION2)==Local_au8Password[1]) && (EEPROM_u8ReadeData(EEPROM_PASSWORD_LOCATION3)==Local_au8Password[2]) && (EEPROM_u8ReadeData(EEPROM_PASSWORD_LOCATION4)==Local_au8Password[3]) )
				   { 
					    LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
			            LCD_enuSendString("New Password:");
			            for( i =0; i<=3 ; i++)
			            {
			                
			                do
			                {
			           	     KEYPAD_enuGetPressedKey(&Local_u8ReadPassword);
			           	     
			                } while (Local_u8ReadPassword == KEYPAD_u8_NOTPRESSED);
			                
			                LCD_enuGoTo(1,i);
			                LCD_enuSendCharacter(Local_u8ReadPassword);
			                _delay_ms(500);
			                LCD_enuGoTo(1,i);
			                LCD_enuSendCharacter('*');
			                EEPROM_enuWriteData(EEPROM_PASSWORD_LOCATION1+i,Local_u8ReadPassword);
			             }
				 }
				 else
				 {
					  
					  LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
					  LCD_enuSendString("Wrong Password");
					  _delay_ms(1000);
				 }				 
		  }	
		  else 
		  {
			   LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
			   LCD_enuSendString("Wrong Choice");
			   _delay_ms(1000);
		  }			  	   
	    
    }
    
     while(1)
     {        
				 
     }
     
	
	return 0;
}