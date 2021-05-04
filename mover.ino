#include "header.h"

//Setup variables
bool isManagerConnectionEstabilished;
bool isBluetoothConnectionEstabilished;

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
    
  delay(3000);

  Serial.begin(9600); //not sure if it's correct
  Serial.println("MASTER");

  //Await Serial connection... todo handshake
  isManagerConnectionEstabilished = false;
  isBluetoothConnectionEstabilished = false;

  while (!isManagerConnectionEstabilished)
  {
    char chk_connection = Serial.read();
    isManagerConnectionEstabilished = (chk_connection == 'c');
  }
  
#ifdef DISABLE_BT_TEST
  isConnectionEstabilished = true;
#endif

  //BT test connection
  while (!isBluetoothConnectionEstabilished)
  {
    isBluetoothConnectionEstabilished = bluetoothLink.checkConnectionMaster();
  }
#ifdef ENABLE_IMU
  imuManager.setup();
#endif

  //Timer setup
  timerPrinting.setup(TIMER_PRINTING);
  timerMovement.setup(TIMER_MOVEMENT);
}

//////////////////////////////////////////////////////////////////////////////////
void printValues()
{

  /* VALUES FROM MAIN MOVER*/
  Serial.print("main");
  Serial.println();

  //Accelerometer
  Serial.print(mAcc.x);
  Serial.print(",");
  Serial.print(mAcc.y);
  Serial.print(",");
  Serial.print(mAcc.z);
  Serial.print(",");

  //Gyroscope
  Serial.print(mGyr.x);
  Serial.print(",");
  Serial.print(mGyr.y);
  Serial.print(",");
  Serial.print(mGyr.z);

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

void checkEvents()
{

  char cmd = Serial.read();

  switch (cmd)
  {
  case 'r':

    //rerun setup
    setup();
    break;
  }
}
//////////////////////////////////////////////////////////////////////////////////

void loop()
{

  imuManager.getGyroAndAccelValues(&mAcc, &mGyr);
  bluetoothLink.getData(&sAcc, &sGyr);

  // Printing and debug
  if (timerPrinting.update())
  {
    printValues();
  }

  //Event handling from outer inputs like the manager
  checkEvents();

  //xinputMovement.manageMotions(fMov, sMov);
}
