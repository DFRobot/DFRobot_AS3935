#ifndef DF_AS3935_I2C_h
#define DF_AS3935_I2C_h

#include "Arduino.h"
#include "avr/pgmspace.h"
#include "util/delay.h"
#include "stdlib.h"
#include "Lib_I2C.h"

// I2C address
#define AS3935_ADD1           0x01     // A0=high, A1=low
#define AS3935_ADD3           0x03     // A0=high, A1=high
#define AS3935_ADD2           0x02     // A0=low, A1=high

class DF_AS3935_I2C
{
 public:
	DF_AS3935_I2C(uint8_t IRQx, uint8_t DEVADDx);
	/*! Set i2c address */
	void AS3935_SetI2CAddress(uint8_t DEVADDx);
	/*! Manual calibration */
	void AS3935_ManualCal(uint8_t capacitance, uint8_t location, uint8_t disturber);
	/*! reset registers to default */
	void AS3935_DefInit(void);
	void AS3935_PowerUp(void);
	void AS3935_PowerDown(void);
	void AS3935_DisturberEn(void);
	void AS3935_DisturberDis(void);
	void AS3935_SetIRQ_Output_Source(uint8_t irq_select);
	void AS3935_SetTuningCaps(uint8_t cap_val);
	/*! 0 = unknown src, 1 = lightning detected, 2 = disturber, 3 = Noise level too high */
	uint8_t AS3935_GetInterruptSrc(void);
	/*! Get rid of non-distance data */
	uint8_t AS3935_GetLightningDistKm(void);
	/*! Get lightning energy intensity */
	uint32_t AS3935_GetStrikeEnergyRaw(void);
	uint8_t AS3935_SetMinStrikes(uint8_t min_strk);
	void AS3935_ClearStatistics(void);
	void AS3935_SetIndoors(void);
	void AS3935_SetOutdoors(void);
	uint8_t AS3935_GetNoiseFloorLvl(void);
	void AS3935_SetNoiseFloorLvl(uint8_t nf_sel);
	uint8_t AS3935_GetWatchdogThreshold(void);
	void AS3935_SetWatchdogThreshold(uint8_t wdth);
	uint8_t AS3935_GetSpikeRejection(void);
	void AS3935_SetSpikeRejection(uint8_t srej);
	void AS3935_SetLCO_FDIV(uint8_t fdiv);
	/*! View register data */
	void AS3935_PrintAllRegs(void);
	
 private:
	uint8_t _irq, _si, _devadd;
	uint8_t _sing_reg_read(uint8_t RegAdd);
	void _sing_reg_write(uint8_t RegAdd, uint8_t DataMask, uint8_t RegData);
	void _AS3935_Reset(void);
	void _CalRCO(void);
};

#endif




