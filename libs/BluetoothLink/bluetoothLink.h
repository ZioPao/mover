#include "Arduino.h"

void setupBluetooth();

//MASTER METHODS

bool checkBTConnectionMaster();

int16_t getBluetoothData();

//SLAVE METHODS

bool checkBTConnectionSlave();

void sendBluetoothData(int16_t value);