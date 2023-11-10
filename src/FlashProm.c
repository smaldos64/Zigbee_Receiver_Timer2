#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include "ProjectDefines.h"
#include "FlashProm.h"
#include "Eeprom.h"

const char StateMachineReceivingAddressString[] PROGMEM = "\n\nIndtast Adresse (Maks 4 cifre) i Hex : 0x";
const char StateMachineReceivingBitPositionString[] PROGMEM = "\nIndtast bit position (0 - 7) : ";
const char StateMachineReceiveBitValueString[] PROGMEM = "\nIndtast bit værdi (0 - 1) : ";
const char StateMachineConvertReceivedCharacters[] PROGMEM = "\nIndtast en streng, hvor bogstaver konverteres (afslut med 0) !!! : ";
const char StateMachineUnknownStateString[] PROGMEM = "\nUkendt State maskine tilstand !!!";
const char StateMachineWriteFunnyText[] PROGMEM = "\nIndtast karakteren : for udskrift af sjov tekst !!! : ";

uint16_t strlen_FlashProm(const char *FlashProm_Address)
{
	uint16_t FlashPromStringAddress;
	uint16_t NumberOfBytes = 0;
	uint8_t FlashProm_Value_In_Byte;
		
	//FlashPromStringAddress = pgm_read_word((uint16_t)FlashProm_Address);
	FlashPromStringAddress = (uint16_t)FlashProm_Address;
		
	while ( ((FlashProm_Value_In_Byte = pgm_read_byte(FlashPromStringAddress)) != 0) && (NumberOfBytes < Max_Number_Of_Characters_In_String) )
	{
		NumberOfBytes++;
		FlashPromStringAddress++;
	}
		
	return (NumberOfBytes + 1);
}

uint16_t strlen_FlashProm_EEprom(const char *FlashProm_Address)
{
	uint16_t EEpromStringAddress;
	uint16_t NumberOfBytes = 0;
	uint8_t EEprom_Value_In_Byte;
	
	EEpromStringAddress = pgm_read_word((uint16_t)FlashProm_Address);
	
	while ( ((EEprom_Value_In_Byte = eeprom_read_byte((const uint8_t *)EEpromStringAddress)) != 0) && (NumberOfBytes < Max_Number_Of_Characters_In_String) )
	{
		NumberOfBytes++;
		EEpromStringAddress++;
	}
	
	return (NumberOfBytes + 1);
}

void strcpy_FlashProm(char *RAM_Malloc_Pointer, const char *FlashProm_Address)
{
	strcpy_P(RAM_Malloc_Pointer, (PGM_P)pgm_read_word(FlashProm_Address));
}

void strcpy_FlashProm_EEprom(char *RAM_Malloc_Pointer, const char *FlashProm_Address)
{
	uint16_t EEpromStringAddress;
	
	EEpromStringAddress = pgm_read_word((uint16_t)FlashProm_Address);
	
	EEprom_Read_String(RAM_Malloc_Pointer, EEpromStringAddress);
}

void memcpy_FlashProm(char *RAM_Malloc_Pointer, const char *FlashProm_Address, uint16_t NumberOfBytes)
{
	memcpy_P(RAM_Malloc_Pointer, FlashProm_Address, NumberOfBytes);
}