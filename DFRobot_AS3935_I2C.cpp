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
#include "DFRobot_AS3935_I2C.h"

DFRobot_AS3935_I2C::DFRobot_AS3935_I2C(uint8_t irqx, uint8_t devAddx)
{
  devAdd = devAddx;
  irq = irqx;
  // initalize the IRQ pins
  pinMode(irq, INPUT);
}

DFRobot_AS3935_I2C::DFRobot_AS3935_I2C(uint8_t irqx)
{
  irq = irqx;
  pinMode(irq, INPUT);
}

void DFRobot_AS3935_I2C::setI2CAddress(uint8_t devAddx)
{
  if (devAddx == AS3935_ADD1){
  devAdd = devAddx;
  }else if (devAddx == AS3935_ADD2){
    devAdd = devAddx;
  }else{
    devAdd = AS3935_ADD3;
  }
}

uint8_t DFRobot_AS3935_I2C::singRegRead(uint8_t regAdd)
{
  uint8_t buf[1];
  readReg(regAdd, buf, 1);
  return buf[0];
}


void DFRobot_AS3935_I2C::singRegWrite(uint8_t regAdd, uint8_t dataMask, uint8_t regData)
{
  // start by reading original register data (only modifying what we need to)
  uint8_t origRegData = singRegRead(regAdd);
    
  // calculate new register data... 'delete' old targeted data, replace with new data
  // note: 'DataMask' must be bits targeted for replacement
  // add'l note: this function does NOT shift values into the proper place... they need to be there already
  uint8_t newRegData = ((origRegData & ~dataMask) | (regData & dataMask));
  uint8_t buf[1];
  buf[0] = newRegData;

  // finally, write the data to the register
  //I2c.write(devAdd, regAdd, newRegData);
  writeReg(regAdd, buf, 1);
}

int DFRobot_AS3935_I2C::defInit()
{
  return reset();            // reset registers to default
}

int DFRobot_AS3935_I2C::reset()
{
  // run PRESET_DEFAULT Direct Command to set all registers in default state
  //int error = I2c.write(devAdd, (uint8_t)0x3C, (uint8_t)0x96);
  uint8_t buf[1];
  buf[0] =  0x96;
  writeReg(0x3c, buf, 1);
  return 0;
}

void DFRobot_AS3935_I2C::calRCO()
{
  // run ALIB_RCO Direct Command to cal internal RCO
  //I2c.write(devAdd, (uint8_t)0x3D, (uint8_t)0x96);
  uint8_t buf[1];
  buf[0] =  0x96;
  writeReg(0x3D, buf, 1);
  delay(2);                // wait 2ms to complete
}

void DFRobot_AS3935_I2C::powerUp(void)
{
  // power-up sequence based on datasheet, pg 23/27
  // register 0x00, PWD bit: 0 (clears PWD)
  singRegWrite(0x00, 0x01, 0x00);
  calRCO();                        // run RCO cal cmd
  singRegWrite(0x08, 0x20, 0x20);    // set DISP_SRCO to 1
  delay(2);
  singRegWrite(0x08, 0x20, 0x00);    // set DISP_SRCO to 0
}

void DFRobot_AS3935_I2C::powerDown(void)
{
  // register 0x00, PWD bit: 0 (sets PWD)
  singRegWrite(0x00, 0x01, 0x01);
  Serial.println("AS3935 powered down");
}

void DFRobot_AS3935_I2C::disturberEn(void)
{
  // register 0x03, PWD bit: 5 (sets MASK_DIST)
  singRegWrite(0x03, 0x20, 0x00);
  Serial.println("disturber detection enabled");
}

void DFRobot_AS3935_I2C::disturberDis(void)
{
  // register 0x03, PWD bit: 5 (sets MASK_DIST)
  singRegWrite(0x03, 0x20, 0x20);
}

void DFRobot_AS3935_I2C::setIRQOutputSource(uint8_t irqSelect)
{
  // set interrupt source - what to display on IRQ pin
  // reg 0x08, bits 5 (TRCO), 6 (SRCO), 7 (LCO)
  // only one should be set at once, I think
  // 0 = NONE, 1 = TRCO, 2 = SRCO, 3 = LCO
  if(1 == irqSelect){
    singRegWrite(0x08, 0xE0, 0x20);            // set only TRCO bit
  }else if(2 == irqSelect){
    singRegWrite(0x08, 0xE0, 0x40);            // set only SRCO bit
  }else if(3 == irqSelect){
    singRegWrite(0x08, 0xE0, 0x80);            // set only LCO bit
  }else{
    singRegWrite(0x08, 0xE0, 0x00);            // clear IRQ pin display bits
  } 
}

void DFRobot_AS3935_I2C::setTuningCaps(uint8_t capVal)
{
  // Assume only numbers divisible by 8 (because that's all the chip supports)
  if(120 < capVal){    // cap_value out of range, assume highest capacitance
    singRegWrite(0x08, 0x0F, 0x0F);            // set capacitance bits to maximum
  }else{
    singRegWrite(0x08, 0x0F, (capVal >> 3));    // set capacitance bits
  }
}

