// Initialization require header files.
#include "define.h"
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>  /* for sei() */
#include <util/delay.h>     /* for _delay_ms() */
#include <avr/eeprom.h>
#include <avr/pgmspace.h>   /* required by usbdrv.h */
#include "usbdrv/usbdrv.c"
#include "usbdrv/oddebug.c"        /* This is also an example for using debug macros */


uchar pixels[3];
uchar GetKeyPressed( void );



void process_show(void);

/* Begin of 办跑计 */
//uint16_t voltage;
//uchar kfreq;
char strE[32];
uchar scan_line, scan_in, scan_value, scan_last,count2;
uchar station_number, key;
uchar disp_mode, logo_flag; //,realnumber,vbkey,R,G,B,k1,k2,k3,k4,k5,k6,k7,ct; 
unsigned int timer[10];
uchar bKeybusy = 0;
                      
//uchar hh,mm,ss,online,flag_close,cmd,CmdOut,i,k;
unsigned char online = 0;
unsigned char cmd,CmdOut,flag_close;
uchar INdata[8];
uchar OUTdata[8];
uchar temp_timer[6];                  //PC
unsigned int t1cnt,vbf;
byte  LCDbuff[2][16];		
byte  bLCDref = 0;			//0:no refresh in need,  1:refresh required.
const char HexData[16] = "0123456789ABCDEF";
char Comp2Array(unsigned char *ptr1, unsigned char *ptr2);
void System_init(void);
void init_timer(void);
//uchar keyboard_scan(void);
//void process_keyin(uchar value);
void process_show_station(void);
void show_logo1(void);
void show_logo2(void);
void lb(int f);
void sb(int f);
void cb(void);
void lcdclear(void);
void lcdclear1(void);
void lcdclear2(void);
void keypadmain(char ch);
void job_1s(void);
void job_500ms(void);
//void trans_number(void);
void vbmode(void);
/* PIN.c */
unsigned char  PINTemp[pinlen];
unsigned char  PINRead[pinlen];
//unsigned char  PINnew[pinlen];
//unsigned char  PINconfirm[pinlen];
char strcmptrue(unsigned char *str1, unsigned char *str2, unsigned char len);
void keyinput(unsigned char *str, unsigned char len, unsigned char ch, unsigned char mode);
void station(void);
char pininput=0;
void pininit(void);
void cleanpin(void);
void pin_daemon(char ch);
void enterpin(void);
char pin_input_len = 0;
void okbutton(void);
unsigned char pinwait = 0;
/* PIN.c */
/* End of 办跑计 */

/* Begin of bool */
char fcmode = 1; //(freq=1,cycle=0)
char fcauto = 1;
char autocount = 0;
//char okbutton = 0;
char B_mainmenu = 1;
char B_enterpin = 1;
char B_pinok = 0;
/* End of bool */
uchar key;

