void lb(int f){
	t1cnt = 65536-(6000000/f);                              
	TIMSK |= (1 << TOIE1); 
}
void sb(int f){
	t1cnt = 65536-(6000000/f);                              
	TIMSK |= (1 << TOIE1); 
	_delay_ms(500);
	PORTC = PORTC & ~0x08;                              //BEEP����   �}�����I 
	TIMSK &= ~(1 << TOIE1); 
}
void cb(void){
	PORTC = PORTC & ~0x08;                              //BEEP����   �}�����I 
	TIMSK &= ~(1 << TOIE1);    
}
