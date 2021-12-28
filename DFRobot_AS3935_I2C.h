
/*!
 * @file DFRobot_AS3935_I2C.h
 * @brief This is a library for AS3935_I2C from DFRobot
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [TangJie](jie.tang@dfrobot.com)
 * @version  V1.0.2
 * @date  2019-09-28
 * @url https://github.com/DFRobor/DFRobot_AS3935
 */

#ifndef DFRobot_AS3935_I2C_h
#define DFRobot_AS3935_I2C_h

#include "Arduino.h"
#include "stdlib.h"

#include "Wire.h"

// I2C address
#define AS3935_ADD1           0x01     ///< A0=high, A1=low
#define AS3935_ADD3           0x03     ///< A0=high, A1=high
#define AS3935_ADD2           0x02     ///< A0=low, A1=high

//#define ENABLE_DBG
#ifdef  ENABLE_DBG
#define DBG(...){Serial.print("[");Serial.print(__FUNCTION__);\
                 Serial.print("():");Serial.print(__LINE__);\
                 Serial.print("]");Serial.print(__VA_ARGS__); Serial.println("");}
#else
#define DBG(...)
#endif

class DFRobot_AS3935_I2C{
public:
 /**
  * @fn DFRobot_AS3935_I2C
  * @brief AS3935 object
  * @param irqx        irq pin
  * @param devAddx     i2c address
  * @return None
  */
  DFRobot_AS3935_I2C(uint8_t irqx, uint8_t devAddx);

 /**
  * @fn DFRobot_AS3935_I2C
  * @brief AS3935 object
  * @param irqx        irq pin
  * @return None
  */
  DFRobot_AS3935_I2C(uint8_t irqx);

 /**
  * @fn begin
  * @brief I2C init
  * @return uint8_t type, indicates the initialization status
  * @retval 0 succeed 
  * @retval 1 failure
  */
  uint8_t begin(void);

 /**
  * @fn setI2CAddress
  * @brief set i2c address
  * @param devAddx     i2c address  
  * @return None
  */
  void setI2CAddress(uint8_t devAddx);

 /**
  * @fn manualCal
  * @brief manual calibration 
  * @param capacitance    capacitance
  * @param location       location
  * @param disturber      disturber
  * @return None
  */
  void manualCal(uint8_t capacitance, uint8_t location, uint8_t disturber);

 /**
  * @fn defInit
  * @brief reset registers to default
  * @return int type,represents rest state
  * @retval 0 success
  */
  int defInit(void);

 /**
  * @fn disturberEn
  * @brief Disturber detection enabled
  * @return None
  */
  void disturberEn(void);

 /**
  * @fn disturberDis
  * @brief Disturber detection disenabled
  * @return None
  */
  void disturberDis(void);

 /**
  * @fn setIRQOutputSource
  * @brief Set interrupt source
  * @param irqSelect 0 = NONE, 1 = TRCO, 2 = SRCO, 3 = LCO
  * @return None
  */
  void setIRQOutputSource(uint8_t irqSelect);

  /**
   * @fn setTuningCaps
   * @brief set capacitance
   * @param capVal size
   * @return None
   */
  void setTuningCaps(uint8_t capVal);

 /**
  * @fn getInterruptSrc
  * @brief get interrupt source
  * @return uint8_t type，returns the interrupt source type
  * @retval 0    interrupt result not expected
  * @retval 1    lightning caused interrupt
  * @retval 2    disturber detected
  * @retval 3    Noise level too high
  */
  uint8_t getInterruptSrc(void);

 /**
  * @fn getLightningDistKm
  * @brief get lightning distance 
  * @return unit kilometer
  */
  uint8_t getLightningDistKm(void);

 /**
  * @fn getStrikeEnergyRaw
  * @brief get lightning energy intensity 
  * @return lightning energy intensity(0-1000)
  */
  uint32_t getStrikeEnergyRaw(void);

 /**
  * @fn setIndoors
  * @brief Set to the indoor model
  * @return None
  */
  void setIndoors(void);

 /**
  * @fn setOutdoors
  * @brief Set to the outdoor model
  * @return None
  */
  void setOutdoors(void);

 /**
  * @fn setOutdoors
  * @brief Get the noise level
  * @return Return noise level
  */
  uint8_t getNoiseFloorLvl(void);

 /**
  * @fn setNoiseFloorLvl
  * @brief Set the noise level
  * @param 0~7,More than 7 will use the default value:2
  * @return None
  */
  void setNoiseFloorLvl(uint8_t nfSel);

 /**
  * @fn getWatchdogThreshold
  * @brief read WDTH
  * @return Return interference level
  */
  uint8_t getWatchdogThreshold(void);

 /**
  * @fn setWatchdogThreshold
  * @brief Set an anti-interference rating
  * @param 0~7,More than 7 will use the default value:2
  * @return None
  */
  void setWatchdogThreshold(uint8_t wdth);

 /**
  * @fn getSpikeRejection
  * @brief read SREJ (spike rejection)
  * @return Return SREJ value
  */
  uint8_t getSpikeRejection(void);

 /**
  * @fn setSpikeRejection
  * @brief Modify SREJ (spike rejection)
  * @param 0~7,More than 7 will use the default value:2
  * @return None
  */
  void setSpikeRejection(uint8_t srej);

 /**
  * @fn setLcoFdiv
  * @brief Sets LCO_FDIV register
  * @param fdiv Set 0, 1, 2 or 3 for ratios of 16, 32, 64 and 128, respectively
  * @return None
  */
  void setLcoFdiv(uint8_t fdiv);

 /**
  * @fn printAllRegs
  * @brief view register data
  * @return None
  */
  void printAllRegs(void);

  /**
   * @fn powerUp
   * @brief Configure sensor
   * @return None
   */
  void powerUp(void);
    
private:
  uint8_t irq, devAdd;
  uint8_t singRegRead(uint8_t regAdd);
  void singRegWrite(uint8_t regAdd, uint8_t dataMask, uint8_t regData);
  int reset(void);
  void powerDown(void);
  void calRCO(void);
  void clearStatistics(void);
  uint8_t setMinStrikes(uint8_t minStrk);

 /**
  * @fn writeReg
  * @brief  Write register value through IIC bus
  * @param reg Register address 8bits
  * @param pBuf Storage cache to write data in
  * @param size The length of data to be written
  */
  void writeReg(uint8_t reg, void *pBuf, size_t size);
  //void writeRegNoStop(uint8_t reg, void *pBuf, size_t size)

 /**
  * @fn readReg
  * @brief Read register value through IIC bus
  * @param reg Register address 8bits
  * @param pBuf Read data storage cache
  * @param size Read the length of data
  * @return Return the read length
  */
  size_t readReg(uint8_t reg, void *pBuf, size_t size);
};
#endif




