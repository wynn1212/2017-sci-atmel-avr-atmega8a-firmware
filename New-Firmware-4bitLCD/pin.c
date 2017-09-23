void pininit(void){
	if (EEPROM_read(0) == 0xff && 
		EEPROM_read(1) == 0xff && 
		EEPROM_read(2) == 0xff && 
		EEPROM_read(3) == 0xff){
			DISP_Str(LINE1,"First Time Use.");
			DISP_Str(LINE2,"Setting Up...");

			for(i=0;i<4;i++) EEPROM_write(i,i+0x31); 
			EEPROM_write(10,0);
			wdt_reset();
			_delay_ms(500);
			lcdclear();
	}
}

void pinfunc_loop(void){
	if (uptry >2){
		updatefailed();
		B_newpin = 0;
		B_changepin = 0;
		uptry = 0;
	}
	if (B_changepin){
		changepin();
	} else if (B_newpin) {
		newpin();
	} else if (B_confirmpin) {	
		confirmpin();
	} else {
		enterpin();
	}
	if (okbutton){
		static char try = 0;
		try = EEPROM_read(10);
		okbutton = 0;
		if(B_changepin){
			if(pincheck()){
				clearpin();
				B_newpin = 1;
				B_changepin = 0;
				try = 0;
				EEPROM_write(10,try);
				lcdclear();
			} else if( !pincheck() && try < 3){
				++try;
				EEPROM_write(10,try);
				clearpin();
				wrongpin();
			}
		} else if(B_newpin){
			clearpin();
			B_newpin = 0;
			B_confirmpin = 1;
		} else if(B_confirmpin){
			if(PINnew[0] == 0 || PINnew[1] == 0 || PINnew[2] == 0 || PINnew[3] == 0 ){
				uptry++;
				weakpin();
				clearpin();
				B_newpin = 1;
				B_confirmpin = 0;
			} else if ( !Comp2Array( &PINnew[0] , &PINconfirm[0]) ) {
				uptry++;
				differentpin();
				clearpin();
				B_newpin = 1;
				B_confirmpin = 0;					
			} else {
				updatepin();
				clearpin();
				uptry = 0;
				B_confirmpin = 0;
			}
		} else {
			if(pincheck()){
				clearpin();
				correctpin();
				try = 0;
				EEPROM_write(10,try);
			} else if( !pincheck() && try < 3){
				++try;
				EEPROM_write(10,try);
				clearpin();
				wrongpin();
			}
		}
	}
}

void keyjob(char ch){
	if ( ch ) {
		if (ch !='*' && ch != '#' && ch != '/'){
			if(B_newpin){
				PINnew[0] = PINnew[1];
				PINnew[1] = PINnew[2];
				PINnew[2] = PINnew[3];
				PINnew[3] = ch;
//				for(i=0;i<4;i++)printi("%c",PINnew[i]);
//				printi("\n\r",0);
				if(pininput < 4){
					DISP_Chr(LINE1+8+pininput,'*');
					++pininput;
				}
			} else if(B_confirmpin){
				PINconfirm[0] = PINconfirm[1];
				PINconfirm[1] = PINconfirm[2];
				PINconfirm[2] = PINconfirm[3];
				PINconfirm[3] = ch;
//				for(i=0;i<4;i++)printi("%c",PINconfirm[i]);
//				printi("\n\r",0);
				if(pininput < 4){
					DISP_Chr(LINE2+12+pininput,'*');
					++pininput;
				}
			} else {
				PINTemp[0] = PINTemp[1];
				PINTemp[1] = PINTemp[2];
				PINTemp[2] = PINTemp[3];
				PINTemp[3] = ch;
				if(pininput < 4){ 
					if(B_changepin){
						DISP_Chr(LINE2+12+pininput,'*');
					} else {
						DISP_Chr(LINE1+10+pininput,'*');
					}
				++pininput;
				}
			}
		
		} else if (ch == '*' && pininput > 0){
			if(B_newpin){
				PINnew[3] = PINnew[2];
				PINnew[2] = PINnew[1];
				PINnew[1] = PINnew[0];
				PINnew[0] = 0;
				//for(i=0;i<4;i++)printi("%c",PINnew[i]);
				//printi("\n\r",0);
				--pininput;
				DISP_Chr(LINE1+8+pininput,' ');
			} else if (B_confirmpin){
				PINconfirm[3] = PINconfirm[2];
				PINconfirm[2] = PINconfirm[1];
				PINconfirm[1] = PINconfirm[0];
				PINconfirm[0] = 0;
				//for(i=0;i<4;i++)printi("%c",PINconfirm[i]);
				//printi("\n\r",0);
				--pininput;
				DISP_Chr(LINE2+12+pininput,' ');
			} else {
				PINTemp[3] = PINTemp[2];
				PINTemp[2] = PINTemp[1];
				PINTemp[1] = PINTemp[0];
				PINTemp[0] = 0;
				--pininput;
			}
			if(B_changepin){
				DISP_Chr(LINE2+12+pininput,' ');
			} else if(!B_confirmpin && !B_newpin) {
				DISP_Chr(LINE1+10+pininput,' ');
			}
		} else if (ch == '#'){
			okbutton = 1;
		} else if (ch == '/' && !B_changepin && !B_newpin && !B_confirmpin){
			lcdclear();
			clearpin();
			B_changepin = 1;
		}
	}
}

