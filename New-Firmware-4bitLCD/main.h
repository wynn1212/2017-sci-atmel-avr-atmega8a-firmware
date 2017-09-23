// Initialization require header files.
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>  /* for sei() */
#include <util/delay.h>     /* for _delay_ms() */
#include <avr/eeprom.h>
#include <avr/pgmspace.h>   /* required by usbdrv.h */
#include "usbdrv/usbdrv.c"
#include "usbdrv/oddebug.c"        /* This is also an example for using debug macros */
#define LED_NUM  1
#define INPUT  0
#define OUTPUT 1
#define HIGH 1
#define LOW  0
#define  byte unsigned char

uchar pixels[3];
uchar GetKeyPressed( void );

/* Begin of Define Port Direction */
#define XOR_RUNLED PORTC ^= 0x08
/* End of Define Port Direction */

/* Begin of uart.c */
#include <avr/io.h>
#include <inttypes.h>
#define putchar USARTWriteChar
#define CR 0x0D
#define LF 0x0A
#define ESC 0x1B
void printi(char *str, unsigned int iVal);
char USARTReadChar( void );
void USARTInit(uint16_t ubrr_value);
char kbhit(void);
unsigned char EEPROM_read(unsigned int uiAddress);
void EEPROM_write(unsigned int uiAddress, unsigned char ucData);
#define Baudrate 26		//26uS = 38400
#define BIT1 0x02
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
char B_usbflag =1;
char strE[32];
/* End of Clock */

void process_show(void);

/* Begin of 办跑计 */
//uint16_t voltage;
//uchar kfreq;
uchar scan_line, scan_in, scan_value, scan_last,count2;
uchar station_number, key;
uchar disp_mode, logo_flag ,realnumber,vbkey,R,G,B,k1,k2,k3,k4,k5,k6,k7,ct; 
unsigned int timer[10];
                      
uchar hh,mm,ss,online,flag_close,cmd,CmdOut,i,k;
uchar INdata[8];
uchar OUTdata[8];
uchar temp_timer[6];                  //PC
uchar uptry = 0;
unsigned int t1cnt,vbf;
byte  LCDbuff[2][16];		
byte  bLCDref = 0;			//0:no refresh in need,  1:refresh required.
const char HexData[16] = "0123456789ABCDEF";
const char HexDataLow[16] = "0123456789abcdef";
char Comp2Array(unsigned char *ptr1, unsigned char *ptr2);
void System_init(void);
void init_timer(void);
uchar keyboard_scan(void);
void process_keyin(uchar value);
void process_show_station(void);
void show_logo1(void);
void show_logo2(void);
void lb(int f);
void sb(int f);
void cb(void);
void lcdclear(void);
void lcdclear1(void);
void lcdclear2(void);
//void trans_number(void);
void vbmode(void);
unsigned char  PINTemp[5];
unsigned char  PINnew[5];
unsigned char  PINconfirm[5];
void cleanpin(void);
void enterpin(void);
void correctpin(void);
void wrongpin(void);
void changepin(void);
char pincheck(void);
void unauthorizeuser(void);
void clearpin(void);
void newpin(void);
void confirmpin(void);
void weakpin(void);
void differentpin(void);
void updatepin(void);
void updatefailed(void);
void station(void);
static char pininput=0;
void wait_2s(void);
void keyjob(char ch);
void pininit(void);
void check_unauth_flag(void);
void pinfunc_loop(void);
/* End of 办跑计 */

/* Begin of bool */
char fcmode = 1; //(freq=1,cycle=0)
char fcauto = 1;
char autocount = 0;
char okbutton = 0;
char B_changepin;
char B_newpin;
char B_confirmpin;
/* End of bool */
uchar key;

