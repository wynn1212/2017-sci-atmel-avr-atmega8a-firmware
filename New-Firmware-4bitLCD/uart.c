//This function is used to initialize the USART
//at a given UBRR value

#define Baudrate 25		//26uS = 38400
#define BIT3 0x08

char USARTReadChar( void );
void USARTInit(uint16_t ubrr_value){

	//Set Baud rate

	UBRRL = ubrr_value;
	UBRRH = (ubrr_value>>8);

	/*Set Frame Format

	>> Asynchronous mode
	>> No Parity
	>> 1 StopBit

	>> char size 8

	*/

	UCSRC=(1<<URSEL)|(3<<UCSZ0);

	//Enable The receiver and transmitter

	UCSRB=(1<<RXEN)|(1<<TXEN);
}

char kbhit(void){
	return UCSRA & (1<<RXC);
}

//This function is used to read the available data
//from USART. This function will wait untill data is
//available.
char USARTReadChar( void ) {
	//Wait untill a data is available

	//while(!(UCSRA & (1<<RXC))){ //*****WARNING******
		//Do nothing
	//}

	//Now USART has got data from host
	//and is available is buffer

	return UDR;
}

//This fuction writes the given "data" to
//the USART which then transmit it via TX line
void USARTWriteChar(char data){
	//Wait untill the transmitter is ready

	while(!(UCSRA & (1<<UDRE))){
		//Do nothing
	}

	//Now write the data to USART buffer

	UDR=data;
}

//A function similar to printf(); but it's call printuart();
//Because It print messages on Uart

/*void printuart( char *ptr){
	byte i =0, max = 100;
	while( i<max && ptr[i] ) USARTWriteChar(ptr[i++]);
}
void printint(long ptr){
	byte i,j[8],k;
	for (i=1;i<8;++i){
		j[i] = (ptr%10)+0x30;
		ptr/=10;
		//if(ptr==0)break;
	}
	for (k=7;k>0;--k){
		USARTWriteChar(j[k]);
	}
}*/

void putcharJ( unsigned char indata ) {
	cli();
	unsigned char ch, i;
	
	_delay_us( Baudrate );
	PORTD &= ~BIT3;	//Start bit = 0
	_delay_us( Baudrate );
	for ( i=0; i<8; i++ ) {
		ch = indata & 0x01;
		if ( ch ) {	//if ( LSB=1 )
			PORTD |= BIT3;
		} else {
			PORTD &= ~BIT3;
		}
		_delay_us( Baudrate );
		indata >>= 1;
	}
	PORTD |= BIT3;	//Stop bit
	sei();
} 

void printi(char *str, unsigned int iVal){
	uchar i=0;
	unsigned char j,k;
	byte a,b[6],c,b0 = 0; //if b0 == 0 cut leading-zero.
	while ( str[i] && i<100 ){
		if ( str[i] == '%'){
			++i;	//get the next char
			if ( str[i] == 'c' ) putcharJ(iVal);
			if ( str[i] == 'X' ){
				j = iVal / 16 ;
				k = iVal % 16 ;
				putcharJ(HexData[j]);
				putcharJ(HexData[k]);
			}
			if ( str[i] == 'x' ){
				j = iVal / 16 ;
				k = iVal % 16 ;
				putcharJ(HexDataLow[j]);
				putcharJ(HexDataLow[k]);
			}
			if ( str[i] == 'd' ){
				for (a=1;a<6;a++){
					b[a] = (iVal%10)+0x30;
					iVal/=10;
				}
				for (c=5;c>0;c--){
					if ( b[c]!= '0' ) b0 = 1;
					if ( b0 ) putcharJ( b[c] );
				}
			}
		} else {
			putcharJ(str[i]);
		}
		++i;
	}
}