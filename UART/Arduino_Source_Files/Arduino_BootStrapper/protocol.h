#ifndef PROTOCOL_H_INC
#define PROTOCOL_H_INC

#include <stdint.h>
#include <ctype.h>
#include <Arduino.h>
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

//#define rx 13
//#define tx 14
extern byte rx, tx;



//void SWprint(byte data);
extern byte SWread();
extern uint16_t getSonar(uint8_t snum);
extern uint16_t getOdometerX(void);
extern uint16_t getOdometerY(void);
extern uint16_t resetOdometer(void);
extern uint16_t forward(uint16_t speed);
extern uint16_t turn(uint16_t angle);
extern uint16_t stop(void);
extern uint16_t beep(uint8_t len, uint8_t freq);
extern uint16_t sonarEnable(uint8_t smask);
extern uint16_t getOdometerTh(void);


extern int distanceForward(int distanceInMillimeters);

#endif
