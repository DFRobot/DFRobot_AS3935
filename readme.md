# AS3935

AS3935 Lightning Sensor can detect lightning and display the distance and intensity of the lightning without the disturbance of electric arc and noise.<br>
It can be set as indoor or outdoor mode.<br>

## DFRobot_AS3934 Library for Arduino
---------------------------------------------------------
Provide a library faciltates operations in the as3935 modules.

## Table of Contents

* [Summary](#summary)
* [Feature](#feature)
* [Installation](#installation)
* [Methods](#methods)

* [Compatibility](#compatibility)
* [Credits](#credits)
<snippet>
<content>

## Summary

Input commands and read data from AS3935 modules

## Feature

1. Lightning sensor warns of lightning storm activity within a radius of 40km <br>
2. Distance estimation to the head of the storm from overhead to 40km in 15 steps <br>
3. Detects both cloud-to-ground and intra-cloud(cloud-to-cloud) flashes <br>
4. Embedded man-made disturber rejection algorithm <br>
5. Programmable detection levels enable threshold setting for optimal controls <br>
6. Three i2c interfaces, switch freely to avoid site conflicts <br>

## Installation

Download the library ZIP file and unzip it to the Arduino folder of the library.<br>

## Methods

```C++

#include "DFRobot_AS3935_I2C.h"

/*
 * @brief AS3935 object
 *
 * @param irqx        irq pin
 *        devAddx     i2c address
 */
DFRobot_AS3935_I2C(uint8_t irqx, uint8_t devAddx);

/*
 * @brief AS3935 object
 *
 * @param irqx        irq pin
 */
DFRobot_AS3935_I2C(uint8_t irqx);

/*
 * @brief reset registers to default
 *
 * @return 0 success
 */
int defInit(void);

/*
 * @brief set i2c address
 *
 * @param devAddx     i2c address  
 */
void setI2CAddress(uint8_t devAddx);

/*
 * @brief manual calibration
 * 
 * @param capacitance    capacitance
 *        location       location
 *        disturber      disturber
 */
void manualCal(uint8_t capacitance, uint8_t location, uint8_t disturber);

/*
 * @brief view register data
 */
void printAllRegs(void);

/*
 * @brief get interrupt source
 *
 * @return 0    interrupt result not expected
 *         1    lightning caused interrupt
 *         2    disturber detected
 *         3    Noise level too high
 */
uint8_t getInterruptSrc(void);

/*
 * @brief get lightning distance
 * 
 * @return unit kilometer
 */
uint8_t getLightningDistKm(void);

/*
 * @brief get lightning energy intensity
 * 
 * @return lightning energy intensity(0-1000)
 */
uint32_t getStrikeEnergyRaw(void);

/*
 * @brief Set to the outdoor model
 */
void setOutdoors(void);

/*
 * @brief Set to the indoor model
 */
void setIndoors(void);

/*
 * @brief Disturber detection enabled
 */
void disturberEn(void);

/*
 * @brief Disturber detection disenabled
 */
void disturberDis(void);

/*
 * @brief Sets LCO_FDIV register
 *
 * @param fdiv Set 0, 1, 2 or 3 for ratios of 16, 32, 64 and 128, respectively
 */
void setLcoFdiv(uint8_t fdiv);

/*
 * @brief Set interrupt source
 *
 * @param irqSelect 0 = NONE, 1 = TRCO, 2 = SRCO, 3 = LCO
 */
void setIRQOutputSource(uint8_t irqSelect);

/*
 * @brief Set the noise level
 *
 * @param 0~7,More than 7 will use the default value:2
 */
void setNoiseFloorLvl(uint8_t nfSel);

/*
 * @brief Get the noise level
 *
 * @return 0~7
 */
uint8_t getNoiseFloorLvl(void);

/*
 * @brief Set an anti-interference rating
 *
 * @param 0~7,More than 7 will use the default value:1
 */
void setWatchdogThreshold(uint8_t wdth);

/*
 * @brief read WDTH
 *
 * @return 0~7
 */
uint8_t getWatchdogThreshold(void);

/*
 * @brief Modify SREJ (spike rejection)
 *
 * @param 0~7,More than 7 will use the default value:2
 */
void setSpikeRejection(uint8_t srej);

/*
 * @brief read SREJ (spike rejection)
 *
 * @return 0~7
 */
uint8_t getSpikeRejection(void);

```



## Compatibility

MCU                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno |       √      |             |            | 


## Credits

Written by DFRobot_JH, 2018. (Welcome to our [website](https://www.dfrobot.com/))
