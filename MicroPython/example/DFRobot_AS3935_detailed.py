# file DFRobot_AS3935_detailed.py
#
# SEN0290 Lightning Sensor
# This sensor can detect lightning and display the distance and intensity of the lightning within 40 km
# It can be set as indoor or outdoor mode.
# The module has three I2C, these addresses are:
# AS3935_ADD1  0x01   A0 = 1  A1 = 0
# AS3935_ADD2  0x02   A0 = 0  A1 = 1
# AS3935_ADD3  0x03   A0 = 1  A1 = 1
#
#
# Copyright    [DFRobot](http://www.dfrobot.com), 2018
# Copyright    GNU Lesser General Public License
#
# version  V1.0
# date  2018-11-28

from DFRobot_AS3935_Lib import DFRobot_AS3935
from machine import Pin, I2C
import utime

#I2C address
AS3935_I2C_ADDR1 = 0X01
AS3935_I2C_ADDR2 = 0X02
AS3935_I2C_ADDR3 = 0X03

# I2C HW ID or -1 for SW I2C
I2C_ID = 1
I2C_SCL_PIN = 22
I2C_SDA_PIN = 23

#Antenna tuning capcitance (must be integer multiple of 8, 8 - 120 pf)
AS3935_CAPACITANCE = 120
IRQ_PIN = 12

# Initialize 
i2c = I2C(I2C_ID, scl=Pin(I2C_SCL_PIN), sda=Pin(I2C_SDA_PIN), freq=400000)
sensor = DFRobot_AS3935(AS3935_I2C_ADDR3, i2c)
if (sensor.reset()):
    print("init sensor sucess.")
else:
    print("init sensor fail")
    while True:
        pass
#Configure sensor
sensor.powerUp()

#set indoors or outdoors models
sensor.setIndoors()
#sensor.setOutdoors()

#disturber detection
sensor.disturberEn()
#sensor.disturberDis()

sensor.setIrqOutputSource(0)
utime.sleep(0.5)
#set capacitance
sensor.setTuningCaps(AS3935_CAPACITANCE)

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
sensor.setWatchdogThreshold(2)
#wtdgThreshold = sensor.getWatchdogThreshold()

#used to modify SREJ (spike rejection),values should only be between 0x00 and 0x0F (0 and 7)
sensor.setSpikeRejection(2)
#spikeRejection = sensor.getSpikeRejection()

#view all register data
#sensor.printAllRegs()

def callback_handle(channel):
    global sensor
    utime.sleep(0.005)
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
pinirq = Pin(IRQ_PIN, Pin.IN)
#Set the interrupt pin, the interrupt function, rising along the trigger
pinirq.irq(trigger=Pin.IRQ_RISING, handler=callback_handle)
print("start lightning detect.")

while True:
    utime.sleep(1.0)


