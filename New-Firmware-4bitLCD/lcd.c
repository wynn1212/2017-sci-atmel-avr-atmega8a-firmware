//LCD�Ҳը禡�A�Ω��r��LCD
//lcd.h
#include <util/delay.h> 					/* for _delay_ms() */

/*   =======  �w�鱵�}���w�q  =============  */
#define DBPORT PORTC						//PC0~PC3  
#define CTPORT PORTB 
#define E_INDEX  0x01						//bit0
#define RS_INDEX 0x02						//bit1
#define RW_INDEX 0x04						//bit2
#define dT 20

void LCD_CMD(char cmd);
const char BITLEN = 4;						//4-bit mode 
//const char HexData[16] = "0123456789ABCDEF";
const uchar picture1[6][8] ={	{0x1F,0x10,0x17,0x17,0x17,0x17,0x17,0x17},
								{0x1F,0x00,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F}, 
								{0x1F,0x01,0x1D,0x1D,0x1D,0x1D,0x1D,0x1D},                              	                            
								{0x17,0x17,0x17,0x17,0x17,0x17,0x10,0x1F}, 
								{0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x00,0x1F},                                                           
								{0x1D,0x1D,0x1D,0x1D,0x1D,0x1D,0x01,0x1F}, 
                                } ;

const uchar picture2[6][8] ={	{0x1F,0x10,0x10,0x10,0x10,0x10,0x10,0x10},                                                            
								{0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00},                              
								{0x1F,0x01,0x01,0x01,0x01,0x01,0x01,0x01},                                                                                                                                                      
								{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1F},
								{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F},                                                                                                                        
								{0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x1F},                                                                                                                                                                                    
								} ;


 
/*   ==========================     */    
void Init_LCD( void ){						// LCD ��l�ƨ禡
	_delay_ms(30);							// ���� LCD �q���}�ҧ���
	if ( BITLEN==4 ) LCD_CMD(0x28);		//4BIT 
	if ( BITLEN==8 ) LCD_CMD(0x38);		//8BIT 
	LCD_CMD(0x33);
	_delay_ms(10);
	LCD_CMD(0x32);
	_delay_ms(10);
	_delay_ms(1);							//	LCD_CMD(0x0E);
	LCD_CMD(0x0C);
	_delay_ms(1);
	LCD_CMD(0x01);
	_delay_ms(1);
	LCD_CMD(0x06);
	_delay_ms(10);
	LCD_CMD(0x80);							// �]�wDD RAM��}�Ĥ@��Ĥ@�C	
	_delay_ms(10);
} 

uchar LCD_BUSY(void){						/* 0 for Ready */
	_delay_us(dT);                    		// �@�ӵu�ɶ�������ɧ�   
	return 0;  
}
void LCD_CMD(char cmd){						// �g�J���O�Ȧs���禡
    while (LCD_BUSY());
	CTPORT = CTPORT & ~RS_INDEX;			//RS = 0
	_delay_us(dT);							// �@�ӵu�ɶ�������ɧ�		
	CTPORT = CTPORT & ~RW_INDEX;			//RW = 0	
	_delay_us(dT);							// �@�ӵu�ɶ�������ɧ�	

	DBPORT = (cmd>>4) & 0x0F;				//�g�J���O�Ȧs�� bit5-0
	_delay_us( dT );						// �@�ӵu�ɶ�������ɧ�	
	CTPORT = CTPORT |  E_INDEX;				//E  = 1		
	_delay_us( dT );						// �@�ӵu�ɶ�������ɧ�	
	CTPORT = CTPORT & ~E_INDEX;				//E  = 0	
	_delay_us( dT );						// �@�ӵu�ɶ�������ɧ�		
	
	DBPORT = cmd & 0x0F;					//�g�J���O�Ȧs�� bit5-0
	_delay_us( dT );						// �@�ӵu�ɶ�������ɧ�	
	CTPORT = CTPORT |  E_INDEX;				//E  = 1		
	_delay_us( dT );						// �@�ӵu�ɶ�������ɧ�	
	CTPORT = CTPORT & ~E_INDEX;				//E  = 0	
	_delay_us( dT );						// �@�ӵu�ɶ�������ɧ�			
}

