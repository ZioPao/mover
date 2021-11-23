#include "header.h"

//#define LEFT

//Setup variables
bool isManagerConnectionEstabilished;
bool isBluetoothConnectionEstabilished;

//Components
IMUManager imuManager;

//Timer stuff
MiniTimer timerPrinting;
MiniTimer timerMovement;

//Movement variables
VectorFloat values;

void setup()
{

  while (!Serial)
    ; // wait for Leonardo enumeration, others continue immediately

  Serial.begin(38400);

#ifdef LEFT
  Serial.println("LEFT");
#else
  Serial.println("RIGHT");
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
  values.x = 0;
  values.y = 0;
  values.z = 0;
#endif

  Serial.println("Setup timers");
  //Timer setup
  timerPrinting.setup(TIMER_PRINTING);
  timerMovement.setup(TIMER_MOVEMENT);

  // Bluetooth setup

  //Serial1.begin(115200);
  //bluetooth_transfer.begin(Serial1, true);
  
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

void printValues()
{

  //filtering
  //a[1] \times yfilt[i-1] + b[0]
  //float x_filter = 0.9601172921934632 * x_filter_old + 0.019941353903268455 * acc.x + 0.019941353903268566 * x_og_old;

  /// X FILTERING

  //float b[] = {0.00066048, 0.00132097, 0.00066048};
  //float a[] = {1.92600086, -0.92864279};


  //float x_filter = 0.9601172921934632 * x_filter_old + 0.019941353903268455 * acc.x + 0.019941353903268566 * x_og_old;
  //x_filter_old = x_filter;
  //x_og_old = acc.x;


  // Y FILTERING
  //float y_filter = 0.9601172921934632 * y_filter_old + 0.019941353903268455 * acc.y + 0.019941353903268566 * y_og_old;
  //y_filter_old = y_filter;
  //y_og_old = acc.y;


  // Z FILTERING
  //float z_filter = 0.9601172921934632 * z_filter_old + 0.019941353903268455 * acc.z + 0.019941353903268566 * z_og_old;
  //z_filter_old = z_filter;
  //z_og_old = acc.z;


  if (values.x != 0){
    // TEST ONLY ACCELEROMETERS
    #ifdef LEFT
    String printed_string = "l,";
    #else
    String printed_string = "r,";
    #endif
    printed_string += String(values.x);    
    printed_string += ",";
    printed_string += String(values.y);
    printed_string += ",";
    printed_string += String(values.z);
    printed_string += ",";
    printed_string += String(millis());
    Serial.println(printed_string);
  }

 

}


//////////////////////////////////////////////////////////////////////////////////

void loop()
{

  values = imuManager.getValues();
  printValues();
  //checkEvents();
  


}