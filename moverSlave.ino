#include "header.h"

//Setup variables
bool isConnectionEstabilished;

//Components
XinputMovement xinputMovement;
BluetoothLink bluetoothLink;
IMUManager imuManager;

//Timer stuff
MiniTimer timerPrinting;
MiniTimer timerMovement;

//Movement variables
VectorInt16 mAcc, sAcc;
VectorInt16 mGyr, sGyr;


void setup()
{

  while (!Serial)
    ; // wait for Leonardo enumeration, others continue immediately
  //TEST
  //pinMode(17, OUTPUT);
  Serial.println("SLAVE");

  isConnectionEstabilished = false;

  #ifdef ENABLE_IMU
    imuManager.setup();
  #endif

  //Timer setup
  timerPrinting.setup(TIMER_PRINTING);
  timerMovement.setup(TIMER_MOVEMENT);

#ifdef DISABLE_BT_TEST
  isConnectionEstabilished = true;
#endif

  //BT test connection
  while (!isConnectionEstabilished)
  {
    if (bluetoothLink.checkConnectionSlave())
    {
      isConnectionEstabilished = true;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////
void printValues()
{

  /* VALUES FROM SLAVE MOVER*/
  Serial.println();
  Serial.print("slave");
  Serial.println();

  //Accelerometer
  Serial.print(sAcc.x);
  Serial.print(",");
  Serial.print(sAcc.y);
  Serial.print(",");
  Serial.print(sAcc.z);
  Serial.print(",");

  //Gyroscope
  Serial.print(sGyr.x);
  Serial.print(",");
  Serial.print(sGyr.y);
  Serial.print(",");
  Serial.print(sGyr.z);

  Serial.println();
}

//////////////////////////////////////////////////////////////////////////////////

void loop()
{

  #ifdef ENABLE_IMU
    imuManager.getGyroAndAccelValues(&sAcc, &sGyr);
  #else
    sAcc = VectorInt16(1,1,1);
    sGyr = VectorInt16(1,1,1);
  #endif

  bluetoothLink.sendData(sAcc, sGyr);

  // Printing and debug
   if (timerPrinting.update())
   {
     // printValues();
   }

}
