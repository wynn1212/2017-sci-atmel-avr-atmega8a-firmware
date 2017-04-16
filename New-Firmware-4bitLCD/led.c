void process_show(void){
	volatile uint16_t
	loop_cnt = LED_NUM * 3;				// Loop counter = 8(led number) * 3
	volatile uint8_t
	*ptr = pixels,						// Pointer to next byte2
	b_data   = *ptr++,					// Current byte2 value
	hi,									// PORT w/output bit set high
	lo;									// PORT w/output bit set low
	volatile uint8_t next;

	cli();
	hi   = PORTD |  0x01;				//腳位更改點 
	lo   = PORTD & ~0x01;				//腳位更改點 

	next = lo;
	if(b_data & 0x80) next = hi;
	asm volatile(						//1T ~= 83.3ns  ,21 instruction clocks per bit: HHHHxxxxxxxxxxxxLLLLL
		"headD:"					"\n\t"	//        (T =  0)
		"out   %[port], %[hi]"		"\n\t"	//        (T =  1)
		"rcall bitTimeD"			"\n\t"	// 3      Bit 7  (T = 15)
		"out   %[port], %[hi]"		"\n\t"
		"rcall bitTimeD"			"\n\t" // Bit 6
		"out   %[port], %[hi]"		"\n\t"
		"rcall bitTimeD"			"\n\t" // Bit 5
		"out   %[port], %[hi]"		"\n\t"
		"rcall bitTimeD"			"\n\t" // Bit 4
		"out   %[port], %[hi]"		"\n\t"
		"rcall bitTimeD"			"\n\t" // Bit 3
		"out   %[port], %[hi]"		"\n\t"
		"rcall bitTimeD"			"\n\t" // Bit 2
		"out   %[port], %[hi]"		"\n\t"
		"rcall bitTimeD"			"\n\t" // Bit 1
		// Bit 0:
		"out  %[port] , %[hi]"		"\n\t" // 1    PORT = hi    (T =  1)
		"rjmp .+0"					"\n\t" // 2    nop nop      (T =  3)
		"ld   %[byte2] , %a[ptr]+" 	"\n\t" // 2    b = *ptr++   (T =  5)
		"out  %[port] , %[next]"	"\n\t" // 1    PORT = next  (T =  6)
		"nop"						"\n\t" // 1                 (T =  7)  +   
		"nop"						"\n\t" // 1                 (T =  8)  +   
		"nop"						"\n\t" // 1                 (T =  9)  +         
		"nop"						"\n\t" // 1                 (T = 10)  +               
		"nop"						"\n\t" // 1                 (T = 11)  +                     
		"nop"						"\n\t" // 1                 (T = 12)  +     
		"mov  %[next] , %[lo]"		"\n\t" // 1    next = lo    (T = 13)
		"sbrc %[byte2] , 7"			"\n\t" // 1-2  if(b & 0x80) (T = 14)
		"mov %[next] , %[hi]"		"\n\t" // 0-1    next = hi  (T = 15)
		"nop"						"\n\t" // 1                 (T = 16)
		"out  %[port] , %[lo]"		"\n\t" // 1    PORT = lo    (T = 17)
		"sbiw %[count], 1"			"\n\t" // 2    i--          (T = 19)
		"brne headD"				"\n\t" // 2    if(i != 0) -> (next byte2)(T = 21)
		"rjmp doneD"				"\n\t"
		"bitTimeD:"					"\n\t" //                      (T =  4)
		"out  %[port], %[next]"		"\n\t" // 1    PORT = next     (T =  5)    
		"nop"						"\n\t" // 1                    (T =  6)    
		"nop"						"\n\t" // 1                    (T =  7)     
		"nop"						"\n\t" // 1                    (T =  8)           
		"nop"						"\n\t" // 1                    (T =  9)                 
		"nop"						"\n\t" // 1                    (T = 10)                       
		"nop"						"\n\t" // 1                    (T = 11)                 
		"mov  %[next], %[lo]"		"\n\t" // 1    next = lo       (T = 12)    
		"rol  %[byte2]"				"\n\t" // 1    b <<= 1         (T = 13)    
		"sbrc %[byte2], 7"			"\n\t" // 1-2  if(b & 0x80)    (T = 14)    
		"mov %[next], %[hi]"		"\n\t" // 0-1   next = hi      (T = 15)
		"nop"						"\n\t" // 1                    (T = 16)
		"out  %[port], %[lo]"		"\n\t" // 1    PORT = lo       (T = 17)
		"ret"						"\n\t" // 4    nop nop nop nop (T = 18-21)
		"doneD:"					"\n"
		:[byte2]"+r"(b_data),
		[next]	"+r"(next),
		[count]	"+w"(loop_cnt)
		:[port]	"I"(_SFR_IO_ADDR(PORTD)),	//腳位更改點 
		[ptr]	"e"(ptr),
		[hi]	"r" (hi),
		[lo]	"r" (lo)
    );
    sei();    
}

void setPixelColor( uchar number, uchar color_r, uchar color_g, uchar color_b){
	uchar *p;  
	if(number < LED_NUM){
		p = &pixels[number * 3];
		p[0] = color_r;
		p[1] = color_g;
		p[2] = color_b;
	}
}

void rgbled(uchar r,uchar g,uchar b){
	setPixelColor(0,r,g,b);
	process_show();
	R = (r*2)-1;
	G = (g*2)-1;
	B = (b*2)-1;
}