uint8_t DFRobot_AS3935_I2C::getInterruptSrc(void)
{
  // definition of interrupt data on table 18 of datasheet
  // for this function:
  // 0 = unknown src, 1 = lightning detected, 2 = disturber, 3 = Noise level too high
  delay(10);                        // wait 3ms before reading (min 2ms per pg 22 of datasheet)
  uint8_t intSrc = (singRegRead(0x03) & 0x0F);    // read register, get rid of non-interrupt data
  if(0x08 == intSrc){
    return 1;                    // lightning caused interrupt
  }else if(0x04 == intSrc){
    return 2;                    // disturber detected
  }else if(0x01 == intSrc){
    return 3;                    // Noise level too high
  }else{
    return 0;
  }                    // interrupt result not expected 
}

uint8_t DFRobot_AS3935_I2C::getLightningDistKm(void)
{
  uint8_t strikeDist = (singRegRead(0x07) & 0x3F);    // read register, get rid of non-distance data
  return strikeDist;
}

uint32_t DFRobot_AS3935_I2C::getStrikeEnergyRaw(void)
{
  uint32_t nrgyRaw = ((singRegRead(0x06) & 0x1F) << 8);    // MMSB, shift 8  bits left, make room for MSB
  nrgyRaw |= singRegRead(0x05);                            // read MSB
  nrgyRaw <<= 8;                                            // shift 8 bits left, make room for LSB
  nrgyRaw |= singRegRead(0x04);                             // read LSB, add to others
  return nrgyRaw/16777;
}

uint8_t DFRobot_AS3935_I2C::setMinStrikes(uint8_t minStrk)
{
  // This function sets min strikes to the closest available number, rounding to the floor, 
  // where necessary, then returns the physical value that was set. Options are 1, 5, 9 or 16 strikes.
  // see pg 22 of the datasheet for more info (#strikes in 17 min)
  if(5 > minStrk){
    singRegWrite(0x02, 0x30, 0x00);
    return 1;
  }else if(9 > minStrk){
    singRegWrite(0x02, 0x30, 0x10);
    return 5;
  }else if(16 > minStrk){
    singRegWrite(0x02, 0x30, 0x20);
    return 9;
  }else{
    singRegWrite(0x02, 0x30, 0x30);
    return 16;
  }
}

void DFRobot_AS3935_I2C::setIndoors(void)
{
  // AFE settings addres 0x00, bits 5:1 (10010, based on datasheet, pg 19, table 15)
  // this is the default setting at power-up (AS3935 datasheet, table 9)
  singRegWrite(0x00, 0x3E, 0x24);
  Serial.println("set up for indoor operation");
}

void DFRobot_AS3935_I2C::setOutdoors(void)
{
  // AFE settings addres 0x00, bits 5:1 (01110, based on datasheet, pg 19, table 15)
  singRegWrite(0x00, 0x3E, 0x1C);
  Serial.println("set up for outdoor operation");
}

void DFRobot_AS3935_I2C::clearStatistics(void)
{
  // clear is accomplished by toggling CL_STAT bit 'high-low-high' (then set low to move on)
  singRegWrite(0x02, 0x40, 0x40);            // high
  singRegWrite(0x02, 0x40, 0x00);            // low
  singRegWrite(0x02, 0x40, 0x40);            // high
}

uint8_t DFRobot_AS3935_I2C::getNoiseFloorLvl(void)
{
  // NF settings addres 0x01, bits 6:4
  // default setting of 010 at startup (datasheet, table 9)
  uint8_t regRaw = singRegRead(0x01);        // read register 0x01
  return ((regRaw & 0x70) >> 4);            // should return value from 0-7, see table 16 for info
}

void DFRobot_AS3935_I2C::setNoiseFloorLvl(uint8_t nfSel)
{
  // NF settings addres 0x01, bits 6:4
  // default setting of 010 at startup (datasheet, table 9)
  if(7 >= nfSel){                                // nfSel within expected range
    singRegWrite(0x01, 0x70, ((nfSel & 0x07) << 4));
  }else{                                            // out of range, set to default (power-up value 010)
    singRegWrite(0x01, 0x70, 0x20);
  }
}

uint8_t DFRobot_AS3935_I2C::getWatchdogThreshold(void)
{
  // This function is used to read WDTH. It is used to increase robustness to disturbers,
  // though will make detection less efficient (see page 19, Fig 20 of datasheet)
  // WDTH register: add 0x01, bits 3:0
  // default value of 0001
  // values should only be between 0x00 and 0x0F (0 and 7)
  uint8_t regRaw = singRegRead(0x01);
  return (regRaw & 0x0F);
}

