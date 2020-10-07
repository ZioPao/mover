#include "bluetoothLink.h"

bool isDataWritten;
bool isConfirmed;
bool isMaster;

void setupBluetooth()
{
  Serial1.begin(38400); // Default communication rate of the Bluetooth module
  isDataWritten = false;
  isConfirmed = false;
  Serial.println("Avviata comunicazione bluetooth");
}

//MASTER METHODS

bool checkBTConnectionMaster()
{
  Serial1.write(1);

  while (Serial1.available() == 0)
  {
    //Serial.println(Serial1.available());
    Serial1.flush();
    Serial1.write(1);
    Serial.println("Waiting for BT connection");
  }

  //When the loop ends, it checks wheter or not it's a single bit
  if (Serial1.available() == 1)
  {
    Serial1.read();

    Serial.println("Connection confirmed");
    return true;
  }
  else
  {
    return false;
  }
}

int16_t getBluetoothData()
{

  //Check for start character
  while (Serial1.available() > 1 && Serial1.read() != '<')
    ;

  uint8_t buffer[3];
  int16_t result;
  Serial1.readBytesUntil('>', buffer, 3);

  Serial1.write('#');     //Confirmation

  return (int16_t)(buffer[0] << 8 | buffer[1]);
}
//SLAVE METHODS

bool checkBTConnectionSlave()
{
  while (Serial1.available() == 0)
  {
    //Serial.println(Serial1.available());

    Serial.println("Waiting for master");
  }

  if (Serial1.available() != 0)
  {
    Serial.println("Connection confirmed");
    Serial1.flush();  //flush
    Serial1.write(1); //sends confirmation
    delay(100);
    return true;
  }
  else
  {
    return false;
  }
}

void sendBluetoothData(int16_t value)
{
  isConfirmed = false;
  byte byteArray[4];

  byteArray[0] = '<';
  byteArray[1] = (value >> 8) & 0xFF;
  byteArray[2] = value & 0xFF;
  byteArray[3] = '>';

  Serial1.write(byteArray, 4);
  //isDataWritten = true;

  Serial.print("sent -> ");
  Serial.print(value);
  Serial.println("");

  while(!Serial1.available());

  if (Serial1.available() && Serial1.read() == '#'){
    Serial.println("Confirmation received");
    //delay(100);
    return;
  }
  else{
    Serial.println("No confirmation received");
    return;
  }
  /*
  while (!isConfirmed)
  {
    // wait for ready
    Serial.println(F("\nSend any character to check confirmation: "));
    while (Serial.available() && Serial.read())
      ; // empty buffer
    while (!Serial.available())
      ; // wait for data
    while (Serial.available() && Serial.read())
      ; // empty buffer again

    if (Serial1.available() && Serial1.read() == '>')
    {
      isConfirmed = true;
      Serial.println("Confirmed!");
    }
  }
  */
}
