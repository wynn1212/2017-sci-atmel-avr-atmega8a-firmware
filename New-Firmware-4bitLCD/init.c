void System_init(void){
	uchar   i;	
	wdt_enable(WDTO_1S);
	/* Even if you don't use the watchdog, turn it off here. On newer devices,
	 * the status of the watchdog (on/off, period) is PRESERVED OVER RESET!
	 */
	 
	/* IO SETUP */   //腳位更改點 
	{
	/*	DDR* 1=Output 0=Input
						//   DDB7   DDB6   DDB5   DDB4   DDB3   DDB2   DDB1   DDB0
		DDRB = 0x3f;    //    0      0      1      1      1      1      1      1
						//    x      x     out    out    out    out    out    out
						//  PORTB7 PORTB6 PORTB5 PORTB4 PORTB3 PORTB2 PORTB1 PORTB0
		PORTB = 0x04;   //    0      0      0      0      0      0      0      0
  
	 
						//   -     DDC6   DDC5   DDC4   DDC3   DDC2   DDC1   DDC0
		DDRC = 0x47;    //    0      1     0      0      0     1      1       1  
						//(Read)    out    in     in     in    out    out    out
						//    -    PORTC6 PORTC5 PORTC4 PORTC3 PORTC2 PORTC1 PORTC0							 
		PORTC = 0x07;   //    0      0      0      0      0      0      0      0
  
						//   DDD7   DDD6   DDD5   DDD4   DDD3   DDD2   DDD1   DDD0
		DDRD = 0xeb;    //    1      1      1      0      1      0      1      1 
						//   out    out    out     D-    out     D+     out    out
						//  PORTD7 PORTD6 PORTD5 PORTD4 PORTD3 PORTD2 PORTD1 PORTD0
		PORTD = 0x0;    //    0      0      0      0      0      0      0      0  	*/
		/*DDRB = 0x33;    //    0      0      1      1      0      0      1      1   @@@@@@@@@@@@@@@@@@
		PORTB = 0x00;   //    0      0      0      0      0      0      0      0
		DDRC = 0x5F;    //    0      1      0      1      1      1      1      1  
		PORTC = 0x0D;   //    0      0      0      0      1      1      0      1
		DDRD = 0xEA;    //    1      1      1      0      1      0      1      0 
		PORTD = 0x0;    //    0      0      0      0      0      0      0      0
		*/
		// ---------------------------------------------------------
						//   DDB7   DDB6   DDB5   DDB4   DDB3   DDB2   DDB1   DDB0
		DDRB = 0x3F;    //    0      0      1      1      1      1      1      1
						//    x      x     out    out    out    out    out    out
						// ---------------------------------------------------------
						//  PORTB7 PORTB6 PORTB5 PORTB4 PORTB3 PORTB2 PORTB1 PORTB0
		PORTB = 0x0;    //    0      0      0      0      0      0      0      0
						// ---------------------------------------------------------

						// ---------------------------------------------------------
						//    -     DDC6   DDC5   DDC4   DDC3   DDC2   DDC1   DDC0
		DDRC = 0x47;    //    0      1      0      0      0      1      1      1  
						//  (Read)  out    in     in     in     out    out    out							 
						// ---------------------------------------------------------
						//    -    PORTC6 PORTC5 PORTC4 PORTC3 PORTC2 PORTC1 PORTC0							 
		PORTC = 0x7F;   //    0      1      1      1      1      1      1      1
						// ---------------------------------------------------------

						// ---------------------------------------------------------
						//   DDD7   DDD6   DDD5   DDD4   DDD3   DDD2   DDD1   DDD0
		DDRD = 0xEB;    //    1      1      1      0      1      0      1      1    
						//   out    out    out    D-     out    D+     out    out
						// ---------------------------------------------------------
						//  PORTD7 PORTD6 PORTD5 PORTD4 PORTD3 PORTD2 PORTD1 PORTD0
		PORTD = 0x0;    //    0      0      0      0      0      0      0      0  
						// ---------------------------------------------------------
		UCSRA = 0x22;   // For more information, Please refer ATmega8A datasheet
		//TCCR1B = 0x06;
   }
		
	usbInit();
	usbDeviceDisconnect();  /* enforce re-enumeration, do this while interrupts are disabled! */
	i = 0;
	while(--i){              /* fake USB disconnect for > 250 ms */            
		wdt_reset();
		_delay_ms(1);
	}
	usbDeviceConnect();
	sei();
	Init_LCD();                        /* LCD初始設定 */ 
	init_timer();
	//USARTInit(12);    //USART Initialization 115200bps UBRR = 12 http://wormfood.net/avrbaudcalc.php
	/* 變數初始設定 */ 
	ADMUX = (1 << REFS1) | (1 << REFS0) | (0 << ADLAR) | (0 << MUX3) | (1 << MUX2) | (0 << MUX1) | (1 << MUX0);
	ADCSRA = (1 << ADEN) | (0 << ADSC) | (1 << ADFR) | (0 << ADPS2)|(0 << ADPS1)|(0 << ADPS0);  
	ADCSRA |= (1 << ADSC);         // start dummy conversion
	scan_line = 0;          //0-2   
	station_number = 105;    
	count2 = 0;
	logo_flag  = 0;
	scan_last = 0xff;
	disp_mode = 0;
	hh = 0; mm = 0; ss = 0, online = 0;
	key = 0;
	flag_close = 0;
	   
	DISP_Str(LINE1,"                ");      //初始顯示                 
	DISP_Str(LINE2,"                ");      
		 
	for(i=0;i<10;i++) timer[i] = 0;     
}