#include "Arduino.h"
#include "ShiftRegister17x7.h"


// constructor
ShiftRegister17x7::ShiftRegister17x7(int numberOfShiftRegisters, int serialDataPin, int clockPin, int latchPin)
{
    // set attributes
    _numberOfShiftRegisters = numberOfShiftRegisters;
	int _numberOfRows = 7;
    
    _clockPin = clockPin;
    _serialDataPin = serialDataPin;
    _latchPin = latchPin;
    
    // define pins as outputs
    pinMode(clockPin, OUTPUT);
    pinMode(serialDataPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    
    // set pins low
    digitalWrite(clockPin, LOW);
    digitalWrite(serialDataPin, LOW);
    digitalWrite(latchPin, LOW);
    
    // allocates the specified number of bytes and initializes them to zero
    byte _digitalValues[7][3] = {};
	/*	
	(byte *)malloc(numberOfShiftRegisters * sizeof(byte) * _numberOfRows);
    memset(_digitalValues, 0, numberOfShiftRegisters * sizeof(byte) * _numberOfRows);
	*/
    displayAll(); // reset shift register
}

void ShiftRegister17x7::setAll(byte digitalValues[7][3]) {
	for ( int i=0; i<7; i++) {
		for ( int byte = _numberOfShiftRegisters - 1; byte >= 0; byte--) {
				_digitalValues[i][byte] = digitalValues[i][byte]; 
		}
    }
}

void ShiftRegister17x7::displayAll() {
	for ( int i=0; i<35; i++) { //lets 5 iterations for each row in order to let the led 100% lighting
		for ( int byte = _numberOfShiftRegisters - 1; byte >= 0; byte--) {
				shiftOut(_serialDataPin, _clockPin, LSBFIRST, ~_digitalValues[i/5][byte]);
		}
		digitalWrite(_latchPin, HIGH);
		digitalWrite(_latchPin, LOW); 
    }
}

void ShiftRegister17x7::setRow(byte * digitalValues) {

	for ( int byte = _numberOfShiftRegisters - 1; byte >= 0; byte--) {
			shiftOut(_serialDataPin, _clockPin, LSBFIRST, ~digitalValues[byte]);
	}
	for (int i=0; i<7; i++) {
		for ( int j = _numberOfShiftRegisters - 1; j >= 0; j--) {
			_digitalValues[i][j] = digitalValues[j]; 
		}
	}
	digitalWrite(_latchPin, HIGH);
	digitalWrite(_latchPin, LOW); 
}

void ShiftRegister17x7::setAllLow() {
    byte value[3] ={ B11111110, B00000000, B00000000 };
    setRow(value); 
}

void ShiftRegister17x7::setAllHigh() {
	byte value[3] = { B00000001, B11111111, B11111111 };
    setRow(value); 
}

void ShiftRegister17x7::SerialDigitalValues() {

	Serial.println("------------");
	for ( int i=0; i<7; i++) { 
		Serial.print(_digitalValues[i][0],BIN); 
		Serial.print(' '); 
		Serial.print(_digitalValues[i][1],BIN); 
		Serial.print(' '); 
		Serial.print(_digitalValues[i][2],BIN); 
		Serial.println(); 
	}
}

// byte GetRowByte() returns the selected bit in a byte
bool ShiftRegister17x7::GetBit( byte N, int pos)  { 
  // pos = 7 6 5 4 3 2 1 0
  int b = N >> pos ;         // Shift bits
  b = b & 1 ;                // coger solo el ultimo bit
  return b ;
}

// byte GetRowByte() returns the selected bit in a byte
byte ShiftRegister17x7::SetByte( bool n[8]) {   
  	byte N = B00000000;
	for (int i=0; i<=8; i++ )
    {
	  	N |= (n[i] << i);
    }
  return N;
}

// byte GetRowByte() returns the first byte for a row
// int row (values from 0 to 6)
byte ShiftRegister17x7::GetRowByte( int row ) {
      // BIN  1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000
      // DEC  0, 1 , 2  , 3   , 4    , 5     , 6      , 7       , 8
      int pot = 0.5 + pow(2,row+1);
      byte pos = (B11111110^pot);
	  return pos;
}