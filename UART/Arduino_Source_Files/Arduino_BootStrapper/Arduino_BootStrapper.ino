//Created August 23 2006
//Heather Dewey-Hagborg
//http://www.arduino.cc

#include <ctype.h>
#include <stdint.h>
#include "protocol.h"

#define bit9600Delay 100
#define halfBit9600Delay 50
#define bit4800Delay 188
#define halfBit4800Delay 94

#define B0 0x01
#define B1 0x02
#define B2 0x04
#define B3 0x08
#define B4 0x10
#define B5 0x20
#define B6 0x40
#define B7 0x80

//#define byte uint8_t

byte rx = 13;
byte tx = 14;
byte SWval;
char testVal;
char debug;
bool started = 0;
int valueSonar;

const uint16_t MSB=0xff00;
const uint16_t LSB=0x00ff;

void setup() {
	pinMode(rx,INPUT);
	pinMode(tx,OUTPUT);
	digitalWrite(tx,HIGH);
	delay(2);
	digitalWrite(13,HIGH); //turn on debugging LED

	 delay(1000);
	 //setup serial - for debugging and testing implemented commands - remove later
	 Serial.begin(9600);

	 // while (!Serial) {
	 // 	 ; // wait for serial port to connect. Needed for native USB port only
	 // }
	 Serial.println("Arduino Started");
	 SWread();
	 Serial.println("Byte Recieved");
	 beep(2,0x40);
}

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
int convertAngle(int arg){
	return (arg>180)  ? arg - 360 : arg;
}
void routine1(){	//clear baffle
	sonarEnable(B2 | B3);
	Serial.println("in routine 1");
	Serial.println(getSonar(0));
	resetOdometer();
	while((getSonar(3)>850) && (getSonar(3)>850)){
		forward(350);
		delay(50);
	}
	beep(2,0x40);
	/*while(getOdometerX() < 1524){
		forward(350);
		delay(50);
		}
		beep(2,0x40);
	while(1){
	Serial.println(getSonar(0));
		forward(350);
		delay(50);
		valueSonar = getSonar(0);
		if (!((valueSonar < 1524) && (valueSonar < 30000))){
			break;
		}
		beep(2,0x40);
		Serial.println(valueSonar);
	}*/
	stop();
	//turn off sonars to avoid future problems
	sonarEnable(0);
}

void routine2(){
	resetOdometer();
	turn(90);
	delay(5000);
	sonarEnable(B0);
	resetOdometer();
	while(getOdometerX() < 1530){
		forward(350);
		int d=getSonar(0);
		if((d<3048)&&(d>915)) {beep(8,0x40);}
		delay(50);
	}
	beep(2,0x40);
	stop();
	int originalTheta = convertAngle(getOdometerTh());
	int currentTheta  = originalTheta;
}

void routine3(){
	sonarEnable(B5 | B0);
	resetOdometer();
	while(getOdometerX() < 1530){
		forward(350);
		delay(50);
	}
	turn(180);
	delay(4000);
	sonarEnable(0);
}

void loop()
{
	if(!started){
		routine1();
		routine2();
		Serial.println("im alive");
	}
	started = 1;
}
