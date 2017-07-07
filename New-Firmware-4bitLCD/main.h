// Initialization require header files.

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>  /* for sei() */
#include <util/delay.h>     /* for _delay_ms() */
#include <avr/pgmspace.h>   /* required by usbdrv.h */
#include "usbdrv/usbdrv.c"
#include "usbdrv/oddebug.c"        /* This is also an example for using debug macros */
#include <avr/eeprom.h>			/*EEPROM support.*/
#define LED_NUM  1
#define XOR_RUNLED PORTD ^= 0x01
#define  byte unsigned char
#define ADMUX_ADCMASK  ((0 << MUX3)|(1 << MUX2)|(0 << MUX1)|(1 << MUX0))
#define ADMUX_REFMASK  ((1 << REFS1)|(1 << REFS0))
#define ADMUX_REF_AREF ((0 << REFS1)|(0 << REFS0))
#define ADMUX_REF_AVCC ((0 << REFS1)|(1 << REFS0))
#define ADMUX_REF_RESV ((1 << REFS1)|(0 << REFS0))
#define ADMUX_REF_VBG  ((1 << REFS1)|(1 << REFS0))
#define ADMUX_ADC_VBG  ((0 << MUX3)|(1 << MUX2)|(0 << MUX1)|(1 << MUX0))

uchar pixels[3];
uchar GetKeyPressed( void );

/* Begin of uart.c */
#include <avr/io.h>
#include <inttypes.h>
#define putchar USARTWriteChar
#define CR 0x0D
#define LF 0x0A
#define ESC 0x1B
void printuart( char *ptr);
void printint( long ptr);
void printi(char *str, unsigned int iVal);
char USARTReadChar( void );
void USARTInit(uint16_t ubrr_value);
char kbhit(void);
/* End of uart.c */


/* Begin of Clock */
#define LINE2 0xC0
#define LINE1 0x80
void Job_Clock(void);
void Set_Clock(uchar shour, uchar smin, uchar ssec);
char count = -1;
uchar bKeybusy = 0;
uchar sec;
uchar min;
uchar hour;
/* End of Clock */

void process_show(void);

/* Begin of 办跑计 */
uint16_t voltage;
void eeprom_string_read(int record);
unsigned int freq,cycle,cycletmp;
uchar kfreq;
uchar scan_line, scan_in, scan_value, scan_last,count2;
uchar station_number, key;
uchar disp_mode, logo_flag ,realnumber,vbkey,R,G,B,k1,k2,k3,k4,k5,k6,k7,ct; 
unsigned int timer[10];
                      
uchar hh,mm,ss,online,flag_close,cmd,CmdOut,i,k;
uchar INdata[8];
uchar OUTdata[8];
uchar temp_timer[6];                  //PC
unsigned int t1cnt,vbf;
byte  LCDbuff[2][16];		
byte  bLCDref = 0;			//0:no refresh in need,  1:refresh required.
const char HexData[16] = "0123456789ABCDEF";
const char HexDataLow[16] = "0123456789abcdef";
void System_init(void);
void init_timer(void);
uchar keyboard_scan(void);
uint16_t measure_supply(void);
void process_keyin(uchar value);
void process_show_station(void);
void setPixelColor( uchar number, uchar color_r, uchar color_g, uchar color_b);
void show_logo1(void);
void show_logo2(void);
void rgbled(uchar r,uchar g,uchar b);
void lb(int f);
void sb(int f);
void cb(void);
void lcdclear(void);
void trans_number(void);
void vbmode(void);
/* End of 办跑计 */

/* Begin of bool */
char fcmode = 1; //(freq=1,cycle=0)
char fcauto = 1;
char Vauto = 0;
char autocount = 0;
/* End of bool */
uchar key;