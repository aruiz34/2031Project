#ifndef PROTOCOL_H_INC
#define PROTOCOL_H_INC

#include <stdint.h>

uint16_t getSonar(uint8_t snum);
uint16_t getOdometerX(void);
uint16_t getOdometerY(void);
uint16_t resetOdometer(void);
uint16_t forward(uint16_t speed);
uint16_t turn(uint16_t angle);
uint16_t stop(void);
uint16_t beep(uint8_t len, uint8_t freq);
uint16_t sonarEnable(uint8_t smask);
uint16_t getOdometerTh(void);


#endif
