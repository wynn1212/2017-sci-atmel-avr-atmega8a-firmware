/*
	This example should run on most AVRs with only little changes. No special
	hardware resources except INT0 are used. You may have to change usbconfig.h for
	different I/O pins for USB. Please note that USB D+ must be the INT0 pin, or
	at least be connected to INT0 as well.
*/
#include "main.h"
#include "iopin.c"
#include "lcd.c" 	//#include "led.c"
#include "usb.c"
#include "beep.c"
#include "init.c"	//#include "uart.c"
#include "keypad.c"
#include "eeprom.c"
#include "pin.c"


/* ------------------------------------------------------------------------- */
ISR (TIMER0_OVF_vect){		// timer0 overflow interrupt
	uchar   i; 
	
	TCNT0 = 22;  			// event to be exicuted every 5ms here
	for(i=0;i<10;i++){
		if(timer[i]>0)timer[i]--;           
	}    
}

ISR(INT1_vect){   }
//
ISR (TIMER1_OVF_vect){						// timer0 overflow interrupt
	TCNT1 = t1cnt;
	digitalWrite(6,0xff);		//PD1 接 BEEP   腳位更改點 
}
 
int main(void){	
	uchar ch;

	System_init();	
	lcdclear();
	pininit();
	show_logo1();
	show_logo2();
	for(;;){          						/* main event loop */   
		wdt_reset();
		//usbPoll();
		//digitalWrite(1,0xff);				//??????????????????
		if(timer[0] ==0){					//5ms x 6 = 30ms, 鍵盤掃描時間
			timer[0] = 6;
			//DISP_Dec(LINE1+5,online);
			usbPoll();			
		}
		if(timer[1] ==0){					//5ms x 200 = 1s 上數
			timer[1] = 200; 				//200 for normal, 20 for test
			//++autocount;
			check_unauth_flag();
			if(disp_mode == 0 && !bKeybusy ){
				DISP_Str(0x80,"106   ");                                       
				DISP_Str(0xC0,"NHSSC ");
				DISP_Str(0x89,"ST:34");
				show_logo1();    	            	
			}else if(disp_mode == 1  && !bKeybusy ){
				DISP_Str(0x88,"WELCOME ");         	
				show_logo1();
				DISP_Chr(0xCA, 0x30 | (station_number/100));
				i = station_number % 100;
				DISP_Chr(0xCB, 0x30 | (i/10));
				DISP_Chr(0xCC, 0x30 | (i%10));
			}
		}  		
		if(timer[2] ==0){					//5ms x 100 = 0.5s 上數 
			timer[2] = 100; 	     	
			if(online == 1){ 
				online = 0;
				cmd = INdata[1];
				if (cmd == 1 ){
					cleanpin();
					CmdOut = 1;
				}else if(cmd == 2){
					CmdOut = 2;
				}
			}	
		}
		if(timer[3] == 0) {
			timer[3] = 30;	//150mS			
			//pinfunc_loop();
			ch = GetKeyPressed();  //********************************************************
			digitalWrite(19,0xff);
			
			//DISP_Hex(LINE1,digitalRead3());
			//DISP_Hex(LINE1+12,ch);
			//PORTC |= 0x38;
			//PORTD |= 0x10;
			if ( ch ){
				//keyjob( ch );
				if (ch == '1'){
					sb(200);
					DISP_Str(LINE2+11,"1  ");
				}
				if (ch == '2'){
					sb(300);
					DISP_Str(LINE2+11,"2  ");
				}
				if (ch == '3'){
					sb(400);
					DISP_Str(LINE2+11,"3  ");
				}
				if (ch == 'a'){
					sb(200);
					DISP_Str(LINE2+11,"1+2");
				}
				if (ch == 'b'){
					sb(200);
					DISP_Str(LINE2+11,"1+3");
				}
				if (ch == '4'){
					sb(500);
					DISP_Str(LINE2+11,"4  ");
				}
				if (ch == '5'){
					sb(600);
					DISP_Str(LINE2+11,"5  ");
				}
				if (ch == '6'){
					sb(700);
					DISP_Str(LINE2+11,"6  ");
				}
				if (ch == 'c'){
					sb(500);
					DISP_Str(LINE2+11,"4+5");
				}
				if (ch == 'd'){
					sb(500);
					DISP_Str(LINE2+11,"4+6");
				}
				if (ch == '7'){
					sb(800);
					DISP_Str(LINE2+11,"7  ");
				}
				if (ch == '8'){
					sb(900);
					DISP_Str(LINE2+11,"8  ");
				}
				if (ch == '9'){
					sb(1000);
					DISP_Str(LINE2+11,"9  ");
				}
				if (ch == 'e'){
					sb(800);
					DISP_Str(LINE2+11,"7+8");
				}
				if (ch == 'f'){
					sb(800);
					DISP_Str(LINE2+11,"7+9");
				}
				if (ch == '*'){
					sb(1100);
					DISP_Str(LINE2+11,"*  ");
				}
				if (ch == '0'){
					sb(1200);
					DISP_Str(LINE2+11,"0  ");
				}
				if (ch == '#'){
					sb(1300);
					DISP_Str(LINE2+11,"#  ");
				}
				if (ch == 'g'){
					sb(1100);
					DISP_Str(LINE2+11,"*+0");
				}
				if (ch == '/'){
					sb(1100);
					DISP_Str(LINE2+11,"*+#");
				}
				//sb(1000);
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
	TCCR1B |= (1 << CS10);					// set prescaler to No prescaling
	TCNT1 = 0;
}

void vbmode(void){
}


