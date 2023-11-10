#define Display_Attached

#include <Arduino.h>

#include <Ticker.h>

// #include "ProjectDefines.h"
// #include "FlashProm.h"

//#include "SoftwareSerial.h"
#include "avr_debugger.h"
#include "avr8-stub.h"
#include "app_api.h"

#ifdef Display_Attached
//#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET LED_BUILTIN  //4
Adafruit_SSD1306 display(OLED_RESET);

	#if (SSD1306_LCDHEIGHT != 64)
	#error("Height incorrect, please fix Adafruit_SSD1306.h!");
	#endif
#endif

#define USE_SERIAL Serial2

#include <XBee.h>

#define LED 9

static volatile bool Interrupt_Occured = false;
static volatile uint32_t Interrupt_Counter = 0;
//=======================================================================
void changeState()
{
	digitalWrite(LED, !(digitalRead(LED)));  //Invert Current State of LED
	Interrupt_Occured = true;
	Interrupt_Counter++;
}

Ticker Blinker(changeState, 1000);

/*
This example is for Series 2 XBee
Receives a ZB RX packet and sets a PWM value based on packet data.
Error led is flashed if an unexpected packet is received
*/

XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
// create reusable response objects for responses we expect to handle 
ZBRxResponse rx = ZBRxResponse();
ModemStatusResponse msr = ModemStatusResponse();

int statusLed = 13;
int errorLed = 12;
int dataLed = 13;

int my_putc(char c, FILE* t)
{
	USE_SERIAL.write(c);
	return 0;
}

void WriteInitText()
{
	#ifdef Display_Attached
	display.clearDisplay();
	display.setTextSize(1);
	display.setCursor(0, 16);
	display.println("Program Start !!!");
	
	display.setCursor(0, 32);
	display.println("Venter - Zigbee - ko");

	display.setCursor(0, 48);
	display.println("Indtast fra Commu(T)");

	display.display();
#endif
	printf("\nNu er vi klar\n");
}

void WriteText(char *StringToDisplay)
{
#ifdef Display_Attached
	display.clearDisplay();
	display.setTextSize(1);
	display.setCursor(0, 16);
	display.println("Tekst fra Com:");
	
	display.setCursor(0, 32);
	display.println(StringToDisplay);

	display.display();
#endif
	printf("\nNu udskrevet til Display !!!\n");
	printf("Tekst modtaget fra Communicator : ");
	printf(StringToDisplay);
	printf("\n");
}

void flashLed(int pin, int times, int wait) {
    
    for (int i = 0; i < times; i++) {
      digitalWrite(pin, HIGH);
      delay(wait);
      digitalWrite(pin, LOW);
      
      if (i + 1 < times) {
        delay(wait);
      }
    }
}

void setup() {
  USE_SERIAL.begin(115200);
  debug_init();
  delay(3000);

  fdevopen(&my_putc, 0);    // OBS !!! Har omdirigerer vi printf til at bruge UART gennem den angivne funktion : my_putc. 
                            // Det vil sige, at alle printf sætninger vil blive omdirigeret til UART'en.

#ifdef Display_Attached
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display.clearDisplay();
	display.setTextColor(WHITE);
	WriteInitText();
#endif

  pinMode(statusLed, OUTPUT);
  pinMode(errorLed, OUTPUT);
  pinMode(dataLed,  OUTPUT);
  
  // start serial
  Serial.begin(9600);
  xbee.begin(Serial);

  Blinker.start();
  
  //flashLed(statusLed, 3, 50);
}

// continuously reads packets, looking for ZB Receive or Modem Status
void loop() {
  char ErrorCodeArray[3];

  Blinker.update();
	if (Interrupt_Occured)
	{
		Interrupt_Occured = false;
		USE_SERIAL.print("Interrupt Counter : ");
		USE_SERIAL.println(Interrupt_Counter);
	}
    
  xbee.readPacket();
  
  if (xbee.getResponse().isAvailable()) 
  {
    USE_SERIAL.println("1a");
    // got something
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) 
    {
      // got a zb rx packet
      
      // now fill our zb rx class
      xbee.getResponse().getZBRxResponse(rx);
          
      if (rx.getOption() == ZB_PACKET_ACKNOWLEDGED) {
          // the sender got an ACK
          flashLed(statusLed, 10, 10);
      } else 
      {
          // we got it (obviously) but sender didn't get an ACK
          flashLed(errorLed, 2, 20);
      }
      // set dataLed PWM to value of the first byte in the data
      //analogWrite(dataLed, rx.getData(0));  // LTPE
      uint8_t NumberOfBytesReceived = rx.getDataLength();
      char ZigBeeDataArray[NumberOfBytesReceived];
      for (uint8_t Counter = 0; Counter < NumberOfBytesReceived; Counter++)
      {
        ZigBeeDataArray[Counter] = (char)rx.getData(Counter);
      }
      printf("\n");
      printf(ZigBeeDataArray);
      printf("\n");
      WriteText(ZigBeeDataArray);
    } 
    else if (xbee.getResponse().getApiId() == MODEM_STATUS_RESPONSE) 
    {
      xbee.getResponse().getModemStatusResponse(msr);
      // the local XBee sends this response on certain events, like association/dissociation
      
      if (msr.getStatus() == ASSOCIATED) 
      {
        // yay this is great.  flash led
        flashLed(statusLed, 10, 10);
      } else if (msr.getStatus() == DISASSOCIATED)
      {
        // this is awful.. flash led to show our discontent
        flashLed(errorLed, 10, 10);
      } else 
      {
        // another status
        flashLed(statusLed, 5, 10);
      } 
    } 
    else
    {
      // not something we were expecting
      flashLed(errorLed, 1, 25);    
    }
  } else if (xbee.getResponse().isError()) 
  {
    printf("Error reading packet.  Error code: ");  
    uint8_t ErrorCode = xbee.getResponse().getErrorCode();
    sprintf(ErrorCodeArray, "%d", ErrorCode);
    printf(ErrorCodeArray);
    printf("\n");
    //printf(xbee.getResponse().getErrorCode());
  }
}


