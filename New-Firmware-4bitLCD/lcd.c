//LCD模組函式適用於文字型LCD
//lcd.h
#include <util/delay.h> 					/* for _delay_ms() */

/*   =======  硬體接腳的定義  =============  */
#define RS 7  
#define E 5
#define dT 30

void LCD_E( char b );
void LCD_RW( char b );
void LCD_RS( char b );
void LCD_CMD(char ch);
void LCD_COM(char cmd );
//const char BITLEN = 8;						//4-bit mode 
const uchar picture1[6][8] ={	{0x1F,0x10,0x10,0x10,0x11,0x12,0x14,0x18},
								{0x1F,0x04,0x0A,0x11,0x00,0x04,0x0A,0x11}, 
								{0x1F,0x01,0x01,0x01,0x11,0x09,0x05,0x03},                              	                            
								{0x11,0x12,0x14,0x1F,0x00,0x00,0x03,0x1F}, 
								{0x00,0x00,0x00,0x1F,0x0E,0x0E,0x1F,0x1F},                                                           
								{0x11,0x09,0x05,0x1F,0x00,0x00,0x18,0x1F}, 
                                } ;

const uchar picture2[6][8] ={	{0x1F,0x10,0x10,0x10,0x10,0x10,0x10,0x10},                                                            
								{0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00},                              
								{0x1F,0x01,0x01,0x01,0x01,0x01,0x01,0x01},                                                                                                                                                      
								{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1F},
								{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F},                                                                                                                        
								{0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x1F},                                                                                                                                                                                    
								} ;

void Init_LCD( void ){						// LCD 初始化函式
	char ch = 0x38;		//8BIT
	cli();
	//if ( BITLEN==4 ) ch = 0x28;
	_delay_ms(dT);						// 等待 LCD 電源開啟完成
	LCD_CMD(ch);		//
	_delay_ms(dT);
	LCD_CMD(ch);		// 
	_delay_ms(dT);
	LCD_CMD(ch);		// 
	_delay_ms(dT);
	LCD_CMD(0x08);
	_delay_ms(dT);
	LCD_CMD(0x01);
	_delay_ms(dT);
	LCD_CMD(0x06);
	_delay_ms(dT);
	LCD_CMD(0x0C);
	_delay_ms(dT);
	LCD_CMD(0x80);
	_delay_ms(dT);
	sei();
	//init_LCD_CGRAM();
} 

uchar LCD_BUSY(void){						/* 0 for Ready */
	_delay_us(dT);                    		// 一個短時間的延遲時序   
	return 0;  
}
void LCD_CMD(char ch){						// 寫入指令暫存器函式
	LCD_RS(0);								//RS = 	0
	LCD_COM( ch );
}

void LCD_DATA(char ch) {					// 寫入資料暫存器函式
	LCD_RS(1);								//RS = 1
	LCD_COM( ch );
}
void LCD_COM(char cmd ) {	
	//LCD_RW(0);								//RW = 0
    while (LCD_BUSY()); 
	digitalWrite8(cmd);	
	_delay_us( dT );						// 一個短時間的延遲時序	
	LCD_E(1);								//E  = 1		
	_delay_us( dT );						// 一個短時間的延遲時序	
	LCD_E(0);								//E  = 0	
}
void DISP_Str(char addr1,char *str) {		// 在LCD指定位置顯示字串函式
	LCD_CMD(addr1);							// 設定DD RAM位址第一行第一列
	while(*str !=0) LCD_DATA(*str++);		// 呼叫顯示字串函式
}

void DISP_Chr(char col,char chrx) {			// 在LCD指定位置顯示字元函式 
	LCD_CMD(col);         
	LCD_DATA(chrx);	                    
}

void DISP_Dec(char col,char bytex) {		// 在LCD指定位置顯示字元函式 
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

void DISP_Int(char addr1,long v1) {			// 在LCD指定位置顯示字元函式  
	char i;
	for (i=0;i<7;i++){
		LCD_CMD(addr1-i+7);
		LCD_DATA((v1%10)+0x30);
		v1/=10;
		if(v1==0)
		break;
	}
}

void DISP_Hex(char addr1,unsigned char v1) {// 在LCD指定位置顯示字元函式
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
   lcd_set_char1();							/* 自行定義字型 */		 
   
   DISP_Chr(0x86, 0);	
   DISP_Chr(0x87, 1);	           
   DISP_Chr(0x88, 2);	              
   
   DISP_Chr(0xC6, 3);
   DISP_Chr(0xC7, 4);
   DISP_Chr(0xC8, 5);
}

void show_logo2(void) {
   lcd_set_char2();							/* 自行定義字型 */
   	 
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

void process_show_station(void) {			//顯示站別
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

void lcdclear2(void) {   
	DISP_Str(0xC0,"                "); 
}

void lcdclear1(void) {
	DISP_Str(0x80,"                ");
}
	
void LCD_E( char b ) {      	//LCD Enabler 
	if ( b ) digitalWrite(E,1);//PORTD |= 0x08;     	//PD3 = 1 
	if ( !b ) digitalWrite(E,0);//PORTD &= ~0x08;    	//PD3 = 0 
	_delay_us(3);
	//if ( b ) PORTD |= 0x20;     	//PD5 = 1 
	//if ( !b ) PORTD &= ~0x20;    	//PD5 = 0 
} 

void LCD_RS( char b ) { 
 if ( b ) digitalWrite(RS,1);//PORTD |= 0x01;     	//PD0
 if ( !b ) digitalWrite(RS,0);//PORTD &= ~0x01;    	// 
 //if ( b ) PORTD |= 0x02;     	//
 //if ( !b ) PORTD &= ~0x02;    // 
} 

void LCD_RW( char b ) { 
	b=0;
	//if ( b ) PORTD |= 0x08; 
	//if ( !b ) PORTD &= ~0x08; 
}