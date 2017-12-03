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
#define footToMil(distanceInFeet) distanceInFeet*304.8
#define milToFoot(distanceInMillimeters) distanceInMillimeters/304.8
#define turnFactor(angle) ((3*1000)/90)*angle

#define CRITICAL_DISTANCE 2.3
#define THRESHOLD 2.5

//#define byte uint8_t

byte rx = 13;
byte tx = 14;
byte SWval;
char testVal;
char debug;
int valueSonar;

bool baffleffleCLeared = 0;
bool stuck = 0;

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
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
   Serial.println("Arduino Started");
 SWread();
 beep(3, 0x40);
 resetOdometer();
 delay(1000);
 resetOdometer();
 delay(1000);
 Serial.println("Byte Recieved");
 //delay(1000);
 //Serial.println(getOdometerX());
 
 resetOdometer();
}

void SWprint(byte data)
{
  byte mask;
  //startbit
  digitalWrite(tx,LOW);
  delayMicroseconds(bit9600Delay);
  for (mask = 0x01; mask>0; mask <<= 1) {
    if (data & mask){ // choose bit
      digitalWrite(tx,HIGH); // send 1u
    }
    else{
      digitalWrite(tx,LOW); // send 0
    }
    delayMicroseconds(bit9600Delay);
  }
  //stop1 bit
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
    //wait for stop1 bit + extra
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
int16_t getRetVal1(void){
  int16_t val=SWread()<<8;
  val |= SWread();
  //MSWread();
  return val;
}
int distanceForward(int distanceInMillimeters){
  sonarEnable(0xFF);
  delay(50);
  int time = 0;
  int originalOdometer = 0;
  while(getOdometerX() < distanceInMillimeters){
    delay(50);
    forward(350);
    //Serial.print("Going Forward ");
		if((getSonar(1) < footToMil(CRITICAL_DISTANCE)) || (getSonar(2) < footToMil(CRITICAL_DISTANCE)) || (getSonar(3) < footToMil(CRITICAL_DISTANCE)) || (getSonar(4) < footToMil(CRITICAL_DISTANCE)) || (getSonar(0) < footToMil(CRITICAL_DISTANCE)) || (getSonar(5) < footToMil(CRITICAL_DISTANCE)) || (getSonar(6) < footToMil(CRITICAL_DISTANCE)) || (getSonar(7) < footToMil(CRITICAL_DISTANCE))){
      forward(0);
        while(time > 17){
          resetOdometer();
          stop1();
          motionSensorCheck(8);
          //Serial.println("Now Stuck in motionSensorCheck");
          //stuck = 1;
        }
        //Serial.println("time");
        //Serial.println(time);
      time++;
      //beep(3, 0x40);
      //Serial.println("I've Detected an object that's too close");
      delay(200);
    }
    //Serial.print(milToFoot(distanceInMillimeters));
    //Serial.println(" feet");
    //Serial.println(" Actual distance moved");
    //Serial.println(milToFoot(getOdometerX()));
    delay(50);
  }
  delay(50);
  stop1();
  delay(200);
  //beep(8, 0x40);
  //Serial.println("stop1ping Robot");
  delay(50);
  sonarEnable(0);
}

int16_t getSonar(uint8_t snum){
  SWprint(0x41);
  SWprint(0x00);
  SWprint(snum);
  return getRetVal();
}

int16_t getOdometerX(void){
  SWprint(0x42);
  SWprint(0x00);
  SWprint(0x00);
  return getRetVal1();
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

uint16_t stop1(void){
  SWprint(0x47);
  SWprint(0x00);
  SWprint(0x00);
  //Serial.println("stop1 bytes sent");
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

void waitTurn(int angle)
{
  
}

void approachBaffle(){  //goes to right edge of baffle
  sonarEnable(B5 | B0);
  //Serial.println("in routine 1");
  //Serial.println(getSonar(0));

  while(1){
    //Serial.println(milToFoot(getSonar(0)));
    forward(350); 
    delay(50);

    valueSonar = getSonar(0);
    //We want to continue moving while sonar values are less than 1524
    //We also don't wish to stop1 of we get an eroneous ping(ie continue moving)
    //provided that incoming values are greater than 30000
    //logic (!((valueSonar < 1524) && (valueSonar > 30000)))
    if  (!((valueSonar < footToMil(5)) || (valueSonar > 30000))){
      break;
  
    }
    //Serial.println(valueSonar);
  }

  stop1();
  //turn off sonars to avoid future problems
  sonarEnable(0);
}
void clearBaffle(){
  resetOdometer();
  distanceForward(footToMil(2));
  //Serial.println("Moved Forward 2 feet");
  //don't imagine we need this anymore - we just delay by three once we turn
  //int originalTheta = convertAngle(getOdometerTh());
  //int currentTheta  = originalTheta;
  turn(90);
  delay(turnFactor(90));
    //Serial.println("Delay done - check if turn has comlpleted please.");
  delay(500);
  


}

void motionSensorCheck(int seconds)
{
  sonarEnable(0xFF);
for(int i = 0; i < seconds*2; i++){
int firstArray[8];
int secondArray[8];
//Serial.println("I'm here");
  for(int n = 0; n < 8; n++)
  {
    firstArray[n] = getSonar(n);
  }
delay(500);
  for(int n = 0; n < 8; n++)
  {
    secondArray[n] = getSonar(n);
  }
for(int n = 0; n < 8; n++)
{
  if (abs(firstArray[n] - secondArray[n]) > footToMil(THRESHOLD)) {
    if(i > 4 )
    //if(stuck)
    beep(8, 0x40);
    //Serial.println("Something moved by more than .7 feet");
    //delay(100);
    break;
  }
}
}
  sonarEnable(0x00);
}

void loop()
{
    //First order of business is to clear the baffle
  if(!baffleffleCLeared){
    distanceForward(footToMil(6));
    delay(100);
    //approachBaffle();
    //Serial.println("Baffle Edge Detected");
    baffleffleCLeared = 1;
    //clearBaffle();
    //Serial.println("Baffle Cleared"); 

    //Serial.println("About to Turn");
    resetOdometer();
    delay(200);
  turn(90);
  delay(10000);
  resetOdometer();
  motionSensorCheck(5);
  }

//Serial.println("Going Left");
  distanceForward(footToMil(6));
  resetOdometer();
  //motionSensorCheck(2);
  //delay(100);
  turn(180);
  delay(10000);
  resetOdometer();
  
//Serial.println("Going Right");
  distanceForward(footToMil(6));
  //motionSensorCheck();
  //delay(700);
  turn(180);
  delay(10000);

}

//void loop(){
//motionSensorCheck(1);
//}



