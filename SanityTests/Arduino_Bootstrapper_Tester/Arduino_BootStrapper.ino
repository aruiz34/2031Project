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

//#define byte uint8_t

byte rx = 13;
byte tx = 14;
byte SWval;
char testVal;
char debug;

const uint16_t MSB=0xff00;
const uint16_t LSB=0x00ff;

void setup() {
  pinMode(rx,INPUT);
	pinMode(tx,OUTPUT);
	digitalWrite(tx,HIGH);
	delay(2);
	digitalWrite(13,HIGH); //turn on debugging LED

  //setup serial - for debugging and testing implemented commands - remove later
  Serial.begin(9600);  
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
 Serial.println("Arduino Started");
 SWread();
 Serial.println("Byte Recieved");
 delay(1000);
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
void SonarTest(){
	sonarEnable(0xFF);
	delay(1500);

		for (int i=0; i<8;i++){
			Serial.print(i);
			Serial.print(" ; ");
			Serial.print(getSonar(i), DEC);
			Serial.println();
		}
	delay(1500);
	sonarEnable(0x00);
}
void BeepTest(){
	beep(3,0x30);
	delay(500);
	beep(3,0x40);
	delay(500);
}
void odometryTest(){
	Serial.print("X: ");
	Serial.println(getOdometerX(), DEC);

	Serial.print("Y: ");
	Serial.println(getOdometerY(), DEC);

	Serial.print("Theta: ");
	Serial.println(getOdometerTh(), DEC);
}

void movementTest(){
	resetOdometer();
	Serial.println("RESET");
	odometryTest();
	Serial.println();

	Serial.println("Forward");
	forward(350);
	delay(1000);
	odometryTest();
	Serial.println();

	Serial.println("Stop");
	stop();
	delay(500);
	odometryTest();
	Serial.println();

	Serial.println("turn 90");
	turn(90);
	delay(500);
	odometryTest();
	Serial.println();

	Serial.println("turn 270");
	turn(270);
	delay(500);
	odometryTest();
	Serial.println();
	
}
void loop()
{
	delay(1500);
	Serial.println("I'm Still Alive");
	movementTest();


	
//	Serial.println("debug");
//	       testVal = forward(300);
//	       //SWval = SWread();
//	 Serial.println("done");
//	 Serial.println(testVal);
//	 delay(1500);
//	 testVal = forward(0);
//	 delay(1500);
//	 //SWval = Serial.read();
//		//SWprint(toupper(SWval));
}