void LCD_DATA(char data1) {					// �g�J��ƼȦs���禡
    while (LCD_BUSY());
	CTPORT = CTPORT |  RS_INDEX;			//RS = 1
	_delay_us( dT );						// �@�ӵu�ɶ�������ɧ�		
	CTPORT = CTPORT & ~RW_INDEX;			//RW = 0	
	_delay_us( dT );						// �@�ӵu�ɶ�������ɧ�
	
	DBPORT = (data1>>4) & 0x3F;			//�g�J��� bit5-0
   _delay_us( dT );							// �@�ӵu�ɶ�������ɧ�	     	
	CTPORT = CTPORT |  E_INDEX;				//E  = 1		
	_delay_us( dT );						// �@�ӵu�ɶ�������ɧ�	
	CTPORT = CTPORT & ~E_INDEX;				//E  = 0	
   _delay_us( dT );							// �@�ӵu�ɶ�������ɧ�	

	DBPORT = data1 & 0x0F;					//�g�J��� bit5-0
   _delay_us( dT );							// �@�ӵu�ɶ�������ɧ�	     	
	CTPORT = CTPORT |  E_INDEX;				//E  = 1		
	_delay_us( dT );						// �@�ӵu�ɶ�������ɧ�	
	CTPORT = CTPORT & ~E_INDEX;				//E  = 0	
   _delay_us( dT );							// �@�ӵu�ɶ�������ɧ�		
}

void DISP_Str(char addr1,char *str) {		// �bLCD���w��m��ܦr��禡
	LCD_CMD(addr1);							// �]�wDD RAM��}�Ĥ@��Ĥ@�C
	while(*str !=0) LCD_DATA(*str++);		// �I�s��ܦr��禡
}

void DISP_Chr(char col,char chrx) {			// �bLCD���w��m��ܦr���禡 
	LCD_CMD(col);         
	LCD_DATA(chrx);	                    
}

void DISP_Dec(char col,char bytex) {		// �bLCD���w��m��ܦr���禡 
	LCD_CMD(col);         
	LCD_DATA((bytex%10)+'0');				//'0' = 0x30
	if (bytex > 9){
		LCD_CMD(--col);
		LCD_DATA(((bytex/10)%10)+0x30);	
	}
	if (bytex > 99){
		LCD_CMD(--col);
		LCD_DATA(((bytex/100)%10)+0x30);	
	}
}

void DISP_Int(char addr1,long v1) {			// �bLCD���w��m��ܦr���禡  
	char i;
	for (i=0;i<7;i++){
		LCD_CMD(addr1-i+7);
		LCD_DATA((v1%10)+0x30);
		v1/=10;
		if(v1==0)
		break;
	}
}

void DISP_Hex(char addr1,unsigned char v1) {// �bLCD���w��m��ܦr���禡
   unsigned char i,j;
   i = v1 / 16 ;
   j = v1 % 16 ;
   DISP_Chr(addr1,'0');
   DISP_Chr(addr1 + 1,'x');   
   DISP_Chr(addr1 + 2 ,HexData[i]);
   DISP_Chr(addr1 + 3 ,HexData[j]);
}

void lcd_set_char1(void) {					// address = 0 -7
   uchar i,address;

    for(address=0;address<6;address++) {   
      LCD_CMD( 0x40 | (address*8) );		//set address   
      for(i=0;i<8;i++)         	
	       LCD_DATA(picture1[address][i]);	     
	}
}

void lcd_set_char2(void) {					// address = 0 -7
   uchar i,address;

    for(address=0;address<6;address++) {   
      LCD_CMD( 0x40 | (address*8) );		//set address   
      for(i=0;i<8;i++)         	
	       LCD_DATA(picture2[address][i]);	     
	}
}

void show_logo1(void) {
   lcd_set_char1();							/* �ۦ�w�q�r�� */		 
   
   DISP_Chr(0x86, 0);	
   DISP_Chr(0x87, 1);	           
   DISP_Chr(0x88, 2);	              
   
   DISP_Chr(0xC6, 3);
   DISP_Chr(0xC7, 4);
   DISP_Chr(0xC8, 5);
}

void show_logo2(void) {
   lcd_set_char2();							/* �ۦ�w�q�r�� */
   	 
   DISP_Chr(0x80, 0);	
   DISP_Chr(0x81, 1);
   DISP_Chr(0x82, 1);
   DISP_Chr(0x83, 1);
   DISP_Chr(0x84, 1);
   DISP_Chr(0x85, 1);
   DISP_Chr(0x86, 2);
   DISP_Chr(0xC0, 3);
   DISP_Chr(0xC1, 4);
   DISP_Chr(0xC2, 4);
   DISP_Chr(0xC3, 4);
   DISP_Chr(0xC4, 4);
   DISP_Chr(0xC5, 4);
   DISP_Chr(0xC6, 5);
}

void process_show_station(void) {			//��ܯ��O
	 unsigned char i;
   DISP_Str(0xC0,"Station ");
   i = station_number / 100;
   DISP_Chr(0xC8, 0x30 | i);   
   i = station_number % 100;               
   DISP_Chr(0xC9, 0x30 | (i/10));               
   DISP_Chr(0xCA, 0x30 | (i%10));    
}

void lcdclear(void) {
  DISP_Str(0x80,"                ");   
  DISP_Str(0xC0,"                "); 
}