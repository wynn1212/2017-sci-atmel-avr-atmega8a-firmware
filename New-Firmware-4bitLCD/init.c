void System_init(void){
	uchar   i;	
	wdt_enable(WDTO_1S);
	/* Even if you don't use the watchdog, turn it off here. On newer devices,
	 * the status of the watchdog (on/off, period) is PRESERVED OVER RESET!	 */	 
	/* IO SETUP */   	//1=Output 0=Input
	DDRB = 0x38;    //
	PORTB = 0x00;   //
	
	DDRC = 0x7F;    // 0111-1111
	PORTC = 0x7F;   //
	
	DDRD = 0xEB;    //0000-1011
	PORTD = 0xF3;   //		
	
	UCSRA = 0x22;   // For more information, Please refer ATmega8A datasheet
	//TCCR1B = 0x06;
		
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
	scan_line = 0;          //0-2   
	station_number = 105;    
	count2 = 0;
	logo_flag  = 0;
	scan_last = 0xff;
	disp_mode = 0;
	online = 0;
	key = 0;
	flag_close = 0;
	
	DISP_Str(0x88,"        ");      //初始顯示                 
	DISP_Str(0xC0,"        ");      
		 
	for(i=0;i<10;i++) timer[i] = 0;     
}