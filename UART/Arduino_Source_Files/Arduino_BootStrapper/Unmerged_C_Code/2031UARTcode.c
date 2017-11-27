#define in2mm(inches) inches*25.4
#define MIDDLESPEED 350
#define turnFactor(angle) ((3*1000)/90)*angle

#include <math.h>

/*
int getSonar(int sonarNumber);
int getOdometer();
void resetOdometer();
void forward(int speed);
void stop();
void turn(int angle);
void beep(int time, int freq);
*/

/*
void sweepingSensorCheck(marginL,marginR)
{
  if (getSonar(0) < marginL – in2mm(6) || getSonar(5) < marginR – in2mm(6))
  {
    soundAlarm();
    delay(1000);
    stopAlarm();
    delay(5000);
    //Continue with movement path;
  }
}
*/

int intruderCollisionSensorCheck()
{
  if (getSonar(2) < in2mm(6) || getSonar(3) < in2mm(6))
  {
    stop();
    beep(3, 0x40);
    delay(500);
    delay(5000);
    intruderCollisionSensorCheck();//might implement differently
    return 1;
  }
  return 0;
}

void motionSensorCheck()
{
  int firstArray[8];
  int secondArray[8];
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
    if (abs(firstArray[n] - secondArray[n]) < 6) {
      beep();
      delay(5000);
      break;
    }
  }
}

void step2and8()
{
  turn(90);
  delay(turnFactor(90));
}

void step3and7()
{
  resetOdometer();
  sonarEnable(B2 | B3);
  forward(MIDDLESPEED);
  while(getOdometer() < in2mm(96)/1.05)
  {
    if(intruderCollisionSensorCheck)
    {
      forward(MIDDLESPEED);
    }
  }
  stop();
  sonarEnable(0);
}

void step4and6()
{
  turn(-90);
  delay(turnFactor(90));
}

void setup()
{
  resetOdometer();
    forward(middleSpeed);
    while(getOdometer() < in2mm(90)/1.05)
    {
      if(intruderCollisionSensorCheck)
      {
        forward(MIDDLESPEED);
      }
    }
    stop();
  turn(180);
  delay(turnFactor(180));
}

void step1and5(int iterations)
{
  sonarEnable(0xFF);
  for(int n = 0; n < iterations; n++)
  {
    motionSensorCheck();
  }
  sonarEnable(0);
}

void loop()
{
  step1and5(10);
  step2and8();
  step3and7();
  step4and6();
  step1and5();
  step4and6();
  step3and7();
  step2and8();
}
