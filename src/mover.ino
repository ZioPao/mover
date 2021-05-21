#include "header.h"
//#define MASTER

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

  Serial.begin(115200);


  #ifdef MASTER
  Serial.println("MASTER");
  #else
  Serial.println("SLAVE");
  #endif
  delay(100); //Await Serial connection... todo handshake

  //Await Serial connection... todo handshake
  isManagerConnectionEstabilished = false;
  isBluetoothConnectionEstabilished = false;

#ifdef ENABLE_MANAGER_CONNECTION_TEST
  Serial.println("Waiting connection with manager");
  while (!isManagerConnectionEstabilished)
  {
    char chk_connection = Serial.read();
    isManagerConnectionEstabilished = (chk_connection == 'c');
  }
#endif

#ifdef ENABLE_BT_TEST
  Serial.println("Waiting connection with other mover");
  // //BT test connection
   while (!isBluetoothConnectionEstabilished)
   {
     isBluetoothConnectionEstabilished = bluetoothLink.checkConnectionSlave();
   }

  Serial.println("Setup IMU");
#endif


#ifdef ENABLE_IMU
// Sensor readings with offsets:   8       0       16382   1       0       1
// Your offsets:   		-286    -315    1693    54      -49     -32
  imuManager.setup(-285, -315, 1693, 54, -49, -3);
#endif

  Serial.println("Setup timers");
  //Timer setup
  timerPrinting.setup(TIMER_PRINTING);
  timerMovement.setup(TIMER_MOVEMENT);
}

void reset()
{

  //Await Serial connection... todo handshake
  isManagerConnectionEstabilished = false;
  isBluetoothConnectionEstabilished = false;

  Serial.println("Waiting connection with manager");
  while (!isManagerConnectionEstabilished)
  {
    char chk_connection = Serial.read();
    isManagerConnectionEstabilished = (chk_connection == 'c');
  }

  Serial.println("Setup IMU");
#ifdef ENABLE_IMU
  //-192    -294    1666    53      -50     -27
  imuManager.setup(-192, -294, 1666, 53, -50, -27);
#endif

  Serial.println("Setup timers");
  //Timer setup
  timerPrinting.setup(TIMER_PRINTING);
  timerMovement.setup(TIMER_MOVEMENT);
}

//////////////////////////////////////////////////////////////////////////////////
void printValues()
{
  
  String acc_string = String(mAcc.x);
  acc_string += ",";
  acc_string += String(mAcc.y);
  acc_string += ",";
  acc_string += String(mAcc.z);
  acc_string += ",";

  Serial.println(acc_string);
  Serial.flush();

}

void checkEvents()
{

  char cmd = Serial.read();

  switch (cmd)
  {
  case 'r':

    //rerun setup
    reset();
    break;
  }
}
//////////////////////////////////////////////////////////////////////////////////

void loop()
{
  mAcc = imuManager.getAccelValues();

  // todo something went wrong with bluetooth and I can't get it working again. So... USB for now
  //bluetoothLink.getData(&sAcc, &sGyr);
  
  printValues();

  //if (timerPrinting.update())
  //{

  //}

  //Event handling from outer inputs like the manager
  checkEvents();

}