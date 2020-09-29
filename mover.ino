#include "I2Cdev.h"
#include "helper_3dmath.h"

void setup()
{

  setupIMU();
  setupGamepadEmulation();
}

void loop()
{
  VectorInt16 accel = getAcceleration();
  checkMotion(accel);
}