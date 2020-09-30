void setupBluetooth()
{
  Serial1.begin(38400); // Default communication rate of the Bluetooth module
  Serial.println("Avviata comunicazione bluetooth");
}

int16_t getBluetoothData()
{
  //Reassembles the value in a 16 bit one
  if (Serial1.available() > 0)
  {
    byte a = Serial1.read();
    byte b = Serial1.read();
    return (int16_t)(a << 8 | b);
    //return Serial1.read();
  }
}

void sendBluetoothData(int16_t value)
{
  //Necessary to write 16 bits values

  byte byteArray[2];

  byteArray[0] = (value >> 8) & 0xFF;
  byteArray[1] = value & 0xFF;

  Serial1.write(byteArray, 2);
  //Serial.println("sent -> " + value);
}
