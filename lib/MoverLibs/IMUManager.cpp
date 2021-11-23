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
void IMUManager::setup(int16_t acc_x_offset, int16_t acc_y_offset, int16_t acc_z_offset, int16_t gyr_x_offset, int16_t gyr_y_offset, int16_t gyr_z_offset)
{
    Wire.begin();
    Serial.begin(115200);
    mpu.initialize();

    mpu.setAccelerometerPowerOnDelay(3);
    mpu.setIntZeroMotionEnabled(0);
    mpu.setDHPFMode(1);
    mpu.setMotionDetectionThreshold(2);
    mpu.setZeroMotionDetectionThreshold(1);
    mpu.setMotionDetectionDuration(5);
    mpu.setZeroMotionDetectionDuration(1);	

    Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
    uint8_t dmpStatus = mpu.dmpInitialize();

    if (dmpStatus == 0)
    {
        // offsets
        mpu.setXAccelOffset(acc_x_offset);
        mpu.setYAccelOffset(acc_y_offset);
        mpu.setZAccelOffset(acc_z_offset);

        mpu.setXGyroOffset(gyr_x_offset);
        mpu.setYGyroOffset(gyr_y_offset);
        mpu.setZGyroOffset(gyr_z_offset);

        // Calibration Time: generate offsets and calibrate our MPU6050
        mpu.CalibrateAccel(12);
        mpu.CalibrateGyro(12);


        mpu.setDMPEnabled(true);
        attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();
        packetSize = mpu.dmpGetFIFOPacketSize();
    
    }
}

VectorInt16 IMUManager::getValues()
{   
    if (dmpReady == false){
        return;
    }
    int16_t ax, ay, az, gx, gy, gz;

    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    VectorInt16 temp;

    if (mpu.getIntMotionStatus()){

        temp.x = gx;
        temp.y = gy;
        temp.z = gz;

    }
    else{
        temp.x = 0;         //automatically goes down or automatic filtering?
        temp.y = 0;
        temp.z = 0;
    }


    return temp;

}

void IMUManager::setDmpReady(bool value)
{
    this->dmpReady = value;
}

MPU6050 IMUManager::getMPU(){
    return this -> mpu;
}
