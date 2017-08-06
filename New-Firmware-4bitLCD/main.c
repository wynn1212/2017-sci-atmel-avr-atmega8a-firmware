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
#include "eeprom.c"

char str[32];
/* ------------------------------------------------------------------------- */
ISR (TIMER0_OVF_vect){						// timer0 overflow interrupt
	uchar   i;
		
	TCNT0 = 22;  						// event to be exicuted every 5ms here
	
	for(i=0;i<10;i++){
		if(timer[i]>0)timer[i]--;           
	}    
}

ISR(INT1_vect){

}
	
ISR (TIMER1_OVF_vect){						// timer0 overflow interrupt
	TCNT1 = t1cnt;              
	PORTB ^= 0x02;					//PB1 接 BEEP   腳位更改點  
	//PORTC ^= 0x02;
}

 
int main(void){	
	uchar temp1;
	System_init();
	printi("8\n\rI:Atmega8A OK.\n\r",0);
	printi("I:Atmega8A UART dbgtty at 38400bps .\n\r",0);
	show_logo1();
	show_logo2();
	//GICR = 1<<INT1;					// Enable INT1
	//MCUCR = 1<<ISC11 | 1<<ISC10;	// Trigger INT1 on rising edge
	for(;;){          						/* main event loop */   
		wdt_reset();
		usbPoll();
		/*if (kbhit()){
			temp1=USARTReadChar();
			USARTWriteChar(temp1);
			static int beep=0;
			if (temp1 =='0')TIMSK &= (0 << TOIE1);
			if (temp1 =='z')lb(261);
			if (temp1 =='x')lb(293);
			if (temp1 =='c')lb(329);
			if (temp1 =='v')lb(349);
			if (temp1 =='b')lb(392);
			if (temp1 =='n')lb(440);
			if (temp1 =='m')lb(493);
			if (temp1 ==',')lb(523);
			if (temp1 =='s')lb(277);
			if (temp1 =='d')lb(311);
			if (temp1 =='g')lb(369);
			if (temp1 =='h')lb(415);
			if (temp1 =='j')lb(466);
			if (temp1 =='9')lb(5000);
			if (temp1 =='+'){
				for(i=0;i<=10;i++){
					lb(++beep);
					printi("ToneFreq = %d\n\r",beep);
				}
			}
			if (temp1 =='-'){
				for(i=0;i<=10;i++){
					lb(--beep);
					printi("ToneFreq = %d\n\r",beep);
				}
			}
			if (temp1 =='e'){
				printi("\n\rI:Writing to EEPROM...",0);
				eeprom_string_write("This is a 1st EEPROM data",0);
				eeprom_string_write("2nd",1);
				eeprom_string_write("3rd",2);
				eeprom_string_write("4th",3);
				eeprom_string_write("5th",4);
				printi("Completed.\n\r",0);
			}
			if (temp1 =='r'){
				printi("\n\r Read EE ",0);
				printi("Completed.\n\r",0);
				printi("\n\rEEPROM:",0);
				eeprom_string_read(0);  //--------------------------------------
				printi( &str[0] ,0);
				eeprom_string_read(1);  //--------------------------------------
				printi( &str[32] ,0);
			}
			if ( temp1 == CR ) USARTWriteChar( LF );
		}*/
		
		if(timer[0] ==0){					//5ms x 6 = 30ms, 鍵盤掃描時間
			timer[0] = 6;    
			//scan_value = keyboard_scan();         
			//if(scan_value < 18)process_keyin(scan_value); 
			key = GetKeyPressed();
			if ( key ) {
				//printi("\n\rI:keyed!",0);			//key to UART
				putchar( key+0x30 );
				//DISP_Hex(0x8A,key);
			}
		}   	  
		if(timer[1] ==0){					//5ms x 200 = 1s 上數
			timer[1] = 200; 			 
			printi("8\n\rHello World!\n\r",0);
			if(disp_mode == 0 && !bKeybusy ){
				DISP_Str(0x80,"105   ");                                       
				DISP_Str(0xC0,"NHSSC ");
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
					printi("Clock RX!\n\r",0);
					CmdOut = 1;
				}else if(cmd == 2){
					CmdOut = 2;
					printi("Clock TX\n\r",0);
				}else if(cmd == 3){
					EEPROM_write(INdata[2],0);
					EEPROM_write(INdata[3],1);
					EEPROM_write(INdata[4],2);
					EEPROM_write(INdata[5],3);
					EEPROM_write(INdata[6],4);
					EEPROM_write(INdata[7],5);
					CmdOut = 1;
				}
			}	
		}
		/*if(timer[3] == 0){
			timer[3] = 1;
			PORTC ^= 0x08;
		}*/
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
	TCCR1B |= (1 << CS10);					// set prescaler to No prescaling
	
	
	TCNT1 = 0;
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
	/*DISP_Str(0xc6,":");	//顯示冒號
	DISP_Str(0xc3,":");	//顯示冒號*/
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
	/*if (sec < 10)DISP_Str(LINE2+7,"0");		//如果秒數小於10擇十位數多放個0
	if (min < 10)DISP_Str(LINE2+4,"0");		//如果分數小於10擇十位數多放個0
	if (hour < 10)DISP_Str(LINE2+1,"0");		//如果時數小於10擇十位數多放個0
	DISP_Dec(LINE2+8,sec);						//顯示秒
	DISP_Dec(LINE2+5,min);						//顯示分
	DISP_Dec(LINE2+2,hour);*/						//顯示時
}

void Set_Clock(uchar shour, uchar smin, uchar ssec){
	hour = shour;
	min = smin;
	sec = ssec;
	/*DISP_Dec(LINE1+8,ssec);						//顯示秒
	DISP_Dec(LINE1+5,smin);						//顯示分
	DISP_Dec(LINE1+2,shour);*/					//顯示時
}

/* End of Clock*/

/*uint16_t measure_supply(void) {
	ADMUX &= ~(ADMUX_REFMASK | ADMUX_ADCMASK);
	ADMUX |= ADMUX_REF_VBG;      // select AVCC as reference
	ADMUX |= ADMUX_ADC_VBG;       // measure bandgap reference voltage
	ADCSRA |= (1 << ADSC);        // start conversion
	return (ADC);
	//return (1100UL*1023/ADC);     // AVcc = Vbg/ADC*1023 = 1.1V*1023/ADC 
	//return ((ADC << 1) + (ADC >> 1));
	//test 123
}*/
