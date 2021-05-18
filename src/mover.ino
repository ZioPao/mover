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

  Serial.begin(115200);
  Serial.println("MASTER");

  delay(100); //Await Serial connection... todo handshake

  //Await Serial connection... todo handshake
  isManagerConnectionEstabilished = false;
  isBluetoothConnectionEstabilished = false;

  Serial.println("Waiting connection with manager");
  while (!isManagerConnectionEstabilished)
  {
    char chk_connection = Serial.read();
    isManagerConnectionEstabilished = (chk_connection == 'c');
  }

#ifdef DISABLE_BT_TEST
  isBluetoothConnectionEstabilished = true;
#endif

  Serial.println("Waiting connection with other mover");
  // //BT test connection
   while (!isBluetoothConnectionEstabilished)
   {
     isBluetoothConnectionEstabilished = bluetoothLink.checkConnectionSlave();
   }

  Serial.println("Setup IMU");
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


  // MAIN MOVER
  String m_acc = String(mAcc.x);
  m_acc += ",";
  m_acc += String(mAcc.y);
  m_acc += ",";
  m_acc += String(mAcc.z - 16384);
  m_acc += ",";

  String m_gyr = String(mGyr.x);
  m_gyr += ",";
  m_gyr += String(mGyr.y);
  m_gyr += ",";
  m_gyr += String(mGyr.z);


  String s_acc = String(sAcc.x);
  s_acc += ",";
  s_acc += String(sAcc.y);
  s_acc += ",";
  s_acc += String(sAcc.z - 16384);
  s_acc += ",";

  String s_gyr = String(sGyr.x);
  s_gyr += ",";
  s_gyr += String(sGyr.y);
  s_gyr += ",";
  s_gyr += String(sGyr.z);

  String final_m_string = m_acc + m_gyr;
  String final_s_string = s_acc + s_gyr;


  Serial.print(F("main"));
  Serial.println();

  Serial.print(final_m_string);

  Serial.println();
  Serial.print(F("slave"));
  Serial.println();
  
  Serial.print(final_s_string);

  Serial.println();

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

  imuManager.getGyroAndAccelValues(&mAcc, &mGyr);
  bluetoothLink.getData(&sAcc, &sGyr);

  //Serial.println("Test X");
  //Serial.println(sAcc.x);
  // Printing and debug
  if (timerPrinting.update())
  {
      printValues();

  }

  //Event handling from outer inputs like the manager
  checkEvents();

  //xinputMovement.manageMotions(fMov, sMov);
}
