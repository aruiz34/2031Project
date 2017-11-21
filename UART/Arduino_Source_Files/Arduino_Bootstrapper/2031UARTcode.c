#include <math.h>

Int getSonar(int sonarNumber);
Int getOdometer();
Void resetOdometer();
Void forward(int speed);
Void stop();
Void turn(int angle);
Void soundAlarm();
Void stopAlarm();

Void sweepingSensorCheck(marginL,marginR)
{
  If (getSonar(0) < marginL – 6*25.4 || getSonar(5) < marginR – 6*25.4)
  {
    SoundAlarm();
    delay(1000);
    StopAlarm();
    delay(5000);
    //Continue with movement path;
  }
}

Int intruderCollisionSensorCheck()
{
  If (getSonar(2) < 6*25.4 || getSonar(3) < 6*25.4)
  {
    Stop();
    SoundAlarm();
    delay(1000);
    StopAlarm();
    delay(5000);
    IntruderCollisionSensorCheck();//might implement differently
    Return 1;
  }
  Return 0;
}

Void MotionSensorCheck()
{
  Int firstArray[8];
  Int secondArray[8];
  For(int n = 0; n < 8; n++)
  {
    FirstArray[n] = getSonar(n);
  }
  delay(1000);
  For(int n = 0; n < 8; n++)
  {
    SecondArray[n] = getSonar(n);
  }
  For(int n = 0; n < 8; n++)
  {
    If (abs(firstArray[n] - secondArray[n]) < 6) {
      SoundAlarm();
      delay(1000);
      StopAlarm();
      Break;
    }
  }
}


