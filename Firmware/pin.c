void pininit(void){
	if (EEPROM_read(10) == 0xff){
			EEPROM_write(10,0);
			EEPROM_write(0,0x30);
			EEPROM_write(1,0x30);
			EEPROM_write(2,0x30);
			EEPROM_write(3,0x30);
			EEPROM_write(4,0x30);
			wdt_reset();
			lcdclear();
	}
}

void cleanpin(void){
	for(i=0;i<pinlen;i++)EEPROM_write(0xff,i);
	lcdclear();
	DISP_Str(LINE1,"PIN Cleared!");
	_delay_ms(100);
}

char strcmptrue(unsigned char *str1, unsigned char *str2, unsigned char len){
	char rc = 1;
	for(i=0;i<len;i++){
		if(str1[i] != str2[i]) rc = 0;
	}
	return rc;
}

void keyinput(unsigned char *str, unsigned char len, unsigned char ch, unsigned char mode){
	unsigned char i;
	static char j = 0;
	if(!mode){							//Backspace
		for(i=1; i<len;i++){
			str[i] = str[i-1];
		}
		str[0] = 0xff;
		--pin_input_len;
		DISP_Chr(LINE2+pin_input_len,' ');
		
	} else if(mode == 2) {
		if (j > pinlen-1){
			j = 0;
		} else {
			EEPROM_write(j,ch);
			++j;
		}
	} else {							//Input
		for(i=1; i<len; i++){
			str[i-1] = str[i];
		}
		str[len-1] = ch;
		for(i=0;i<len;i++)DISP_Chr(LINE1+11+i,str[i]);
		DISP_Chr(LINE2+pin_input_len,'*');
		++pin_input_len;
	}
}

void pin_daemon(char ch){
	if(!B_mainmenu){
		if(ch){
			if(ch !='*' && ch != '#' && ch != '/'){
				keyinput(&PINTemp[0], pinlen, ch, 1);
			}
			if(ch == '*'){
				keyinput(&PINTemp[0], pinlen, ch, 0);
			}
			if(ch == '#'){
				okbutton();
			}
		}
	}
}

void enterpin(void){
	B_enterpin = 1;
	B_mainmenu = 0;
	lcdclear();
	DISP_Str(LINE1,"Enter PIN:");
}


void okbutton(void){
	if(B_enterpin){
		for(i=0;i<pinlen;i++)PINRead[i] = EEPROM_read(i);
		if( strcmptrue(&PINTemp[0],&PINRead[0],pinlen)){
			B_pinok = 1;
			DISP_Str(LINE2,"Welcome User!");
		} else {
			DISP_Str(LINE2,"WRONG PIN");
		}
	B_enterpin = 0;
	B_mainmenu = 1;
	pin_input_len = 0;
	for(i=0;i<pinlen;i++)PINTemp[i] = 0;
	}
}