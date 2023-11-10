#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include "eeprom.h"
#include "ProjectDefines.h"

uint8_t Read_EEprom_Byte(uint16_t EEProm_Address)
{
	uint8_t EEprom_Value_In_Byte = eeprom_read_byte((EEpromConstBytePointer)EEProm_Address);
	
	return (EEprom_Value_In_Byte);
}

uint16_t Read_EEprom_Word(uint16_t EEProm_Address)
{
	uint16_t EEprom_Value_In_Word = eeprom_read_word((EEpromConstWordPointer)EEProm_Address);
	
	return (EEprom_Value_In_Word);
}

void EEprom_Write_Byte(uint16_t EEProm_Address, uint8_t EEprom_Value)
{
	eeprom_write_byte((EEpromBytePointer)EEProm_Address, EEprom_Value);
}

void EEprom_Write_Word(uint16_t EEProm_Address, uint16_t EEprom_Value)
{
	eeprom_write_word((EEpromWordPointer)EEProm_Address, EEprom_Value);
}

void EEprom_Read_Block(char *Ram_Pointer, uint16_t EEProm_Address, uint8_t NumberOfBytes)
{
	eeprom_read_block(Ram_Pointer, (const void *) EEProm_Address, NumberOfBytes);
}

void EEprom_Read_String(char *Ram_Pointer, uint16_t EEProm_Address)
{
	uint8_t EEprom_Value_In_Byte;
	uint16_t NumberOfBytes = 0;
	
	while ( ((EEprom_Value_In_Byte = Read_EEprom_Byte(EEProm_Address)) != '\0') && (NumberOfBytes < Max_Number_Of_Characters_In_String) )
	{
        *Ram_Pointer++ = EEprom_Value_In_Byte;
		EEProm_Address++;
		NumberOfBytes++;
	}
	*Ram_Pointer = 0;
}