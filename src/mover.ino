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
Vector2Float gyr;

#ifdef MASTER

//#define DEBUG_MASTER
VectorInt16 second_acc;
Vector2Float second_gyr;

float x_filter_old = 0;
float x_og_old = 0;

float y_filter_old = 0;
float y_og_old = 0;

float z_filter_old = 0;
float z_og_old = 0;

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

  // Debug LEDs setup

  pinMode(DEBUG_LED_PIN, OUTPUT);
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

#ifdef MASTER
//////////////////////////////////////////////////////////////////////////////////
// MASTER ONLY
//////////////////////////////////////////////////////////////////////////////////
void printValues()
{

  //filtering
  //a[1] \times yfilt[i-1] + b[0]
  //float x_filter = 0.9601172921934632 * x_filter_old + 0.019941353903268455 * acc.x + 0.019941353903268566 * x_og_old;

  /// X FILTERING

  float b[] = {0.00066048, 0.00132097, 0.00066048};
  float a[] = {1.92600086, -0.92864279};
  

  float x_filter = 0.9601172921934632 * x_filter_old + 0.019941353903268455 * acc.x + 0.019941353903268566 * x_og_old;
  x_filter_old = x_filter;
  x_og_old = acc.x;


  // Y FILTERING
  float y_filter = 0.9601172921934632 * y_filter_old + 0.019941353903268455 * acc.y + 0.019941353903268566 * y_og_old;
  y_filter_old = y_filter;
  y_og_old = acc.y;


  // Z FILTERING
  float z_filter = 0.9601172921934632 * z_filter_old + 0.019941353903268455 * acc.z + 0.019941353903268566 * z_og_old;
  z_filter_old = z_filter;
  z_og_old = acc.z;


  // TEST ONLY ACCELEROMETERS

  String acc_string = String(acc.x);    // unfiltered x
  acc_string += ",";
  acc_string += String(y_filter);
  acc_string += ",";
  acc_string += String(z_filter);
  acc_string += ",";
  acc_string += String(millis());
  Serial.println(acc_string);
  /*

  String acc_string = "a,";
  acc_string += String(acc.x);
  acc_string += ",";
  acc_string += String(acc.y);
  acc_string += ",";
  acc_string += String(acc.z);
  //acc_string += ",";
  //acc_string += String(second_acc.x);
  //acc_string += ",";
  //acc_string += String(second_acc.y);
  //acc_string += ",";
  //acc_string += String(second_acc.z);

  Serial.println(acc_string);

  String gyr_string = "g,";

  gyr_string += String(gyr.y);
  gyr_string += ",";
  gyr_string += String(gyr.z);
  gyr_string += ",";
  //gyr_string += String(second_gyr.y);
  //gyr_string += ",";
  //gyr_string += String(second_gyr.z);
  //gyr_string += ",";

  gyr_string += String(millis());

  Serial.println(gyr_string);
*/
}

void receiveData(VectorInt16* a, Vector2Float* g)
{

  #ifndef DEBUG_MASTER
  uint16_t received_data = 0;
  float packet[5];

  if (bluetooth_transfer.available())
  {
    //bluetooth_transfer.rxObj(second_acc, received_data);
    bluetooth_transfer.rxObj(packet, received_data);

    a -> x = packet[0];
    a -> y  = packet[1];
    a -> z  = packet[2];
    g -> y  = packet[3];
    g -> z  = packet[4];

  }
  #endif
}
#else
//////////////////////////////////////////////////////////////////////////////////
// SLAVE ONLY
//////////////////////////////////////////////////////////////////////////////////
void sendData(){
  

  //we pack it in a single array 

  float packet[5];

  packet[0] = acc.x;
  packet[1] = acc.y;
  packet[2] = acc.z;
  packet[3] = gyr.y;
  packet[4] = gyr.z;

  uint16_t sent_data = 0;
  sent_data = bluetooth_transfer.txObj(packet, sent_data); 
  bluetooth_transfer.sendData(sent_data);
  digitalWrite(DEBUG_LED_PIN, HIGH);
  delay(100);
  digitalWrite(DEBUG_LED_PIN, LOW);

}


#endif

//////////////////////////////////////////////////////////////////////////////////

void loop()
{

  imuManager.updateValues();
  acc = imuManager.getAcceleration();
  gyr = imuManager.getPitchRoll();

#ifdef MASTER
  receiveData(&second_acc, &second_gyr);
  printValues();

#else
  sendData();

#endif

  checkEvents();

}