
#include <avr/pgmspace.h>

typedef void (*Function_Pointer)(char *);

#define StateMachineSeperatorCharacter ','

#define Max_Number_Of_Characters_In_String 256

typedef enum
{
	STATE_MACHINE_RECEIVING_ADDRESS,
	STATE_MACHINE_RECEIVING_BIT_POSITION,
	STATE_MACHINE_RECEIVING_BIT_VALUE,
	// STATE_MACHINE_CONVERT_RECEIVED_CHARACTERS,
	// STATE_MACHINE_WRITE_FUNNY_TEXT,
	STATE_MACHINE_UNKNOWN_STATE
} StateMachineStates;

typedef enum
{
  ERROR_WRONG_CHARACTER_TYPED,
  ERRROR_WRONG_ADDRESS,
  ERROR_WRONG_BIT_POSITION,
  ERROR_WRONG_BIT_VALUE
} ErrorStates;

typedef struct
{
	StateMachineStates WorkingState;
	Function_Pointer ThisFunctionPointer;
	PGM_P ptrToFlashStatusString;
} StateMachineStruct;

#define MaxCharactersInAddressString 4

typedef struct  
{
	uint16_t Address;
	char Address_String[MaxCharactersInAddressString + 1];
	uint8_t Address_StringPointer; 
	
	uint8_t Bit_Position;
	
	uint8_t Bit_State;
} AddressStruct;

#define Upper_Lower_Bit_Position 5
#define Upper_Lower_Bit_Value (1 << Upper_Lower_Bit_Position)

#define Write_Funny_Text_Character ':'