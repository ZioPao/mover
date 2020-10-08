#include "header.h"

//Setup variables
bool isConnectionEstabilished;
Timer timer;

//Acceleration variables
int16_t fMov, sMov;
void setup()
{

  isConnectionEstabilished = false;

  setupBluetooth();
  //setupGamepadEmulation();

  fMov = 0;
  sMov = 0;
  timer.startTimer(1000, printValues);
#ifdef DISABLE_BT_TEST
  setupIMU();
  isConnectionEstabilished = true;
#endif
}

/////////////////////////////////////////
void printValues(int timer)
{
  Serial.print("Main value -> ");
  Serial.print(fMov);

  Serial.print("   ");
  Serial.println();

}
/////////////////////////////////////////
void loop()
{

  //BT Connection test

  if (!isConnectionEstabilished)
  {

    if (checkBTConnectionSlave())
    {
      isConnectionEstabilished = true;
      setupIMU();
    }
  }
  else
  {
    //Main loop
    timer.runTimers();
    fMov = getRealAcceleration();

    sendBluetoothData(fMov);
  }
}