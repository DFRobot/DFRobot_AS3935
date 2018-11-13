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
	/*! Set i2c address */
	void AS3935SetI2CAddress(uint8_t devAddx);
	/*! Manual calibration */
	void AS3935ManualCal(uint8_t capacitance, uint8_t location, uint8_t disturber);
	/*! reset registers to default */
	void AS3935DefInit(void);
	void AS3935PowerUp(void);
	void AS3935PowerDown(void);
	void AS3935DisturberEn(void);
	void AS3935DisturberDis(void);
	void AS3935SetIRQOutputSource(uint8_t irqSelect);
	void AS3935SetTuningCaps(uint8_t capVal);
	/*! 0 = unknown src, 1 = lightning detected, 2 = disturber, 3 = Noise level too high */
	uint8_t AS3935GetInterruptSrc(void);
	/*! Get rid of non-distance data */
	uint8_t AS3935GetLightningDistKm(void);
	/*! Get lightning energy intensity */
	uint32_t AS3935GetStrikeEnergyRaw(void);
	uint8_t AS3935SetMinStrikes(uint8_t minStrk);
	void AS3935ClearStatistics(void);
	void AS3935SetIndoors(void);
	void AS3935SetOutdoors(void);
	uint8_t AS3935GetNoiseFloorLvl(void);
	void AS3935SetNoiseFloorLvl(uint8_t nfSel);
	uint8_t AS3935GetWatchdogThreshold(void);
	void AS3935SetWatchdogThreshold(uint8_t wdth);
	uint8_t AS3935GetSpikeRejection(void);
	void AS3935SetSpikeRejection(uint8_t srej);
	void AS3935SetLcoFdiv(uint8_t fdiv);
	/*! View register data */
	void AS3935PrintAllRegs(void);
	
 private:
	uint8_t irq, devAdd;
	uint8_t singRegRead(uint8_t regAdd);
	void singRegWrite(uint8_t regAdd, uint8_t dataMask, uint8_t regData);
	void AS3935Reset(void);
	void calRCO(void);
};

#endif




