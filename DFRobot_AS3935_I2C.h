#ifndef DFRobot_AS3935_I2C_h
#define DFRobot_AS3935_I2C_h

#include "Arduino.h"
#include "avr/pgmspace.h"
#include "util/delay.h"
#include "stdlib.h"
#include "Lib_I2C.h"

// I2C address
#define AS3935_ADD1           0x01     // A0=high, A1=low
#define AS3935_ADD3           0x03     // A0=high, A1=high
#define AS3935_ADD2           0x02     // A0=low, A1=high

class DFRobot_AS3935_I2C
{
 public:
    DFRobot_AS3935_I2C(uint8_t irqx, uint8_t devAddx);
    DFRobot_AS3935_I2C(uint8_t irqx);
    /*! Set i2c address */
    void setI2CAddress(uint8_t devAddx);
    /*! Manual calibration */
    void manualCal(uint8_t capacitance, uint8_t location, uint8_t disturber);
    /*! reset registers to default */
    int defInit(void);
    void disturberEn(void);
    void disturberDis(void);
    void setIRQOutputSource(uint8_t irqSelect);
    void setTuningCaps(uint8_t capVal);
    /*! 0 = unknown src, 1 = lightning detected, 2 = disturber, 3 = Noise level too high */
    uint8_t getInterruptSrc(void);
    /*! Get rid of non-distance data */
    uint8_t getLightningDistKm(void);
    /*! Get lightning energy intensity */
    uint32_t getStrikeEnergyRaw(void);
    uint8_t setMinStrikes(uint8_t minStrk);
    void clearStatistics(void);
    void setIndoors(void);
    void setOutdoors(void);
    uint8_t getNoiseFloorLvl(void);
    void setNoiseFloorLvl(uint8_t nfSel);
    uint8_t getWatchdogThreshold(void);
    void setWatchdogThreshold(uint8_t wdth);
    uint8_t getSpikeRejection(void);
    void setSpikeRejection(uint8_t srej);
    void setLcoFdiv(uint8_t fdiv);
    /*! View register data */
    void printAllRegs(void);
    void powerUp(void);
    
 private:
    uint8_t irq, devAdd;
    uint8_t singRegRead(uint8_t regAdd);
    void singRegWrite(uint8_t regAdd, uint8_t dataMask, uint8_t regData);
    int reset(void);
    void powerDown(void);
    void calRCO(void);
};

#endif




