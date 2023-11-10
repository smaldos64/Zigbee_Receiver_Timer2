#ifdef __cplusplus
 extern "C" {
#endif

typedef const uint8_t *EEpromConstBytePointer;
typedef const uint16_t *EEpromConstWordPointer;

typedef uint8_t *EEpromBytePointer;
typedef uint16_t *EEpromWordPointer;

extern uint8_t Read_EEprom_Byte(uint16_t EEProm_Address);
extern uint16_t Read_EEprom_Word(uint16_t EEProm_Address);
extern void EEprom_Write_Word(uint16_t EEProm_Address, uint16_t EEprom_Value);
extern void EEprom_Write_Word(uint16_t EEProm_Address, uint16_t EEprom_Value);
extern void EEprom_Read_Block(char *Ram_Pointer, uint16_t EEProm_Address, uint8_t NumberOfBytes);
extern void EEprom_Read_String(char *Ram_Pointer, uint16_t EEProm_Address);

#ifdef __cplusplus
}
#endif