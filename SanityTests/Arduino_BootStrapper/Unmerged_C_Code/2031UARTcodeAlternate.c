int getSonar(int sonarNumber);
int getOdometer();
void resetOdometer();
void forward(int speed);
void stop();
void turn(int angle);
void soundAlarm();
void stopAlarm();


int intruderCollisionSensorCheck()
{
  if (getSonar(2) < 6*25.4 || getSonar(3) < 6*25.4)
  {
    stop();
    soundAlarm();
    delay(1000);
    StopAlarm();
    delay(5000);
    intruderCollisionSensorCheck();//might implement differently
    return 1;
  }
  return 0;
}

void motionSensorCheck()
{
  int firstArray[8];
  for(int n = 0; n < 8; n++)
  {
    firstArray[n] = getSonar(n);
  }
  for(int m = 0; m < 20; m++)
  {
    for(int n = 0; n < 8; n++)
    {
      if (abs(firstArray[n] - getSonar(n)) < 6) {
        soundAlarm();
        delay(1000);
        stopAlarm();
        break;
      }
    }
    delay(500);
  }
}


int main()
{
  int middleSpeed = 350;

  while(1)
  {
    resetOdometer();
    forward(middleSpeed);
    while(getOdometer() < 90*25.4/1.05)
    {
      if(intruderCollisionSensorCheck)
      {
        forward(middleSpeed);
      }
    }
    stop();

    turn(-180);
    motionSensorCheck();
    turn(90);

    resetOdometer();
    forward(middleSpeed);
    while(getOdometer() < 96*25.4/1.05)
    {
      if(intruderCollisionSensorCheck)
      {
        forward(middleSpeed);
      }
    }
    stop();

    turn(-90);
    motionSensorCheck();
    turn(-90);

    resetOdometer();
    forward(middleSpeed);
    while(getOdometer() < 96*25.4/1.05)
    {
      if(intruderCollisionSensorCheck)
      {
        forward(middleSpeed);
      }
    }
    stop();

    turn(90);
    motionSensorCheck();
    turn(90);
}
