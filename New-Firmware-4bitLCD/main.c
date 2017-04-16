/*
	This example should run on most AVRs with only little changes. No special
	hardware resources except INT0 are used. You may have to change usbconfig.h for
	different I/O pins for USB. Please note that USB D+ must be the INT0 pin, or
	at least be connected to INT0 as well.
*/
#include "main.h"
#include "lcd.c" 
#include "led.c"
//#include "keyboard.c"
#include "usb.c"
#include "beep.c"
#include "init.c"
#include "uart.c"
#include "keypad.c"

/* ------------------------------------------------------------------------- */
ISR (TIMER0_OVF_vect){						// timer0 overflow interrupt
	uchar   i;
	static uchar fcount = 0;
		
	TCNT0 = 22;  						// event to be exicuted every 5ms here
	
	if (fcmode == 1){						//Freq mode ON
		if(!--fcount){
			fcount = 200;
			//freq = TCNT1H * 256 + TCNT1L;
			freq = TCNT1;
			TCNT1 = 0;
			kfreq = freq/1000;
			//TCNT1H = 0;
			//TCNT1L = 0;
		}
	}
	
    
	for(i=0;i<10;i++){
		if(timer[i]>0)timer[i]--;           
	}    
}
//
ISR (TIMER1_OVF_vect){						// timer0 overflow interrupt
	//TCNT1 = t1cnt;              
	//PORTC = PORTC ^ 0x40;					//PC6 接 BEEP   腳位更改點  
}
ISR(INT1_vect){
	if(fcmode == 0){							//Cycle mode ON
		cycletmp = TCNT1;
		TCNT1 = 0;
	}
}
 
int main(void){	
	uchar temp1,c = 'a';
	System_init();
	printi("\n\rAtmega8A Started.\n\r",0);
	printi("Atmega8A UART debug console at 115200 bps initialization successful.\n\r",0);
	show_logo1();
	show_logo2();
	GICR = 1<<INT1;					// Enable INT1
	MCUCR = 1<<ISC11 | 1<<ISC10;	// Trigger INT1 on rising edge
	for(;;){          						/* main event loop */   
		wdt_reset();
		usbPoll();
		if (kbhit()){
			temp1=USARTReadChar();
			USARTWriteChar(temp1);
			if (temp1 =='f'){
				if(!fcauto){
					TCCR1B = 0x06;						//Freq Ext Clock
					fcmode = 1;							//Freq mode ON
					printi("\n\r Freq = %d",kfreq);
					printi(".%d KHz \n\r",freq%1000);
				}else{
					printi("\n\rError: fcauto is on, please type 'a' to disable it.\n\r",0);
				}
			}
			if (temp1 =='c'){
				if(!fcauto){
					TCCR1B = 0x02;						//Cycle Ext INT1
					fcmode = 0;							//Cycle mode ON
					printi("\n\r Cycle = %d us\n\r",cycle);
				}else{
					printi("\n\rError: fcauto is on, please type 'a' to disable it.\n\r",0);
				}
			}
			if (temp1 =='a'){
				if(fcauto){
					printi("\n\rfcauto: OFF!\n\r",0);
					fcauto = 0;
				}else if(!fcauto){
					printi("\n\rfcauto: ON!\n\r",0);
					fcauto = 1;
				}
			}
			if (temp1 =='t'){
				printi("\n\r My c Hex is = %x ", c);
				printi("\n\r My c HeX is = %X ", c);
				printi("\n\r My c Dec is = %d ", c);
				printi("\n\r My c Chr is = %c \n\r", c);
			}
			/*if (temp1 =='v'){
				printi("\n\r Voltage = %d ", voltage);
			}*/
			if ( temp1 == CR ) USARTWriteChar( LF );
			DISP_Chr(LINE1+1,temp1);
			DISP_Hex(0x8A,temp1);
		}
		
		if(timer[0] ==0){					//5ms x 6 = 30ms, 鍵盤掃描時間
			timer[0] = 6;    
			//scan_value = keyboard_scan();         
			//if(scan_value < 18)process_keyin(scan_value); 
			key = GetKeyPressed();
			if ( key ) {
				printi("\n\r key Received!",0);			//key to UART
				putchar( key+0x30 );
				DISP_Hex(0x8A,key);
			}
		}   	  
		if(timer[1] ==0){					//5ms x 200 = 1s 上數
			timer[1] = 200; 			 
			if (fcauto){
				if(autocount == 5){
					if(!fcmode){
						fcmode = 1;
					}else{
						fcmode = 0;
					}
					autocount = 0;
				}else{
					++autocount;
				}
			}
			if(disp_mode == 0 && !bKeybusy ){
				DISP_Str(0x80,"105");                                       
				DISP_Str(0xC0,"NHSSC");
				DISP_Str(0x89,"ST:15");
				show_logo1();    	            	
			}else if(disp_mode == 1  && !bKeybusy ){
				DISP_Str(0x88,"WELCOME ");         	
				show_logo1();
				DISP_Chr(0xCA, 0x30 | (station_number/100));
				i = station_number % 100;
				DISP_Chr(0xCB, 0x30 | (i/10));
				DISP_Chr(0xCC, 0x30 | (i%10));
			}
			DISP_Str(LINE1,"       ");
			if(fcmode == 1){
				TCCR1B = 0x06;						//Freq Ext Clock
				DISP_Int(LINE1-6,kfreq);
				DISP_Str(LINE1+2,".");
				DISP_Int(LINE1-2,freq%1000);
				DISP_Str(LINE1+6,"KHz");
			}else if (fcmode == 0){
				TCCR1B = 0x02;						//Cycle Ext INT1
				cycle = (cycletmp/3)<<1;
				DISP_Int(LINE1-2,cycle);
				DISP_Str(LINE1+6,"us");
			}
			voltage = measure_supply();
			printi("\n\r Voltage = %d ", voltage);
			
			Job_Clock();
				XOR_RUNLED; //problem
		}  
		

		if(timer[2] ==0){					//5ms x 100 = 0.5s 上數 
			timer[2] = 100; 	     	
			if(online == 1){ 
				online = 0;
				cmd = INdata[1];
				if (cmd == 1 ){
					Set_Clock(INdata[5],INdata[6],INdata[7]);
					printi("Clock Received!\n\r",0);
					CmdOut = 1;
				}else if(cmd == 2){
					CmdOut = 2;
					printi("Clock Transfered!\n\r",0);
				}
			}	
		}
	}
	return 0;
}


