/* The following variables store the status of the current data transfer */
static uchar    currentAddress;
static uchar    bytesRemaining;

/* usbFunctionRead() is called when the host requests a chunk of data from
 * the device. For more information see the documentation in usbdrv/usbdrv.h.
 * E.X. PC <= Atmega8
 */
 
 #define BASE 0x30
uchar   usbFunctionRead(uchar *data, uchar len){
	if(len > bytesRemaining)len = bytesRemaining;
	if(currentAddress == 0){
		if ( CmdOut == 1 ) {  //Recived Successful.
			for ( i=0;i<8;i++) OUTdata[i] = 5;
			for ( i=0;i<8;i++) *(data+i) = OUTdata[i];		
		}else if( CmdOut == 2) { //Sent Time
			OUTdata[0] = 5;OUTdata[1] = 1; OUTdata[2] = 0; OUTdata[3] = 0;
			OUTdata[4] = 0;OUTdata[5] = hour; OUTdata[6] = min; OUTdata[7] = sec;
			for ( i=0;i<8;i++) *(data+i) = OUTdata[i];
		}else if( CmdOut == 3){
			for ( i=0;i<8;i++) OUTdata[i] = 1;
			for ( i=0;i<8;i++) *(data+i) = OUTdata[i];
		}
		/*
  
        *(data)   = BASE+0;  	// AD value ,HIGH BYTE                         
 		*(data+1) = BASE+1;		// AD value ,LOW BYTE
 		*(data+2) = BASE+2;		// Reserve (zero)
 		*(data+3) = BASE+3;		// Reserve (zero)
 		*(data+4) = BASE+4;		// Reserve (zero)
 		*(data+5) = BASE+5;		// Reserve (zero)
 		*(data+6) = BASE+6;		// Reserve (zero)
 		*(data+7) = BASE+7;		// Reserve (zero)*/
   }
   currentAddress += len;
   bytesRemaining -= len;
   
   return len;
}

/* usbFunctionWrite() is called when the host sends a chunk of data to the
 * device. For more information see the documentation in usbdrv/usbdrv.h.
 * E.X. PC => Atmega8
 */
uchar   usbFunctionWrite(uchar *data, uchar len){
	//static uchar tempB,tempD;
	if(bytesRemaining == 0)
		return 1;               /* end of transfer */
	if(len > bytesRemaining)
		len = bytesRemaining;
	if(currentAddress == 0){   	
		online = 1;
		for ( i=0; i<8; i++ ) INdata[i] = data[i];
		/*if((*(data+1) & 0x20) == 0x20){
    	
		}else if(*(data+1) == 0x01){    	 
			temp_timer[0] = *(data+2);  //時
			temp_timer[1] = *(data+3);  //
			temp_timer[2] = *(data+4);  //分
			temp_timer[3] = *(data+5);  //
			temp_timer[4] = *(data+6);  //秒
			temp_timer[5] = *(data+7);  //    
			hh = temp_timer[0] * 10 + temp_timer[1];
			mm = temp_timer[2] * 10 + temp_timer[3];
			ss = temp_timer[4] * 10 + temp_timer[5];
			online = 1;                                                                                                                                 		 	     		 
    	}else if(*(data+1) == 0x04){    	 
			vbkey = *(data+2);
			vbf = (*(data+3)) *10 +(*(data+4));
			ct = *(data+5); 
			online = 1;
    	}else if(*(data+1) == 0x05){    	 
			Set_Clock(*(data+5),*(data+6),*(data+7));
			online = 1;
    	}else if(*(data+1) == 0x03){       //程式結束 
			online = 0;   
			flag_close = 1;             		                                                                                                                                     		 	     		     	             	                               		 	     		 
    	}*/    	
	}
   currentAddress += len;
   bytesRemaining -= len;
   return bytesRemaining == 0;	/* return 1 if this was the last chunk */
}

usbMsgLen_t usbFunctionSetup(uchar data[8]){
	usbRequest_t    *rq = (void *)data;
	if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS){    /* HID class request */
		if(rq->bRequest == USBRQ_HID_GET_REPORT){  /* wValue: ReportType (highbyte), ReportID (lowbyte) */
			/* since we have only one report type, we can ignore the report-ID */
			bytesRemaining = 8;
			currentAddress = 0;
			return USB_NO_MSG;  /* use usbFunctionRead() to obtain data */
		}else if(rq->bRequest == USBRQ_HID_SET_REPORT){
			/* since we have only one report type, we can ignore the report-ID */
			bytesRemaining = 8;
			currentAddress = 0;
			return USB_NO_MSG;  /* use usbFunctionWrite() to receive data from host */
		}
	}else{
		/* ignore vendor type requests, we don't use any */
	}
	return 0;
}
/* ----------------------------- USB interface ----------------------------- */
PROGMEM const char usbHidReportDescriptor[22] = {	/* USB report descriptor */
	0x06, 0x00, 0xff,								// USAGE_PAGE (Generic Desktop)
	0x09, 0x01,										// USAGE (Vendor Usage 1)
	0xa1, 0x01,										// COLLECTION (Application)
	0x15, 0x00,										//   LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x00,								//   LOGICAL_MAXIMUM (255)
	0x75, 0x08,										//   REPORT_SIZE (8)
	0x95, 0x80,										//   REPORT_COUNT (128)
	0x09, 0x00,										//   USAGE (Undefined)
	0xb2, 0x02, 0x01,								//   FEATURE (Data,Var,Abs,Buf)
	0xc0											// END_COLLECTION
};
