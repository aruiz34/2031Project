#include "protocol.h"
byte rx = 13;
byte tx = 14;


const uint16_t MSB=0xff00;
const uint16_t LSB=0x00ff;


void SWprint(byte data)
{
	byte mask;
	//startbit
	digitalWrite(tx,LOW);
	delayMicroseconds(bit9600Delay);
	for (mask = 0x01; mask>0; mask <<= 1) {
		if (data & mask){ // choose bit
			digitalWrite(tx,HIGH); // send 1
		}
		else{
			digitalWrite(tx,LOW); // send 0
		}
		delayMicroseconds(bit9600Delay);
	}
	//stop bit
	digitalWrite(tx, HIGH);
	delayMicroseconds(bit9600Delay);
}

byte SWread()
{
	byte val = 0;
	while (digitalRead(rx));
	//wait for start bit
	if (digitalRead(rx) == LOW) {
		delayMicroseconds(halfBit9600Delay);
		for (int offset = 0; offset < 8; offset++) {
			delayMicroseconds(bit9600Delay);
			val |= digitalRead(rx) << offset;
		}
		//wait for stop bit + extra
		delayMicroseconds(bit9600Delay); 
		delayMicroseconds(bit9600Delay);
		return val;
	}
}

uint16_t getRetVal(void){
	uint16_t val=SWread()<<8;
	val |= SWread();
  //MSWread();
	return val;
}
int distanceForward(int distanceInMillimeters){
	delay(20);
	while(getOdometerX() < distanceInMillimeters){
		delay(20);
		forward(350);
		Serial.print("Going Forward ");
		sonarEnable(B1 | B2 | B3 | B4);
		if((getSonar(1) < footToMil(CRITICAL_DISTANCE)) || (getSonar(2) < footToMil(CRITICAL_DISTANCE)) || (getSonar(3) < footToMil(CRITICAL_DISTANCE)) || (getSonar(4) < footToMil(CRITICAL_DISTANCE))){
			stop();
			beep(3, 0x40);
			delay(3000);
		}
		Serial.print(milToFoot(distanceInMillimeters));
		Serial.println(" feet");
		delay(50);
	}
	delay(50);
	stop();
}
uint16_t getSonar(uint8_t snum){
	SWprint(0x41);
	SWprint(0x00);
	SWprint(snum);
	return getRetVal();
}

uint16_t getOdometerX(void){
	SWprint(0x42);
	SWprint(0x00);
	SWprint(0x00);
	return getRetVal();
}

uint16_t getOdometerY(void){
	SWprint(0x43);
	SWprint(0x00);
	SWprint(0x00);
	return getRetVal();
}

uint16_t resetOdometer(void){
	SWprint(0x44);
	SWprint(0x00);
	SWprint(0x00);
	return getRetVal();
}

uint16_t forward(uint16_t speed){
	SWprint(0x45);
	SWprint((speed & MSB)>>8);
	SWprint(speed & LSB);
	//
	return getRetVal();
}

uint16_t turn(uint16_t angle){
	SWprint(0x46);
	SWprint((angle & MSB)>>8);
	SWprint(angle & LSB);
	return getRetVal();
}

uint16_t stop(void){
	SWprint(0x47);
	SWprint(0x00);
	SWprint(0x00);
	return getRetVal();
}

uint16_t beep(uint8_t len, uint8_t freq){
	SWprint(0x48);
	SWprint(len);
	SWprint(freq);
	return getRetVal();
}

uint16_t sonarEnable(uint8_t smask){
	SWprint(0x49);
	SWprint(0x00);
	SWprint(smask);
	return getRetVal();
}

uint16_t getOdometerTh(void){
	SWprint(0x4a);
	SWprint(0x00);
	SWprint(0x00);
	return getRetVal();
}
