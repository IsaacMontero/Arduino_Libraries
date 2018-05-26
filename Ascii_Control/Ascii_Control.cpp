#include "Arduino.h"
#include "Ascii_Control.h"

// Retrieve the font data from the lookup tables. We have had to split the lookups 
// into 3 separate tables because of the PIC's addressing limitations. The tables 
// are split as follows: Font1[][] contains fonts for char codes 0x20 to 0x3f 
//                       Font2[][] contains fonts for char codes 0x40 to 0x5f 
//                       Font3[][] contains fonts for char codes 0x50 to 0x7f 
// 
// The valid display chars are 0x20 (Space) to 0x7f (DEL). Any chars 
// outside of this range are simply ignored. 

Ascii_Control::Ascii_Control(){
}
   
byte * Ascii_Control::LoadFont(int Ccode) 
   {
   
	int Ftab;
	byte *cdata;
   // Check if code between 0x20 and 0x3f inclusive. 
   if(Ccode >= 0x20 && Ccode < 0x40) { 
      Ftab = 0;			// use Font1 array 
	  Ccode -= 0x20;      // normalise the ASCII code 
      } 
   else if(Ccode >= 0x40 && Ccode < 0x60) { 
      Ftab = 1;			// use Font2 array 
	  Ccode -= 0x40;      // normalise the ASCII code 
      } 
   else if(Ccode >= 0x60 && Ccode < 0x80) { 
      Ftab = 2; 
	  Ccode -= 0x60;      // normalise the ASCII code 
      } 

   // Now that we have normalized the codes, we can proceed to load up the 
   // display array. This is done based on the colour of the display. 
	
	if(Ftab == 0) cdata = Font1[Ccode]; 
    else if(Ftab == 1) cdata = Font2[Ccode]; 
    else if(Ftab == 2) cdata = Font3[Ccode]; 
	/*
		DEBUG MODE
		
		byte *p = Font2[Ccode];
		  for (int fil = 0; fil <7 ; fil++)
		  {
			byte F = p[fil] ;
			for (int col =8; col >= 0 ; col--)
			{
				bool b;
				int c = F >> col ;
				b = c & 1 ;
			  
			  Serial.print(b);
			  Serial.print(",");
			}
			Serial.println();
		  }
		  Serial.println("----------------------");
		  delay(5000);
	*/
	
	return cdata;

   }

