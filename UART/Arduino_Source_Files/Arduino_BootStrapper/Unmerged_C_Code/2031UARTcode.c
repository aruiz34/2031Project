#include <math.h>

int getSonar(int sonarNumber);
int getOdometer();
void resetOdometer();
void forward(int speed);
void stop();
void turn(int angle);
void soundAlarm();
void stopAlarm();

void sweepingSensorCheck(marginL,marginR)
{
  if (getSonar(0) < marginL – 6*25.4 || getSonar(5) < marginR – 6*25.4)
  {
    soundAlarm();
    delay(1000);
    stopAlarm();
    delay(5000);
    //Continue with movement path;
  }
}

int intruderCollisionSensorCheck()
{
  if (getSonar(2) < 6*25.4 || getSonar(3) < 6*25.4)
  {
    stop();
    soundAlarm();
    delay(1000);
    stopAlarm();
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
  delay(1000);
  for(int n = 0; n < 8; n++)
  {
    secondArray[n] = getSonar(n);
  }
  for(int n = 0; n < 8; n++)
  {
    if (abs(firstArray[n] - secondArray[n]) < 6) {
      soundAlarm();
      delay(1000);
      stopAlarm();
      break;
    }
  }
}


int main()
{
  int slowSpeed = 100;
  int middleSpeed = 350;
  int x = getSonar(5);
  int margin1k = (48-4)*25.4;
  int margin1d = (237-8)*25.4-x;
  int margin1j = (x);
  int margin2a = (90)*25.4-x;
  int margin2o = (30-4)*25.4;
  int margin2g = (36-4)*25.4;
  int margin3j = (96)*25.4+x;
  int margin3l = (48-4)*25.4;
  int margin3d = (191-8)*25.4-x;
  int margin3b = (191+50-8)*25.4-x;


  while(1)
  {
    resetOdometer();
    forward(middleSpeed);
    while(getOdometer() < 56*25.4/1.05)
    {//from start to top of T
      sweepingSensorCheck(margin1k, margin1j);
      if(intruderCollisionSensorCheck)
      {
        forward(middleSpeed);
      }
    }
    while(getOdometer() < 64*25.4/1.05)
    {//getting passed T head
      sweepingSensorCheck(6*25.4, margin1j);
      if(intruderCollisionSensorCheck)
      {
        forward(middleSpeed);
      }
    }
    while(getOdometer() < 86*25.4/1.05)
    {//from top of T to turning point
      sweepingSensorCheck(margin1d, margin1j);
      if(intruderCollisionSensorCheck)
      {
        forward(middleSpeed);
      }
    }
    forward(slowSpeed);//slow down before stopping
    while(getOdometer() < 90*25.4/1.05) { }
    stop();

    motionSensorCheck();
    turn(-30);
    motionSensorCheck();
    turn(-30);
    motionSensorCheck();
    turn(-30);
    motionSensorCheck();

    resetOdometer();
    forward(middleSpeed);
    while(getOdometer() < 20*25.4/1.05)
    {
      sweepingSensorCheck(margin2a, margin2g);
      if(intruderCollisionSensorCheck)
      {
        forward(middleSpeed);
      }
    }
    while(getOdometer() < 76*25.4/1.05)
    {
      sweepingSensorCheck(margin2o, margin2g);
      if(intruderCollisionSensorCheck)
      {
        forward(middleSpeed);
      }
    }
    while(getOdometer() < 92*25.4/1.05)
    {
      sweepingSensorCheck(margin2a, margin2g);
      if(intruderCollisionSensorCheck)
      {
        forward(middleSpeed);
      }
    }
    forward(slowSpeed);
    while(getOdometer() < 96*25.4/1.05) { }
    stop();

    motionSensorCheck();
    turn(-30);
    motionSensorCheck();
    turn(-30);
    motionSensorCheck();
    turn(-30);
    motionSensorCheck();

    resetOdometer();
    forward(middleSpeed);
    while(getOdometer() < 26*25.4/1.05)
    {
      sweepingSensorCheck(margin3j, margin3d);
      if(intruderCollisionSensorCheck)
      {
        forward(middleSpeed);
      }
    }
    while(getOdometer() < 34*25.4/1.05)
    {
      sweepingSensorCheck(6*25.4, margin3d);
      if(intruderCollisionSensorCheck)
      {
        forward(middleSpeed);
      }
    }
    while(getOdometer() < 86*25.4/1.05)
    {
      sweepingSensorCheck(margin3l, margin3b);
      if(intruderCollisionSensorCheck)
      {
        forward(middleSpeed);
      }
    }
    forward(slowSpeed);
    while(getOdometer() < 90*25.4/1.05) { }
    stop();

    motionSensorCheck();
    turn(60);
    motionSensorCheck();
    turn(60);
    motionSensorCheck();
    turn(60);
    motionSensorCheck();

    resetOdometer();
    forward(middleSpeed);
    while(getOdometer() < 56*25.4/1.05)
    {
      sweepingSensorCheck(margin3b, margin3l);
      if(intruderCollisionSensorCheck)
      {
        forward(middleSpeed);
      }
    }
    while(getOdometer() < 64*25.4/1.05)
    {
      sweepingSensorCheck(margin3d, 6*25.4/1.05);
      if(intruderCollisionSensorCheck)
      {
        forward(middleSpeed);
      }
    }
    while(getOdometer() < 86*25.4/1.05)
    {
      sweepingSensorCheck(margin3d, margin3j);
      if(intruderCollisionSensorCheck)
      {
        forward(middleSpeed);
      }
    }
    forward(slowSpeed);
    while(getOdometer() < 90*25.4/1.05) { }
    stop();

    motionSensorCheck();
    turn(30);
    motionSensorCheck();
    turn(30);
    motionSensorCheck();
    turn(30);
    motionSensorCheck();

    resetOdometer();
    forward(middleSpeed);
    while(getOdometer() < 20*25.4/1.05)
    {
      sweepingSensorCheck(margin2g, margin2a);
      if(intruderCollisionSensorCheck)
      {
        forward(middleSpeed);
      }
    }
    while(getOdometer() < 76*25.4/1.05)
    {
      sweepingSensorCheck(margin2g, margin2o);
      if(intruderCollisionSensorCheck)
      {
        forward(middleSpeed);
      }
    }
    while(getOdometer() < 92*25.4/1.05)
    {
      sweepingSensorCheck(margin2g, margin2a);
      if(intruderCollisionSensorCheck)
      {
        forward(middleSpeed);
      }
    }
    forward(slowSpeed);
    while(getOdometer() < 96*25.4/1.05) { }
    stop();

    motionSensorCheck();
    turn(30);
    motionSensorCheck();
    turn(30);
    motionSensorCheck();
    turn(30);
    motionSensorCheck();

    resetOdometer();
    forward(middleSpeed);
    while(getOdometer() < 26*25.4/1.05)
    {
      sweepingSensorCheck(margin1j, margin1d);
      if(intruderCollisionSensorCheck)
      {
        forward(middleSpeed);
      }
    }
    while(getOdometer() < 34*25.4/1.05)
    {
      sweepingSensorCheck(margin1j, 6*25.4);
      if(intruderCollisionSensorCheck)
      {
        forward(middleSpeed);
      }
    }
    while(getOdometer() < 86*25.4/1.05)
    {
      sweepingSensorCheck(margin1j, margin1k);
      if(intruderCollisionSensorCheck)
      {
        forward(middleSpeed);
      }
    }
    forward(slowSpeed);
    while(getOdometer() < 90*25.4/1.05) { }
    stop();

    motionSensorCheck();
    turn(-60);
    motionSensorCheck();
    turn(-60);
    motionSensorCheck();
    turn(-60);
    motionSensorCheck();
  }
}
