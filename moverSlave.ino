#include "header.h"

//Setup variables
bool isConnectionEstabilished;

//Timer stuff
MiniTimer timerPrinting;

//Acceleration variables
int16_t fMov;

//Components
BluetoothLink bluetoothLink;
IMUManager imuManager;

void setup()
{
  isConnectionEstabilished = false;
  imuManager.setup();

  fMov = 0;

  //Timer setup
  timerPrinting.setup(TIMER_PRINTING);

#ifdef DISABLE_BT_TEST
  isConnectionEstabilished = true;
#endif

  //BT test connection
  while (!isConnectionEstabilished)
  {
    if (bluetoothLink.checkConnectionMaster())
    {
      isConnectionEstabilished = true;
    }
  }
}

/////////////////////////////////////////
void printValues()
{
  Serial.print("Main value -> ");
  Serial.print(fMov);

  Serial.print("   ");
  Serial.println();
}
/////////////////////////////////////////
void loop()
{
  fMov = imuManager.getRealAcceleration();
  bluetoothLink.sendData(fMov);

  //Print in the serial monitor once in a predetermined interval
  if (timerPrinting.update())
  {
    printValues();
  }
}