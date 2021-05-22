#include "header.h"

#define MASTER

//Setup variables
bool isManagerConnectionEstabilished;
bool isBluetoothConnectionEstabilished;

//Components
XinputMovement xinputMovement;
IMUManager imuManager;

//Bluetooth stuff
SerialTransfer bluetooth_transfer;

//Timer stuff
MiniTimer timerPrinting;
MiniTimer timerMovement;

//Movement variables
VectorInt16 acc;

#ifdef MASTER
VectorInt16 second_acc;
#endif
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

#ifdef ENABLE_IMU
  Serial.println("Setup IMU");

  // Sensor readings with offsets:   8       0       16382   1       0       1
  // Your offsets:   		-286    -315    1693    54      -49     -32
  imuManager.setup(-285, -315, 1693, 54, -49, -3);
#endif

  Serial.println("Setup timers");
  //Timer setup
  timerPrinting.setup(TIMER_PRINTING);
  timerMovement.setup(TIMER_MOVEMENT);

  // Bluetooth setup

  Serial1.begin(115200);
  bluetooth_transfer.begin(Serial1);


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
void printValues(VectorInt16 slave_acc)
{

  String acc_string = String(acc.x);
  acc_string += ",";
  acc_string += String(acc.y);
  acc_string += ",";
  acc_string += String(acc.z);
  acc_string += ",";
  acc_string += String(slave_acc.x);
  acc_string += ",";
  acc_string += String(slave_acc.y);
  acc_string += ",";
  acc_string += String(slave_acc.z);
  acc_string += ",";

  Serial.println(acc_string);
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

  acc = imuManager.getAccelValues();

#ifdef MASTER

  uint16_t received_data = 0;

  if (bluetooth_transfer.available())
  {
    bluetooth_transfer.rxObj(second_acc, received_data);
    
  }

  printValues(second_acc);

#else

  uint16_t sent_data = 0;
  sent_data = bluetooth_transfer.txObj(acc, sent_data);
  bluetooth_transfer.sendData(sent_data);
  delay(50);


#endif

  //checkEvents();

  //printValues();

  //if (timerPrinting.update())
  //{

  //}

  //Event handling from outer inputs like the manager
}