# file DFRobot_AS3935_detailed.py
#
# SEN0290 Lightning Sensor
# This sensor can detect lightning and display the distance and intensity of the lightning within 40 km
# It can be set as indoor or outdoor mode.
# The module has three I2C, these addresses are:
# AS3935_ADD1  0x01   A0 = High  A1 = Low
# AS3935_ADD3  0x03   A0 = High  A1 = High
# AS3935_ADD2  0x02   A0 = Low   A1 = High
#
#
# Copyright    [DFRobot](http://www.dfrobot.com), 2018
# Copyright    GNU Lesser General Public License
#
# version  V0.1
# date  2018-11-13

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
IRQ_PIN = 37

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
sensor.manualCal(AS3935_CAPACITANCE, AS3935_MODE, AS3935_DIST)

#set indoors or outdoors models
sensor.setIndoors()
#sensor.setOutdoors()

#disturber detection
sensor.disturberEn()
#sensor.disturberDis()

# Connect the IRQ and GND pin to the oscilloscope.
# uncomment the following sentences to fine tune the antenna for better performance.
# This will dispaly the antenna's resonance frequency/16 on IRQ pin (The resonance frequency will be divided by 16 on this pin)
# Tuning AS3935_CAPACITANCE to make the frequency within 500/16 kHz plus 3.5% to 500/16 kHz minus 3.5%
#
# sensor.setLcoFdiv(0)
# sensor.setIrqOutputSource(3)

#Set the noise level,use a default value greater than 7
sensor.setNoiseFloorLv1(2)
#noiseLv = sensor.getNoiseFloorLv1()

#used to modify WDTH,alues should only be between 0x00 and 0x0F (0 and 7)
sensor.setWatchdogThreshold(0)
#wtdgThreshold = sensor.getWatchdogThreshold()

#used to modify SREJ (spike rejection),values should only be between 0x00 and 0x0F (0 and 7)
sensor.setSpikeRejection(2)
#spikeRejection = sensor.getSpikeRejection()

#view all register data
#sensor.printAllRegs()

def callback_handle(channel):
    global sensor
    time.sleep(0.005)
    intSrc = sensor.getInterruptSrc()
    if intSrc == 1:
        lightningDistKm = sensor.getLightningDistKm()
        print('Lightning occurs!')
        print('Distance: %dkm'%lightningDistKm)

        lightningEnergyVal = sensor.getStrikeEnergyRaw()
        print('Intensity: %d '%lightningEnergyVal)
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


