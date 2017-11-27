//Created August 23 2006
//Heather Dewey-Hagborg
//http://www.arduino.cc

#include "protocol.h"


//#define byte uint8_t

byte SWval;
char testVal;
char debug;
int valueSonar;


bool baffleffleCLeared = 0;

int convertAngle(int arg){
	return (arg>180)  ? arg - 360 : arg;
}
void approachBaffle(){	//goes to right edge of baffle
	sonarEnable(B5 | B0);
	Serial.println("in routine 1");
	Serial.println(getSonar(0));

	while(1){
<<<<<<< HEAD:UART/Arduino_Source_Files/Arduino_Bootstrapper/Arduino_BootStrapper.ino
		Serial.println(getSonar(0));
		forward(350);	
		delay(50);

		valueSonar = getSonar(0);
		//We want to continue moving while sonar values are less than 1524
		//We also don't wish to stop of we get an eroneous ping(ie continue moving)
		//provided that incoming values are greater than 30000
		//logic (!((valueSonar < 1524) && (valueSonar > 30000)))
		if	(!((valueSonar < footToMil(5)) || (valueSonar > 30000))){
			break;
  
		}
		Serial.println(valueSonar);
=======
    Serial.println(getSonar(0));
		forward(350);
		delay(50);
    valueSonar = getSonar(0);
    if (!((valueSonar < 1524) && (valueSonar < 30000))){
      break;
    }
    Serial.println(valueSonar);
>>>>>>> 82204bb20e4cfbbc11ea148673d02bfee057a7c4:UART/Arduino_Source_Files/Arduino_BootStrapper/Arduino_BootStrapper.ino
	}

	stop();
	//turn off sonars to avoid future problems
	sonarEnable(0);
}
<<<<<<< HEAD:UART/Arduino_Source_Files/Arduino_Bootstrapper/Arduino_BootStrapper.ino
void clearBaffle(){
=======

void routine2(){
>>>>>>> 82204bb20e4cfbbc11ea148673d02bfee057a7c4:UART/Arduino_Source_Files/Arduino_BootStrapper/Arduino_BootStrapper.ino
	resetOdometer();
	distanceForward(footToMil(2));
	Serial.println("Moved Forward 2 feet");
	//don't imagine we need this anymore - we just delay by three once we turn
	//int originalTheta = convertAngle(getOdometerTh());
	//int currentTheta  = originalTheta;
	turn(90);
<<<<<<< HEAD:UART/Arduino_Source_Files/Arduino_Bootstrapper/Arduino_BootStrapper.ino
	delay(turnFactor(90));
  	Serial.println("Delay done - check if turn has comlpleted please.");
	delay(5000);
	
=======
	delay(4000);
>>>>>>> 82204bb20e4cfbbc11ea148673d02bfee057a7c4:UART/Arduino_Source_Files/Arduino_BootStrapper/Arduino_BootStrapper.ino

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
void setup() {

  pinMode(rx,INPUT);
  pinMode(tx,OUTPUT);
  digitalWrite(tx,HIGH);
  delay(2);
  //digitalWrite(13,HIGH); //turn on debugging LED

   delay(1000);
   //setup serial - for debugging and testing implemented commands - remove later
  Serial.begin(9600);  
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
   Serial.println("Arduino Started");
 SWread();
 Serial.println("Byte Recieved");
}

void loop()
{
  	//First order of business is to clear the baffle
	if(!baffleffleCLeared){
		approachBaffle();
		Serial.println("Baffle Edge Detected");
		baffleffleCLeared = 1;
		clearBaffle();
		Serial.println("Baffle Cleared");	
	}
	distanceForward(footToMil(6));
	turn(180);
	distanceForward(footToMil(6));
	turn(180);

}
