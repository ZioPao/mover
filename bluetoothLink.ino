bool is_data_written;


void setupBluetooth()
{
  Serial1.begin(38400); // Default communication rate of the Bluetooth module
  is_data_written = false;
  Serial.println("Avviata comunicazione bluetooth");
}

int16_t getBluetoothData()
{
  
  //Serial.print("Serial1: ");
  //Serial.print(Serial1.available());
  //Serial.println("");

  
  //Reassembles the value in a 16 bit one
  if (Serial1.available() == 2)
  {

    byte a = Serial1.read();
    byte b = Serial1.read();
    
    //Send confirmation
    Serial1.write(1);
    
    return (int16_t)(a << 8 | b);
    //return Serial1.read();
  }
  else
    return 0;
}

void sendBluetoothData(int16_t value)
{
  //Necessary to write 16 bits values
  if (Serial1.available()  > 0){
    Serial1.read();   //flush
    Serial.println("Flush");

    is_data_written = false;
  }

  if (is_data_written == false){
      byte byteArray[2];

  byteArray[0] = (value >> 8) & 0xFF;
  byteArray[1] = value & 0xFF;

  Serial1.write(byteArray, 2);
  is_data_written = true;
  
  Serial.print("sent -> ");
  Serial.print(value);
  Serial.println("");
  }


}
