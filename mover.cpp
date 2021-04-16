#include "header.h"

//Setup variables
bool isConnectionEstabilished;

//Timer stuff
MiniTimer timerPrinting;
MiniTimer timerMovement;

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

  //Timer setup
  timerPrinting.setup(TIMER_PRINTING);
  timerMovement.setup(TIMER_MOVEMENT);

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

  Serial.print("Value from slave -> ");
  Serial.print(sMov);

  Serial.println();
}
////////////////////////////////////////

void loop()
{

  //Gets the necessary values
  fMov = imuManager.getRealAcceleration();
  sMov = bluetoothLink.getData();

  //Printing and debug
  if (timerPrinting.update())
  {
    printValues();
  }

    xinputMovement.manageMotions(fMov, sMov);
  
}
