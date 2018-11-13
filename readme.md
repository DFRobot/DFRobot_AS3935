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
 * @brief reset registers to default
 */
void AS3935DefInit(void);

/*
 * @brief set i2c address
 *
 * @param devAddx     i2c address  
 */
void AS3935SetI2CAddress(uint8_t devAddx);

/*
 * @brief manual calibration
 * 
 * @param capacitance    capacitance
 *        location       location
 *        disturber      disturber
 */
void AS3935ManualCal(uint8_t capacitance, uint8_t location, uint8_t disturber);

/*
 * @brief view register data
 */
void AS3935PrintAllRegs(void);

/*
 * @brief get interrupt source
 *
 * @return 0    interrupt result not expected
 *         1    lightning caused interrupt
 *         2    disturber detected
 *         3    Noise level too high
 */
uint8_t AS3935GetInterruptSrc(void);

/*
 * @brief get lightning distance
 * 
 * @return unit kilometer
 */
uint8_t AS3935GetLightningDistKm(void);

/*
 * @brief get lightning energy intensity
 * 
 * @return lightning energy intensity(0-1000)
 */
uint32_t AS3935GetStrikeEnergyRaw(void);

/*
 * @brief Set to the outdoor model
 */
void AS3935SetOutdoors(void);

/*
 * @brief Set to the indoor model
 */
void AS3935SetIndoors(void);

/*
 * @brief Print all register values
 */
void AS3935PrintAllRegs(void);

/*
 * @brief Disturber detection enabled
 */
void DFRobot_AS3935_I2C::AS3935DisturberEn(void);

/*
 * @brief Disturber detection disenabled
 */
void DFRobot_AS3935_I2C::AS3935DisturberDis(void);

```



## Compatibility

MCU                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno |       √      |             |            | 


## Credits

Written by DFRobot_JH, 2018. (Welcome to our [website](https://www.dfrobot.com/))