Int main()
{
  Int slowSpeed = 100;
  Int middleSpeed = 350;
  Int x = getSonar(5);
  Int margin1k = (48-4)*25.4;
  Int margin1d = (237-8)*25.4-x;
  Int margin1j = (x);
  Int margin2a = (90)*25.4-x;
  Int margin2o = (30-4)*25.4;
  Int margin2g = (36-4)*25.4;
  Int margin3j = (96)*25.4+x;
  Int margin3l = (48-4)*25.4;
  Int margin3d = (191-8)*25.4-x;
  Int margin3b = (191+50-8)*25.4-x;


  While(1)
  {
    ResetOdometer();
    Forward(middleSpeed);
    While(getOdometer() < 56*25.4/1.05)
    {//from start to top of T
      SweepingSensorCheck(margin1k, margin1j);
      If(intruderCollisionSensorCheck)
      {
        Forward(middleSpeed);
      }
    }
    While(getOdometer() < 64*25.4/1.05)
    {//getting passed T head
      SweepingSensorCheck(6*25.4, margin1j);
      If(intruderCollisionSensorCheck)
      {
        Forward(middleSpeed);
      }
    }
    While(getOdometer() < 86*25.4/1.05)
    {//from top of T to turning point
      SweepingSensorCheck(margin1d, margin1j);
      If(intruderCollisionSensorCheck)
      {
        Forward(middleSpeed);
      }
    }
    Forward(slowSpeed);//slow down before stopping
    While(getOdometer() < 90*25.4/1.05) { }
    Stop();

    MotionSensorCheck();
    Turn(-30);
    MotionSensorCheck();
    Turn(-30);
    MotionSensorCheck();
    Turn(-30);
    MotionSensorCheck();

    ResetOdometer();
    Forward(middleSpeed);
    While(getOdometer() < 20*25.4/1.05)
    {
      SweepingSensorCheck(margin2a, margin2g);
      If(intruderCollisionSensorCheck)
      {
        Forward(middleSpeed);
      }
    }
    While(getOdometer() < 76*25.4/1.05)
    {
      SweepingSensorCheck(margin2o, margin2g);
      If(intruderCollisionSensorCheck)
      {
        Forward(middleSpeed);
      }
    }
    While(getOdometer() < 92*25.4/1.05)
    {
      SweepingSensorCheck(margin2a, margin2g);
      If(intruderCollisionSensorCheck)
      {
        Forward(middleSpeed);
      }
    }
    Forward(slowSpeed);
    While(getOdometer() < 96*25.4/1.05) { }
    Stop();

    MotionSensorCheck();
    Turn(-30);
    MotionSensorCheck();
    Turn(-30);
    MotionSensorCheck();
    Turn(-30);
    MotionSensorCheck();

    ResetOdometer();
    Forward(middleSpeed);
    While(getOdometer() < 26*25.4/1.05)
    {
      SweepingSensorCheck(margin3j, margin3d);
      If(intruderCollisionSensorCheck)
      {
        Forward(middleSpeed);
      }
    }
    While(getOdometer() < 34*25.4/1.05)
    {
      SweepingSensorCheck(6*25.4, margin3d);
      If(intruderCollisionSensorCheck)
      {
        Forward(middleSpeed);
      }
    }
    While(getOdometer() < 86*25.4/1.05)
    {
      SweepingSensorCheck(margin3l, margin3b);
      If(intruderCollisionSensorCheck)
      {
        Forward(middleSpeed);
      }
    }
    Forward(slowSpeed);
    While(getOdometer() < 90*25.4/1.05) { }
    Stop();

    MotionSensorCheck();
    Turn(60);
    MotionSensorCheck();
    Turn(60);
    MotionSensorCheck();
    Turn(60);
    MotionSensorCheck();

    ResetOdometer();
    Forward(middleSpeed);
    While(getOdometer() < 56*25.4/1.05)
    {
      SweepingSensorCheck(margin3b, margin3l);
      If(intruderCollisionSensorCheck)
      {
        Forward(middleSpeed);
      }
    }
    While(getOdometer() < 64*25.4/1.05)
    {
      SweepingSensorCheck(margin3d, 6*25.4/1.05);
      If(intruderCollisionSensorCheck)
      {
        Forward(middleSpeed);
      }
    }
    While(getOdometer() < 86*25.4/1.05)
    {
      SweepingSensorCheck(margin3d, margin3j);
      If(intruderCollisionSensorCheck)
      {
        Forward(middleSpeed);
      }
    }
    Forward(slowSpeed);
    While(getOdometer() < 90*25.4/1.05) { }
    Stop();

    MotionSensorCheck();
    Turn(30);
    MotionSensorCheck();
    Turn(30);
    MotionSensorCheck();
    Turn(30);
    MotionSensorCheck();

    ResetOdometer();
    Forward(middleSpeed);
    While(getOdometer() < 20*25.4/1.05)
    {
      SweepingSensorCheck(margin2g, margin2a);
      If(intruderCollisionSensorCheck)
      {
        Forward(middleSpeed);
      }
    }
    While(getOdometer() < 76*25.4/1.05)
    {
      SweepingSensorCheck(margin2g, margin2o);
      If(intruderCollisionSensorCheck)
      {
        Forward(middleSpeed);
      }
    }
    While(getOdometer() < 92*25.4/1.05)
    {
      SweepingSensorCheck(margin2g, margin2a);
      If(intruderCollisionSensorCheck)
      {
        Forward(middleSpeed);
      }
    }
    Forward(slowSpeed);
    While(getOdometer() < 96*25.4/1.05) { }
    Stop();

    MotionSensorCheck();
    Turn(30);
    MotionSensorCheck();
    Turn(30);
    MotionSensorCheck();
    Turn(30);
    MotionSensorCheck();

    ResetOdometer();
    Forward(middleSpeed);
    While(getOdometer() < 26*25.4/1.05)
    {
      SweepingSensorCheck(margin1j, margin1d);
      If(intruderCollisionSensorCheck)
      {
        Forward(middleSpeed);
      }
    }
    While(getOdometer() < 34*25.4/1.05)
    {
      SweepingSensorCheck(margin1j, 6*25.4);
      If(intruderCollisionSensorCheck)
      {
        Forward(middleSpeed);
      }
    }
    While(getOdometer() < 86*25.4/1.05)
    {
      SweepingSensorCheck(margin1j, margin1k);
      If(intruderCollisionSensorCheck)
      {
        Forward(middleSpeed);
      }
    }
    Forward(slowSpeed);
    While(getOdometer() < 90*25.4/1.05) { }
    Stop();

    MotionSensorCheck();
    Turn(-60);
    MotionSensorCheck();
    Turn(-60);
    MotionSensorCheck();
    Turn(-60);
    MotionSensorCheck();
  }
}
