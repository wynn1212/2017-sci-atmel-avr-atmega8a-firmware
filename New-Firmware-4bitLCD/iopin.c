

void digitalWrite( unsigned char, unsigned char );	//pin no, val=0,1,0xFF
void pinMode(unsigned char, unsigned char );			//pin no, 0=input, 1=output
unsigned char digitalRead(unsigned char pin);
unsigned char digitalRead4(void);

//return 0 if LOW, 1 if HIGH
unsigned char digitalRead(unsigned char pin) {	
	char rc = 1 << (pin % 8);	//0-7
	if (pin < 8) rc = PIND & rc; 
	if ((pin > 7) && (pin < 16)) rc = PINB & rc;
	if (pin > 15) rc = PINC & rc;
	if ( rc ) rc = 1;
	return rc;
}

//val=0 for input, 1 for output
void pinMode(unsigned char pin , unsigned char val ) {
	char ch = 1 << (pin % 8);	//0-7
	if ( !val ) {	// clear bit
		if (pin < 8) DDRD &= ch; 
		if ((pin > 7) && (pin < 16)) DDRB &= ch;
		if (pin > 15) DDRC &= ch;
	} else {
		if (pin < 8) DDRD |= ch;
		if ((pin > 7) && (pin < 16)) DDRB |= ch;
		if (pin > 15) DDRC |= ch;
	}
}

// 0=clear bit 0xFF=XOR, 1~254=set bit
void digitalWrite(unsigned char pin, unsigned char val ){
	char ch = 1 << (pin % 8);	//0-7
	if ( !val ) {	// clear bit
		ch = ~ch;
		if (pin < 8) PORTD &= ch; 
		if ((pin > 7) && (pin < 16)) PORTB &= ch;
		if (pin > 15) PORTC &= ch;
	} else {
		if ( val == 0xFF ) {	//XOR
			if (pin < 8) PORTD ^= ch;
			if ((pin > 7) && (pin < 16)) PORTB ^= ch;
			if (pin > 15) PORTC ^= ch;
		} else {
			if (pin < 8) PORTD |= ch;
			if ((pin > 7) && (pin < 16)) PORTB |= ch;
			if (pin > 15) PORTC |= ch;
		} 
	}
}

unsigned char bytepin[8] = {8,9,10,11,16,17,18,19};	//LCD
void digitalWrite8(unsigned char val) {
	unsigned char i,ch;
	for(i=0;i<8;i++){
		ch = val & (1<<i);
		if (ch){
			digitalWrite(bytepin[i],1);
		} else {
			digitalWrite(bytepin[i],0);
		}
	}
}
unsigned char digitpin[4] = {21,20,13,12};	//Keypad
void digitalWrite4( unsigned char val) {
	unsigned char i,ch;
	for(i=0;i<4;i++){
		ch = val & (1<<i);
		if (ch){
			digitalWrite(digitpin[i],1);
		} else {
			digitalWrite(digitpin[i],0);
		}
	}
}

unsigned char readpin[3] = {7,6,5}; //Keypad Read
unsigned char digitalRead3(void){
	unsigned char i,ch=0;
	for(i=0;i<3;i++){
		ch = ch | (digitalRead(readpin[i])<<i);
	}
	return ch;
}