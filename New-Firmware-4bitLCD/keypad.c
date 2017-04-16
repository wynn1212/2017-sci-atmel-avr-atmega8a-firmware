

char keypadhit(void);
uchar GetKeyPressed( void ){    
	static char pressed = 0;
	uchar r,c, ch, rc = 0;

	//char ch=0; //return
	//temp = PORTB;
	//temp2 = PORTC;
	if ( !pressed ){
		for (r=0; r<4; r++){
			ch = ~(1<<r);
			PORTC = (PORTC | 0x0F) & ch;
			for (c=0; c<4; c++){
				ch = (0x04<<c);
				if(!(PINB & ch)){
					rc = r*4+c+1;
					pressed = 1;
					
				}
			}
		}
	} else {
		//if ((PORTC = (PORTC | 0x0F) & ~(1<<j)) & (PINB & (0x04<<l))) pressed = 0;
		PORTC = PORTC & 0xF0;
		_delay_us( 10 );	
		ch = PINB & 0x3C;
		if ( ch == 0x3C ) pressed = 0;
	}
	//PORTB= temp;
	//PORTC= temp2;

    return rc;//Indicate No key pressed
}

char keypadhit(void){
	return GetKeyPressed();
}
