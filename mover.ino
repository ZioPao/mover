#include "header.h"

//Setup variables
bool isConnectionEstabilished;

void setup()
{

#ifdef MASTER_MOVER
  Serial.println("===========MASTER============");
#endif
#ifdef SLAVE_MOVER
  Serial.println("===========SLAVE============");
#endif

  isConnectionEstabilished = false;

  setupIMU();
  setupBluetooth();
  //setupGamepadEmulation();
}

/////////////////////////////////////////

void loop()
{

  if (!isConnectionEstabilished)
  {
    isConnectionEstabilished = checkBluetoothConnection();
  }
  else
  {
    VectorInt16 movement = getRealAcceleration();

#ifdef MASTER_MOVER

    //todo it should be another VectorInt16
    int16_t secondMovementY = getBluetoothData();
    if (secondMovementY != 0)
    {
      Serial.print("dato arrivato da slave:\t");
      Serial.print(secondMovementY);
      Serial.println("");
    }

    //manageMotion(movement.y);
    //manageMotion(secondMovementY);

#endif

#ifdef SLAVE_MOVER

    sendBluetoothData(movement.y);
#endif
  }

  /*STILL DEBUG STUFF*/
  digitalWrite(9, LOW);

  //printWorldAcceleration();

  // Wire.beginTransmission(2); // transmit to device #4

  //Serial.println(test.x);
  //Wire.write(2);
  //writeInt16(test.x);
  //Wire.endTransmission();    // stop transmitting

  //x++;
  //delay(500);
}
