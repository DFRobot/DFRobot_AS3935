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

1. test <br>
2. test <br>
3. test <br>

## Installation

Download the library ZIP file and unzip it to the Arduino folder of the library.<br>

## Methods

```C++

#include "DFRobot_AS3935_I2C.h"

/*
 * @brief AS3935 object
 *
 * @param IRQx        irq pin
 *        SIx         si pin
 *        DEVADDx     i2c address
 */
DF_AS3935_I2C(uint8_t IRQx, uint8_t SIx, uint8_t DEVADDx);

/*
 * @brief reset registers to default
 */
void AS3935_DefInit(void);

/*
 * @brief set i2c address
 *
 * @param DEVADDx     i2c address  
 */
void AS3935_SetI2CAddress(uint8_t DEVADDx);

/*
 * @brief manual calibration
 * 
 * @param capacitance    capacitance
 *        location       location
 *        disturber      disturber
 */
void AS3935_ManualCal(uint8_t capacitance, uint8_t location, uint8_t disturber);

/*
 * @brief view register data
 */
void AS3935_PrintAllRegs(void);

/*
 * @brief get interrupt source
 *
 * @return 0    interrupt result not expected
 *         1    lightning caused interrupt
 *         2    disturber detected
 *         3    Noise level too high
 */
uint8_t AS3935_GetInterruptSrc(void);

/*
 * @brief manual calibration
 * 
 * @param
 */
uint8_t AS3935_GetLightningDistKm(void);

/*
 * @brief get rid of non-distance data
 * 
 * @return Unit kilometer
 */
uint32_t AS3935_GetStrikeEnergyRaw(void);

```



## Compatibility

MCU                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno |       √      |             |            | 


## Credits

Written by DFRobot, 2018. (Welcome to our [website](https://www.dfrobot.com/))
