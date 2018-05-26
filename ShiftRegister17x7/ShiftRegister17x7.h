/*
  ShiftRegister17x7.h - Library for easy control of the 74HC595 shift register.
  Created by Isaac Montero, Jan 2017.
  Additional information are available on http://shiftregister.simsso.de/
  Released into the public domain.
*/

#ifndef ShiftRegister17x7_h
#define ShiftRegister17x7_h

#include "Arduino.h"

class ShiftRegister17x7 
{
public:
    ShiftRegister17x7(int numberOfShiftRegisters, int serialDataPin, int clockPin, int latchPin);
	void setAll(byte digitalValues[7][3]);
    void displayAll();
    void setRow( byte *value );
    void setAllLow();
    void setAllHigh(); 
	void SerialDigitalValues();
	bool GetBit( byte N, int pos);
	byte SetByte( bool n[8]);
	byte GetRowByte( int row );
private:
	int _numberOfRows;
    int _numberOfShiftRegisters;
    int _clockPin;
    int _serialDataPin;
    int _latchPin;
    byte _digitalValues[7][3];
};

#endif