void check_unauth_flag(void){
	if (EEPROM_read(10) >= 3){		//So call try > 3
		lcdclear();
		unauthorizeuser();
		lcdclear();
		B_changepin = 0;
		EEPROM_write(10,0);		//Reset try to 0
	}
	
}

void enterpin(void){
	DISP_Str(LINE1,"Enter PIN:");
	DISP_Str(LINE2," !SYSTEM READY! ");
}

void correctpin(void){
	DISP_Str(LINE2,"!Greeting, User!");
	_delay_ms(100);
	sb(1000);
	_delay_ms(50);
	sb(2000);
	wait_2s();
	DISP_Str(LINE2,"                ");
}

void wrongpin(void){
	DISP_Str(LINE2,"  !WRONG  PIN!  ");
	sb(2000);
	_delay_ms(50);
	sb(2000);
	_delay_ms(50);
	sb(2000);
	wait_2s();
	DISP_Str(LINE2,"                ");
}

void clearpin(void){
	if(B_changepin){
		for (i=0;i<4;i++){
			DISP_Chr(LINE2+12+i,' ');
			PINTemp[i] = 0;
			pininput=0;
		}
	} else if(B_newpin){
		//for (i=0;i<4;i++)PINnew[i]=0;
		pininput=0;
	} else if(B_confirmpin){
		for (i=0;i<4;i++)PINnew[i]=0;
		for (i=0;i<4;i++)PINconfirm[i]=0;
		pininput=0;
	} else {
		for (i=0;i<4;i++){
			DISP_Chr(LINE1+10+i,' ');
			PINTemp[i] = 0;
			pininput=0;
		}
	}
}

void changepin(void){
	DISP_Str(LINE1,"Change PIN");
	DISP_Str(LINE2,"Current PIN:");
}

void newpin(void){
	DISP_Str(LINE1,"New PIN:");
}

void confirmpin(void){
	DISP_Str(LINE2,"Confirm PIN:");
}

void station(void){
	DISP_Str(LINE2+3,"Station:01");
}

void weakpin(void){
	DISP_Str(LINE1,"!Update  FAILED!");
	DISP_Str(LINE2,"  PIN too weak  ");
	wait_2s();
	lcdclear();
}

void differentpin(void){
	DISP_Str(LINE1,"!Update  FAILED!");
	DISP_Str(LINE2," Different PIN. ");
	wait_2s();
	lcdclear();
}

void updatepin(void){
	lcdclear();
	DISP_Str(LINE1,"Updating PIN...");
	DISP_Str(LINE2,"Please Wait...");
	for(i=0;i<4;i++)EEPROM_write(i,PINconfirm[i]);
	wdt_reset();
	_delay_ms(200);
	DISP_Str(LINE1,"!Update SUCCEED!");
	DISP_Str(LINE2,"Returning  Home.");
	wait_2s();
	lcdclear();
}

void updatefailed(void){
	DISP_Str(LINE1,"!Change  FAILED!");
	DISP_Str(LINE2,"Returning  Home.");
	wait_2s();
	lcdclear();
}

void unauthorizeuser(void){
	lcdclear();
	DISP_Str(LINE1," !UNAUTH  USER! ");
	DISP_Str(LINE2," !Locking    s! ");
	for(i=60; i>0; i--){
		sb(3000);
		DISP_Dec(LINE2+12,i);
		if (i<10) DISP_Str(LINE2+11," ");
		wdt_reset();
		_delay_ms(500);
		wdt_reset();
		_delay_ms(500);
	}
}

char pincheck(void){
	char rc = 1;
	if (EEPROM_read(0) != PINTemp[0] ) rc = 0;
	if (EEPROM_read(1) != PINTemp[1] ) rc = 0; 
	if (EEPROM_read(2) != PINTemp[2] ) rc = 0;
	if (EEPROM_read(3) != PINTemp[3] ) rc = 0;
	return rc;
}

void wait_2s(void){
	char i = 50;
	while ( i ) {
		wdt_reset();
		if(timer[8] ==0){					
			timer[8] = 8;
			usbPoll();
			--i;
		}
	}
}