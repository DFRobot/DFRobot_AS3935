'''!
  @file DFRobot_AS3935_Lib.py
  @brief Define the DFRobot_AS3935 class infrastructure, the implementation of the base method
  @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license     The MIT License (MIT)
  @author      TangJie(jie.tamg@dfrobot.com)
  @version  V1.0.2
  @date  2021-9-28
  @url https://github.com/DFRobot/DFRobot_AS3935
'''
import time
import smbus

class DFRobot_AS3935:
  def __init__(self, address, bus = 1):
    self.address = address
    self.i2cbus = smbus.SMBus(bus)

  def write_byte(self, register, value):
    try:
      self.i2cbus.write_byte_data(self.address, register, value)
      return 1
    except:
      return 0

  def read_data(self, register):
    self.register = self.i2cbus.read_i2c_block_data(self.address, register)

  '''!
    @brief Configure sensor 
    @param capacitance Antenna tuning capcitance (must be integer multiple of 8, 8 - 120 pf)
    @param location    Indoor/outdoor mode selection
    @param disturber   Enable/disable disturber detection
  '''
  def manual_cal(self, capacitance, location, disturber):
    self.powerUp()
    if location == 1:
      self.setIndoors()
    else:
      self.setOutdoors()

    if disturber == 0:
      self.disturberDis()
    else:
      self.disturberEn()

    self.setIrqOutputSource(0)
    time.sleep(0.5)
    self.setTuningCaps(capacitance)

  def set_tuning_caps(self, capVal):
      #Assume only numbers divisible by 8 (because that's all the chip supports)
      if capVal > 120: #cap_value out of range, assume highest capacitance
          self.singRegWrite(0x08, 0x0F, 0x0F) #set capacitance bits to maximum
      else:
          self.singRegWrite(0x08, 0x0F, capVal >> 3) #set capacitance bits
      self.singRegRead(0x08)
      #print('capacitance set to 8x%d'%(self.register[0] & 0x0F))

  def power_up(self):
    #register 0x00, PWD bit: 0 (clears PWD)
    self.singRegWrite(0x00, 0x01, 0x00)
    self.calRCO() #run RCO cal cmd
    self.singRegWrite(0x08, 0x20, 0x20) #set DISP_SRCO to 1
    time.sleep(0.002)
    self.singRegWrite(0x08, 0x20, 0x00) #set DISP_SRCO to 0

  def power_down(self):
    #register 0x00, PWD bit: 0 (sets PWD)
    self.singRegWrite(0x00, 0x01, 0x01)

  def cal_RCO(self):
    self.writeByte(0x3D, 0x96)
    time.sleep(0.002)

  '''!
    @brief Disturber detection enabled
  '''
  def set_indoors(self):
    self.singRegWrite(0x00, 0x3E, 0x24)
    print("set to indoors model")

  '''!
    @brief Set to the outdoor model
  '''
  def set_outdoors(self):
    self.singRegWrite(0x00, 0x3E, 0x1C)
    print("set to outdoors model")

  '''!
    @brief Disturber detection disenabled
  '''
  def disturber_dis(self):
    #register 0x03, PWD bit: 5 (sets MASK_DIST)
    self.singRegWrite(0x03, 0x20, 0x20)
    print("disenable disturber detection")

  '''!
    @brief Disturber detection enabled
  '''
  def disturber_en(self):
    #register 0x03, PWD bit: 5 (sets MASK_DIST)
    self.singRegWrite(0x03, 0x20, 0x00)
    print("enable disturber detection")

  def sing_reg_write(self, regAdd, dataMask, regData):
    #start by reading original register data (only modifying what we need to)
    self.singRegRead(regAdd)
    #calculate new register data... 'delete' old targeted data, replace with new data
    #note: 'dataMask' must be bits targeted for replacement
    #add'l note: this function does NOT shift values into the proper place... they need to be there already
    newRegData = (self.register[0] & ~dataMask)|(regData & dataMask)
    #finally, write the data to the register
    self.writeByte(regAdd, newRegData)
    #print('wrt: %02x'%newRegData)
    self.singRegRead(regAdd)
    #print('Act: %02x'%self.register[0])

  def sing_reg_read(self,regAdd):
    self.readData(regAdd)

  '''!
    @brief Get mid-range type
    @return Return to interrupted state
    @retval  0  Unknown src
    @retval  1  Lightning detected
    @retval  2  Disturber
    @retval  3  Noise level too high
  '''
  def get_interrupt_src(self):
    #definition of interrupt data on table 18 of datasheet
    #for this function:
    #0 = unknown src, 1 = lightning detected, 2 = disturber, 3 = Noise level too high
    time.sleep(0.03) #wait 3ms before reading (min 2ms per pg 22 of datasheet)
    self.singRegRead(0x03) #read register, get rid of non-interrupt data
    intSrc = self.register[0]&0x0F
    if intSrc == 0x08:
      return 1 #lightning caused interrupt
    elif intSrc == 0x04:
      return 2 #disturber detected
    elif intSrc == 0x01:
      return 3 #Noise level too high
    else:
      return 0 #interrupt result not expected

  '''!
    @brief Sensor reset
  '''
  def reset(self):
    err = self.writeByte(0x3C, 0x96)
    time.sleep(0.002) #wait 2ms to complete
    return err

  '''!
    @brief Sets LCO_FDIV register
    @param fdiv Set 0, 1, 2 or 3 for ratios of 16, 32, 64 and 128, respectively
  '''
  def set_lco_fdiv(self,fdiv):
    self.singRegWrite(0x03, 0xC0, (fdiv & 0x03) << 6)

  '''!
    @brief Set interrupt source
    @param irqSelect 0 = NONE, 1 = TRCO, 2 = SRCO, 3 = LCO
  '''
  def set_irq_output_source(self, irqSelect):
    #set interrupt source - what to display on IRQ pin
    #reg 0x08, bits 5 (TRCO), 6 (SRCO), 7 (LCO)
    #only one should be set at once, I think
    #0 = NONE, 1 = TRCO, 2 = SRCO, 3 = LCO
    if irqSelect == 1:
      self.singRegWrite(0x08, 0xE0, 0x20) #set only TRCO bit
    elif irqSelect == 2:
      self.singRegWrite(0x08, 0xE0, 0x40) #set only SRCO bit
    elif irqSelect == 3:
      self.singRegWrite(0x08, 0xE0, 0x80) #set only SRCO bit
    else:
      self.singRegWrite(0x08, 0xE0, 0x00) #clear IRQ pin display bits

  '''！
    @brief get lightning distance 
    @return unit kilometer
  '''
  def get_lightning_distKm(self):
    self.singRegRead(0x07) #read register, get rid of non-distance data
    return self.register[0]&0x3F

  '''！
    @brief get lightning energy intensity 
    @return lightning energy intensity(0-1000)
  '''
  def get_strike_energy_raw(self):
    self.singRegRead(0x06) #MMSB, shift 8  bits left, make room for MSB
    nrgyRaw = (self.register[0]&0x1F) << 8
    self.singRegRead(0x05) #read MSB
    nrgyRaw |= self.register[0]
    nrgyRaw <<= 8 #shift 8 bits left, make room for LSB
    self.singRegRead(0x04) #read LSB, add to others
    nrgyRaw |= self.register[0]
        
    return nrgyRaw/16777

  def set_min_strikes(self, minStrk):
    #This function sets min strikes to the closest available number, rounding to the floor,
    #where necessary, then returns the physical value that was set. Options are 1, 5, 9 or 16 strikes.
    if minStrk < 5:
      self.singRegWrite(0x02, 0x30, 0x00)
      return 1
    elif minStrk < 9:
      self.singRegWrite(0x02, 0x30, 0x10)
      return 5
    elif minStrk < 16:
      self.singRegWrite(0x02, 0x30, 0x20)
      return 9
    else:
      self.singRegWrite(0x02, 0x30, 0x30)
      return 16

  def clear_statistics(self):
    #clear is accomplished by toggling CL_STAT bit 'high-low-high' (then set low to move on)
    self.singRegWrite(0x02, 0x40, 0x40) #high
    self.singRegWrite(0x02, 0x40, 0x00) #low
    self.singRegWrite(0x02, 0x40, 0x40) #high

  '''！
    @brief Get the noise level
    @return 0~7
  '''
  def get_noise_floor_lv1(self):
    #NF settings addres 0x01, bits 6:4
    #default setting of 010 at startup (datasheet, table 9)
    self.singRegRead(0x01) #read register 0x01
    return (self.register[0] & 0x70) >> 4 #should return value from 0-7, see table 16 for info
    
  '''！
    @brief Set the noise level
    @param 0~7,More than 7 will use the default value:2
  '''
  def set_noise_floor_lv1(self, nfSel):
    #NF settings addres 0x01, bits 6:4
    #default setting of 010 at startup (datasheet, table 9)
    if nfSel <= 7: #nfSel within expected range
      self.singRegWrite(0x01, 0x70, (nfSel & 0x07) << 4)
    else:       #out of range, set to default (power-up value 010)
      self.singRegWrite(0x01, 0x70, 0x20)

  '''！
    @brief read WDTH
    @return Return interference level
  '''        
  def get_watchdog_threshold(self):
    #This function is used to read WDTH. It is used to increase robustness to disturbers,
    #though will make detection less efficient (see page 19, Fig 20 of datasheet)
    #WDTH register: add 0x01, bits 3:0
    #default value of 0010
    #values should only be between 0x00 and 0x0F (0 and 7)
    self.singRegRead(0x01)
    return self.register[0] & 0x0F

  '''！
    @brief Set an anti-interference rating
    @param 0~7,More than 7 will use the default value:2
  '''
  def set_watchdog_threshold(self, wdth):
    #This function is used to modify WDTH. It is used to increase robustness to disturbers,
    #though will make detection less efficient (see page 19, Fig 20 of datasheet)
    #WDTH register: add 0x01, bits 3:0
    #default value of 0010
    #values should only be between 0x00 and 0x0F (0 and 7)
    self.singRegWrite(0x01, 0x0F, wdth & 0x0F)

  '''！
    @brief read SREJ (spike rejection)
    @return Return SREJ value
  '''
  def get_spike_rejection(self):
    #This function is used to read SREJ (spike rejection). Similar to the Watchdog threshold,
    #it is used to make the system more robust to disturbers, though will make general detection
    #less efficient (see page 20-21, especially Fig 21 of datasheet)
    #SREJ register: add 0x02, bits 3:0
    #default value of 0010
    #values should only be between 0x00 and 0x0F (0 and 7)
    self.singRegRead(0x02)
    return self.register[0] & 0x0F

  '''！
    @brief Modify SREJ (spike rejection)
    @param 0~7,More than 7 will use the default value:2
  '''
  def set_spike_rejection(self, srej):
    #This function is used to modify SREJ (spike rejection). Similar to the Watchdog threshold,
    #it is used to make the system more robust to disturbers, though will make general detection
    #less efficient (see page 20-21, especially Fig 21 of datasheet)
    #WDTH register: add 0x02, bits 3:0
    #default value of 0010
    #values should only be between 0x00 and 0x0F (0 and 7)
    self.singRegWrite(0x02, 0x0F, srej & 0x0F)
        
  def print_all_regs(self):
    self.singRegRead(0x00)
    print("Reg 0x00: %02x"%self.register[0])
    self.singRegRead(0x01)
    print("Reg 0x01: %02x"%self.register[0])
    self.singRegRead(0x02)
    print("Reg 0x02: %02x"%self.register[0])
    self.singRegRead(0x03)
    print("Reg 0x03: %02x"%self.register[0])
    self.singRegRead(0x04)
    print("Reg 0x04: %02x"%self.register[0])
    self.singRegRead(0x05)
    print("Reg 0x05: %02x"%self.register[0])
    self.singRegRead(0x06)
    print("Reg 0x06: %02x"%self.register[0])
    self.singRegRead(0x07)
    print("Reg 0x07: %02x"%self.register[0])
    self.singRegRead(0x08)
    print("Reg 0x08: %02x"%self.register[0])