void DFRobot_AS3935_I2C::setWatchdogThreshold(uint8_t wdth)
{
  // This function is used to modify WDTH. It is used to increase robustness to disturbers,
  // though will make detection less efficient (see page 19, Fig 20 of datasheet)
  // WDTH register: add 0x01, bits 3:0
  // default value of 0010
  // values should only be between 0x00 and 0x0F (0 and 7)
  singRegWrite(0x01, 0x0F, (wdth & 0x0F));
}

uint8_t DFRobot_AS3935_I2C::getSpikeRejection(void)
{
  // This function is used to read SREJ (spike rejection). Similar to the Watchdog threshold,
  // it is used to make the system more robust to disturbers, though will make general detection
  // less efficient (see page 20-21, especially Fig 21 of datasheet)
  // SREJ register: add 0x02, bits 3:0
  // default value of 0010
  // values should only be between 0x00 and 0x0F (0 and 7)
  uint8_t regRaw = singRegRead(0x02);
  return (regRaw & 0x0F);
}

void DFRobot_AS3935_I2C::setSpikeRejection(uint8_t srej)
{
  // This function is used to modify SREJ (spike rejection). Similar to the Watchdog threshold,
  // it is used to make the system more robust to disturbers, though will make general detection
  // less efficient (see page 20-21, especially Fig 21 of datasheet)
  // WDTH register: add 0x02, bits 3:0
  // default value of 0010
  // values should only be between 0x00 and 0x0F (0 and 7)
  singRegWrite(0x02, 0x0F, (srej & 0x0F));
}

void DFRobot_AS3935_I2C::setLcoFdiv(uint8_t fdiv)
{
  // This function sets LCO_FDIV register. This is useful in the tuning of the antenna
  // LCO_FDIV register: add 0x03, bits 7:6
  // default value: 00
  // set 0, 1, 2 or 3 for ratios of 16, 32, 64 and 128, respectively. 
  // See pg 23, Table 20 for more info.
  singRegWrite(0x03, 0xC0, ((fdiv & 0x03) << 6));
}

void DFRobot_AS3935_I2C::printAllRegs(void)
{
  Serial.print("Reg 0x00: ");
  Serial.println(singRegRead(0x00));
  Serial.print("Reg 0x01: ");
  Serial.println(singRegRead(0x01));
  Serial.print("Reg 0x02: ");
  Serial.println(singRegRead(0x02));
  Serial.print("Reg 0x03: ");
  Serial.println(singRegRead(0x03));
  Serial.print("Reg 0x04: ");
  Serial.println(singRegRead(0x04));
  Serial.print("Reg 0x05: ");
  Serial.println(singRegRead(0x05));
  Serial.print("Reg 0x06: ");
  Serial.println(singRegRead(0x06));
  Serial.print("Reg 0x07: ");
  Serial.println(singRegRead(0x07));
  Serial.print("Reg 0x08: ");
  Serial.println(singRegRead(0x08));
  uint32_t nrgyVal = getStrikeEnergyRaw();
  Serial.println(nrgyVal);
}

void DFRobot_AS3935_I2C::manualCal(uint8_t capacitance, uint8_t location, uint8_t disturber)
{
  // start by powering up
  powerUp();
  // indoors/outdoors next...
  if(1 == location){                            // set outdoors if 1
    setOutdoors();
  }else{                                       // set indoors if anything but 1
    setIndoors();
  }
  // disturber cal
  if(0 == disturber){                           // disabled if 0              
    disturberDis();
  }else{                                       // enabled if anything but 0
    disturberEn();
  }
  setIRQOutputSource(0);
  delay(500);
  // capacitance first... directly write value here
  setTuningCaps(capacitance);
  Serial.println("AS3935 manual cal complete");
}
// a nice function would be to read the last 'x' strike data values.... 

uint8_t DFRobot_AS3935_I2C::begin(void)
{
  uint8_t buf[2];
  Wire.begin();
  Wire.setClock(400000);
  DBG("i2c init");
  if(readReg(0, buf, 2) == 2){
    DBG("return");
    return 0;
  }
  return 1;
}

void DFRobot_AS3935_I2C::writeReg(uint8_t reg, void *pBuf, size_t size)
{
  if(pBuf == NULL){
    DBG("pBuf ERROR!! :null pointer");
  }
  uint8_t *_pBuf = (uint8_t*)pBuf;
  Wire.beginTransmission(devAdd);
  Wire.write(reg);
  for(size_t i = 0; i < size; i++){
    Wire.write(_pBuf[i]);
  }
  Wire.endTransmission();
  DBG("i2c write");
}

size_t DFRobot_AS3935_I2C::readReg(uint8_t reg, void *pBuf, size_t size)
{
  if(pBuf == NULL){
    DBG("pBuf ERROR!!:null pointer");
    return 0;
  }
  uint8_t *_pBuf = (uint8_t*)pBuf;
  Wire.beginTransmission(devAdd);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(devAdd, size);
  for(size_t i = 0; i < size; i++){
    _pBuf[i] = Wire.read();
    DBG(_pBuf[i], HEX);
  }
  return size;
}

