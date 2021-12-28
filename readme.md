# DFRobot_AS3935

  * [中文版](./README_CN.md)
  
AS3935 Lightning Sensor can detect lightning and display the distance and intensity of the lightning without the disturbance of electric arc and noise.
It can be set as indoor or outdoor mode.

![Product Image](./resources/images/SEN0290.png)

## product link （https://www.dfrobot.com/product-1828.html）

    SKU：SEN0290

## Table of Contents
  
  * [Summary](#summary)
  * [Installation](#Installation)
  * [Methods](#Methods)
  * [Compatibility](#compatibility)
  * [History](#history)
  * [Credits](#credits)

## Summary

Input commands and read data from AS3935 modules

1. Lightning sensor warns of lightning storm activity within a radius of 40km 
2. Distance estimation to the head of the storm from overhead to 40km in 15 steps 
3. Detects both cloud-to-ground and intra-cloud(cloud-to-cloud) flashes 
4. Embedded man-made disturber rejection algorithm 
5. Programmable detection levels enable threshold setting for optimal controls 
6. Three i2c interfaces, switch freely to avoid site conflicts 

## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
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
  
```
## Compatibility

MCU                |  Work Well   |  Work Wrong  |  Untested   | Remarks |
------------------ | :----------: | :----------: | :---------: | :-----: |
Arduino uno        |       √      |              |             |         |
esp8266            |       √      |              |             |         |

## History

- 2021/09/30 - Version 1.0.2 released.
- 2021/08/24 - Version 1.0.1 released.
- 2019/09/28 - Version 1.0.0 released.
  
## Credits

Written by TangJie(jie.Tang@dfrobot.com), 2019. (Welcome to our [website](https://www.dfrobot.com/))

