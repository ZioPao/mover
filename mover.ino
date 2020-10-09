#include "header.h"

//Setup variables
bool isConnectionEstabilished = false;
Timer timer;

XinputMovement xinputMovement;
BluetoothLink bluetoothLink;

//Acceleration variables
int16_t fMov, sMov;

void setup()
{
  isConnectionEstabilished = false;

  fMov = 0;
  sMov = 0;
  timer.startTimer(TIMER_PRINTING, printValues);

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

  Serial.print("Value from slave -> ");
  Serial.print(sMov);

  Serial.println();
}
////////////////////////////////////////

void loop()
{

  //BT Connection test

  if (!isConnectionEstabilished)
  {

    if (bluetoothLink.checkConnectionMaster())
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
    sMov = bluetoothLink.getData();

    xinputMovement.manageMotion(fMov, sMov);
  }
}