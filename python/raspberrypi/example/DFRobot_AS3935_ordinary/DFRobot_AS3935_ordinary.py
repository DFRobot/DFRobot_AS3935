'''
 # @file DFRobot_AS3935_ordinary.py
 # @brief SEN0290 Lightning Sensor
 # @n This sensor can detect lightning and display the distance and intensity of the lightning within 40 km
 # @n It can be set as indoor or outdoor mode.
 # @n The module has three I2C, these addresses are:
 # @n  AS3935_ADD1  0x01   A0 = 1  A1 = 0
 # @n  AS3935_ADD2  0x02   A0 = 0  A1 = 1
 # @n  AS3935_ADD3  0x03   A0 = 1  A1 = 1
 # @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 # @licence     The MIT License (MIT)
 # @author [TangJie](jie.tang@dfrobot.com)
 # @version  V1.0.2
 # @date  2019-09-28
 # @url https://github.com/DFRobor/DFRobot_AS3935
'''

import sys
sys.path.append('../')
import time
from DFRobot_AS3935_Lib import DFRobot_AS3935
import RPi.GPIO as GPIO
from datetime import datetime

#I2C address
AS3935_I2C_ADDR1 = 0X01
AS3935_I2C_ADDR2 = 0X02
AS3935_I2C_ADDR3 = 0X03

#Antenna tuning capcitance (must be integer multiple of 8, 8 - 120 pf)
AS3935_CAPACITANCE = 96
IRQ_PIN = 7

#Indoor/outdoor mode selection
AS3935_INDOORS = 0
AS3935_OUTDOORS = 1
AS3935_MODE = AS3935_INDOORS

#Enable/disable disturber detection
AS3935_DIST_DIS = 0
AS3935_DIST_EN = 1
AS3935_DIST = AS3935_DIST_EN

GPIO.setmode(GPIO.BOARD)

sensor = DFRobot_AS3935(AS3935_I2C_ADDR3, bus = 1)
if (sensor.reset()):
  print("init sensor sucess.")
else:
  print("init sensor fail")
  while True:
    pass

#Configure sensor
sensor.manual_cal(AS3935_CAPACITANCE, AS3935_MODE, AS3935_DIST)

# Connect the IRQ and GND pin to the oscilloscope.
# uncomment the following sentences to fine tune the antenna for better performance.
# This will dispaly the antenna's resonance frequency/16 on IRQ pin (The resonance frequency will be divided by 16 on this pin)
# Tuning AS3935_CAPACITANCE to make the frequency within 500/16 kHz plus 3.5% to 500/16 kHz minus 3.5%
#
# sensor.setLco_fdiv(0)
# sensor.set_irq_output_source(3)

#view all register data
#sensor.print_all_regs()

def callback_handle(channel):
  global sensor
  time.sleep(0.005)
  intSrc = sensor.get_interrupt_src()
  if intSrc == 1:
    lightning_distKm = sensor.get_lightning_distKm()
    print('Lightning occurs!')
    print('Distance: %dkm'%lightning_distKm)

    lightning_energy_val = sensor.get_strike_energy_raw()
    print('Intensity: %d '%lightning_energy_val)
  elif intSrc == 2:
    print('Disturber discovered!')
  elif intSrc == 3:
    print('Noise level too high!')
  else:
    pass
#Set to input mode
GPIO.setup(IRQ_PIN, GPIO.IN)
#Set the interrupt pin, the interrupt function, rising along the trigger
GPIO.add_event_detect(IRQ_PIN, GPIO.RISING, callback = callback_handle)
print("start lightning detect.")

while True:
  time.sleep(1.0)


