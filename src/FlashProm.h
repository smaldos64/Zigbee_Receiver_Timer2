#ifdef __cplusplus
 extern "C" {
#endif

extern const char StateMachineReceivingAddressString[] PROGMEM;
extern const char StateMachineReceivingBitPositionString[] PROGMEM;
extern const char StateMachineReceiveBitValueString[] PROGMEM;
extern const char StateMachineConvertReceivedCharacters[] PROGMEM;
extern const char StateMachineUnknownStateString[] PROGMEM;
extern const char StateMachineWriteFunnyText[] PROGMEM;

//extern word strlen_FlashProm(word FlashProm_Address);
extern uint16_t strlen_FlashProm(const char *FlashProm_Address);
extern uint16_t strlen_FlashProm_EEprom(const char *FlashProm_Address);
extern void strcpy_FlashProm(char *RAM_Malloc_Pointer, const char *FlashProm_Address);
extern void strcpy_FlashProm_EEprom(char *RAM_Malloc_Pointer, const char *FlashProm_Address);
extern void memcpy_FlashProm(char *RAM_Malloc_Pointer, const char *FlashProm_Address, uint16_t NumberOfBytes);

#ifdef __cplusplus
}
#endif