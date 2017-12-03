#ifndef PROTOCOL_H_INC
#define PROTOCOL_H_INC





//void SWprint(byte data);
extern byte SWread();
extern int16_t getSonar(uint8_t snum);
extern int16_t getOdometerX(void);
extern uint16_t getOdometerY(void);
extern uint16_t resetOdometer(void);
extern uint16_t forward(uint16_t speed);
extern uint16_t turn(uint16_t angle);
extern uint16_t stop1(void);
extern uint16_t beep(uint8_t len, uint8_t freq);
extern uint16_t sonarEnable(uint8_t smask);
extern uint16_t getOdometerTh(void);


#endif
