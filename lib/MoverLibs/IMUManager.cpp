#include "IMUManager.h"

// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================
volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high

void dmpDataReady() {
    mpuInterrupt = true;
}
// ================================================================
// ===                         Setup                            ===
// ================================================================
void IMUManager::setup(int16_t acc_x_offset, int16_t acc_y_offset, int16_t acc_z_offset, int16_t gyr_x_offset, int16_t gyr_y_offset, int16_t gyr_z_offset, int debug_led_pin)
{
    Wire.begin();
    Serial.begin(9600);
    mpu.initialize();
    
    mpu.setDHPFMode(1);
    mpu.setAccelerometerPowerOnDelay(3);
    mpu.setIntFreefallEnabled(false);
    mpu.setIntZeroMotionEnabled(true);
    mpu.setIntMotionEnabled(true);

    mpu.setMotionDetectionThreshold(1);
    mpu.setFreefallDetectionThreshold(1);
    mpu.setZeroMotionDetectionThreshold(2.2);     //1

    mpu.setMotionDetectionDuration(1);
    mpu.setFreefallDetectionDuration(1);
    mpu.setZeroMotionDetectionDuration(1);	    //1

    //Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
    //uint8_t dmpStatus = mpu.dmpInitialize();
    mpu.setXAccelOffset(acc_x_offset);
    mpu.setYAccelOffset(acc_y_offset);
    mpu.setZAccelOffset(acc_z_offset);

    mpu.setXGyroOffset(gyr_x_offset);
    mpu.setYGyroOffset(gyr_y_offset);
    mpu.setZGyroOffset(gyr_z_offset);

    // Calibration Time: generate offsets and calibrate our MPU6050
    mpu.CalibrateAccel(2);
    mpu.CalibrateGyro(2);

    this -> led_pin = debug_led_pin;
   
}

VectorFloat IMUManager::getValues()
{   

    int16_t ax, ay, az, gx, gy, gz;
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    VectorFloat temp;

    if (abs(gx/131.072) > 3){
        temp.x = gx/131.072;
        temp.y = gy/131.072;
        temp.z = gz/131.072;
        digitalWrite(this -> led_pin, HIGH);
        
    }
    else{
        temp.x = 0;         //automatically goes down or automatic filtering?
        temp.y = 0;
        temp.z = 0;
        digitalWrite(this -> led_pin, LOW);

    }
  


//   if (mpu.getIntMotionStatus() == 1){
//        Serial.println("Motion detected");
 //   }

//    if (mpu.getIntZeroMotionStatus() == 1){
//        Serial.println("Zero motion");
 //   }

    //temp.x = 0;         //automatically goes down or automatic filtering?
    //temp.y = 0;
    //temp.z = 0;
    return temp;

}

void IMUManager::setDmpReady(bool value)
{
    this->dmpReady = value;
}

MPU6050 IMUManager::getMPU(){
    return this -> mpu;
}
