#include "header.h"

//Setup variables
bool isConnectionEstabilished;
Timer timer;

//Acceleration variables
int16_t fMov, sMov;

//Components
XinputMovement xinputMovement;
BluetoothLink bluetoothLink;
IMUManager imuManager;


void setup()
{
  isConnectionEstabilished = false;
  imuManager.setup();

  fMov = 0;
  sMov = 0;
  timer.startTimer(TIMER_PRINTING, printValues);

#ifdef DISABLE_BT_TEST
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

    if (bluetoothLink.checkConnectionSlave())
    {
      isConnectionEstabilished = true;
    }
  }
  else
  {
    //Main loop
    timer.runTimers();
    fMov = imuManager.getRealAcceleration();

    bluetoothLink.sendData(fMov);
  }
}