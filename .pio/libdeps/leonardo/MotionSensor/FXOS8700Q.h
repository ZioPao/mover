#ifndef FXOSDRIVER__H
#define FXOSDRIVER__H

/*==========Dependencies ============*/
#include "MotionSensor.h"
#include "mbed.h"

/*========I2C Connection & ID ========*/
#define FXOS8700CQ_SLAVE_ADDR0 (0x1E<<1) // with pins SA0=0, SA1=0
#define FXOS8700CQ_SLAVE_ADDR1 (0x1D<<1) // with pins SA0=1, SA1=0
#define FXOS8700CQ_SLAVE_ADDR2 (0x1C<<1) // with pins SA0=0, SA1=1
#define FXOS8700CQ_SLAVE_ADDR3 (0x1F<<1) // with pins SA0=1, SA1=1
#define FXOS8700Q_WHOAMI_VAL 0xC7  // Device ID

/*=========FXOS8700Q REGISTERS =========*/
#define FXOS8700Q_STATUS 0x00       // R: DR_STATUS or F_STATUS
#define FXOS8700Q_OUT_X_MSB 0x01    // R: Accel 14-bit [7:0] X direc
#define FXOS8700Q_OUT_Y_MSB 0x03    // R: Accel 14-bit [7:0] Y direc
#define FXOS8700Q_OUT_Z_MSB 0x05    // R: Accel 14-bit [7:0] Z direc
#define FXOS8700Q_WHOAMI 0x0D
#define FXOS8700Q_XYZ_DATA_CFG 0x0E // RW: filter: hpf_out, scale: fs[1:0]

#define FXOS8700Q_A_FFMT_CFG 0x15   // RW: motion function configuration
// format: 0 / 1
/* 7: latch disable/enable (a_ffmt_ele)
   6: freefall / motion    (a_ffmt_oae)
   5: event detection / raise flag Z-axis (a_ffmt_zefe)
   4: event detection / raise flag Y-axis (a_ffmt_yefe)
   3: event detectuin / raise flag X-axis (a_ffmt_xefe)
*/

#define FXOS8700Q_A_FFMT_SRC 0x16   // R: motion event source register
/* 7: a_ffmt_ea set to 1 when A_FFMT_CFG flags True
Used with CTRL_REG4 and CTRL_REG5 to generate motion interrupt
 */
#define FXOS8700Q_A_FFMT_THS 0x17   // RW: motion threshold register
#define FXOS8700Q_A_FFMT_COUNT 0x18 /* RW: a_ffmt_count[7:0] counts required for detection of motion event */

#define FXOS8700Q_CTRL_REG1 0x2A    // RW: ASL_Rate, ODR, OSR, Operating mode
/* 7-6: aslp+Rate[1:0] sleep/auto-wake freq
   5-3: dr[2:0] Output data rate
     2: Inoise  normal / reduced noise
     1: f_read  normal / fast-read
     0: active  standby / active
*/      
#define FXOS8700Q_CTRL_REG2 0x2B    // RW: Self-test, reset, OSR and sleep mode
/* 7: st self test en / dis
   6: rst device reset dis / en
 4-3: smods[1:0] sleep mode power and noise for acceleration measurements
   2: slpe auto-sleep not en / auto-sleep enabled
 1-0: mods[1:0] wake mode power and noise for accel measurements
*/
#define FXOS8700Q_CTRL_REG3 0X2C    // RW: sleep mode interrupt, push-pull configs
 /* 3: wake_ffmt motion function disabled in sleep / enabled
    2: wake_a_vecm accel vec-mag f disabled in sleep / enabled
    1: ipol polarity of INT1 and INT2 active low / active high
    0: pp_od push-pull / open drain
*/

#define FXOS8700Q_CTRL_REG4 0X2D    // RW: Interrupt enable
/*  7: int_en_aslp auto-sleep interrupt disabled / enabled
    2: int_en_ffmt motion interrupt disabled / en
    1: int_en_a_vecm accel vec-mag interrupt disabled / en
*/
#define FXOS8700Q_CTRL_REG5 0x2E    // RW: Interrupt routing config
/*  7: int_cfg_aslp INT2 pin / INT1 pin
    2: int_cfg_ffmt
    1: int_cfg_vecm
*/

#define FXOS8700Q_M_OUT_X_MSB 0x33
#define FXOS8700Q_M_OUT_Y_MSB 0x35
#define FXOS8700Q_M_OUT_Z_MSB 0x37

#define FXOS8700Q_M_CTRL_REG1 0x5B
#define FXOS8700Q_M_CTRL_REG2 0x5C

#define FXOS8700Q_A_VECM_CFG 0x5F      // RW: accel vec-magnitude config
/*  6: a_vecm_ele real time update & clear / latched interrupt flag
    5: a_vecm_initm control bit for ref values current / registered refs
    4: a_vecm_updm updates ref values w current / loads saved from reg
    3: a_vecm_en function disabled / enabled
    Note: vec-mag function can only perform with max of ODR of 400 Hz
*/
#define FXOS8700Q_A_VECM_THS_MSB 0x60  // RW: a_vecm_ths[12:8]

#define FXOS8700Q_A_VECM_CNT 0x62      // RW: [7:0] - debouncer time period

#define FXOS8700Q_A_FFMT_THS_X_MSB 0x73 // RW: [12:6] X-axis accel thresh
#define FXOS8700Q_A_FFMT_THS_Y_MSB 0x75 // RW: [12:6] Y-axis accel threshold
#define FXOS8700Q_A_FFMT_THS_Z_MSB 0x77 // RW: [12:6] Z-axis accel threshold

/*============Class Defintions ===============*/
class FXOS8700Q_acc : public MotionSensor
{
public:
    FXOS8700Q_acc(PinName sda, PinName scl, int addr);

  /**
  * FXOS8700Q destructor
  */
    ~FXOS8700Q_acc();

    void enable(void);
    void disable(void);
    uint32_t sampleRate(uint32_t frequency);
    uint32_t whoAmI(void);
    uint32_t dataReady(void);
    void getX(int16_t * x);
    void getY(int16_t * y);
    void getZ(int16_t * z);
    void getX(float * x);
    void getY(float * y);
    void getZ(float * z);
    void getAxis(MotionSensorDataCounts &data);
    void getAxis(MotionSensorDataUnits &data);
    uint8_t getStatus(void);
    uint8_t getIntSource(void);
  
  void readRegs(int addr, uint8_t * data, int len);
  
private:
  I2C m_i2c;
  int m_addr;

  void writeRegs(uint8_t * data, int len);
  int16_t getAccAxis(uint8_t addr);

};

class FXOS8700Q_mag : public MotionSensor
{
public:
  FXOS8700Q_mag(PinName sda, PinName scl, int addr);

  /**
  * FXOS8700Q destructor
  */
  ~FXOS8700Q_mag();

    void enable(void);
    void disable(void);
    uint32_t sampleRate(uint32_t fequency);
    uint32_t whoAmI(void);
    uint32_t dataReady(void);
    void getX(int16_t * x);
    void getY(int16_t * y);
    void getZ(int16_t * z);
    void getX(float * x);
    void getY(float * y);
    void getZ(float * z);
    void getAxis(MotionSensorDataCounts &data);
    void getAxis(MotionSensorDataUnits &data);
  
  void readRegs(int addr, uint8_t * data, int len);
  
private:
  I2C m_i2c;
  int m_addr;
  char sbuf[12];
  int sstatus;
  
  void writeRegs(uint8_t * data, int len);
  int16_t getAccAxis(uint8_t addr);

};



#endif