/* ------------------------------------------------------------------------- */

void init_timer(void){
	//timer0
	TIMSK |= (1 << TOIE0);					// TIMER0設定
	TCCR0 |= (1 << CS02);					// set prescaler to 256 and start the timer 
	TCNT0 = 22; 	

	//timer1  ext T1
	//TCCR1B |= (1 << CS10);					// set prescaler to No prescaling
	
	
	//TCNT1 = 0;
}
void trans_number(void){
	if (key == 1) realnumber = 1;
	if (key == 2) realnumber = 2;
	if (key == 3) realnumber = 3;
	if (key == 7) realnumber = 4;
	if (key == 8) realnumber = 5;
	if (key == 9) realnumber = 6;
	if (key == 13) realnumber = 7;
}

void vbmode(void){
   
}

/* Begin of Clock*/
void Job_Clock(void){
	DISP_Str(0xc6,":");	//顯示冒號
	DISP_Str(0xc3,":");	//顯示冒號
	if (++count >= 1){ 						//0.5s*2 = 1s
		count = 0;
		if (++sec >= 60){ 						//60s = 1m
			sec = 0;
			if (++min >= 60){ 					//60m = 1h
				min = 0;
				if (++hour >= 24)hour = 0;		//24h = 1day (但不顯示天數)
			}
		}
	}
	if (sec < 10)DISP_Str(LINE2+7,"0");		//如果秒數小於10擇十位數多放個0
	if (min < 10)DISP_Str(LINE2+4,"0");		//如果分數小於10擇十位數多放個0
	if (hour < 10)DISP_Str(LINE2+1,"0");		//如果時數小於10擇十位數多放個0
	DISP_Dec(LINE2+8,sec);						//顯示秒
	DISP_Dec(LINE2+5,min);						//顯示分
	DISP_Dec(LINE2+2,hour);						//顯示時
}

void Set_Clock(uchar shour, uchar smin, uchar ssec){
	hour = shour;
	min = smin;
	sec = ssec;
	DISP_Dec(LINE1+8,ssec);						//顯示秒
	DISP_Dec(LINE1+5,smin);						//顯示分
	DISP_Dec(LINE1+2,shour);					//顯示時
}

/* End of Clock*/

uint16_t measure_supply(void) {
	ADMUX &= ~(ADMUX_REFMASK | ADMUX_ADCMASK);
	ADMUX |= ADMUX_REF_VBG;      // select AVCC as reference
	ADMUX |= ADMUX_ADC_VBG;       // measure bandgap reference voltage
	ADCSRA |= (1 << ADSC);        // start conversion
	return (ADC);
	//return (1100UL*1023/ADC);     // AVcc = Vbg/ADC*1023 = 1.1V*1023/ADC 
	//return ((ADC << 1) + (ADC >> 1));
	//test 123
}
