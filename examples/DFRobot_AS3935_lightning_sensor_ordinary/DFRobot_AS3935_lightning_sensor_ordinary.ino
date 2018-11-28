/*!
   file DFRobot_AS3935_lightning_sensor.ino

   SEN0290 Lightning Sensor
   This sensor can detect lightning and display the distance and intensity of the lightning within 40 km
   It can be set as indoor or outdoor mode.
   The module has three I2C, these addresses are:
   AS3935_ADD1  0x01   A0 = 1  A1 = 0
   AS3935_ADD2  0x02   A0 = 0  A1 = 1
   AS3935_ADD3  0x03   A0 = 1  A1 = 1
  
   Copyright    [DFRobot](http://www.dfrobot.com), 2018
   Copyright    GNU Lesser General Public License

   version  V0.5
   date  2018-11-28
*/

#include "Lib_I2C.h"
#include "DFRobot_AS3935_I2C.h"

volatile int8_t AS3935IsrTrig = 0;

#define IRQ_PIN              2

// Antenna tuning capcitance (must be integer multiple of 8, 8 - 120 pf)
#define AS3935_CAPACITANCE   96

// Indoor/outdoor mode selection
#define AS3935_INDOORS       0
#define AS3935_OUTDOORS      1
#define AS3935_MODE          AS3935_INDOORS

// Enable/disable disturber detection
#define AS3935_DIST_DIS      0
#define AS3935_DIST_EN       1
#define AS3935_DIST          AS3935_DIST_EN

// I2C address
#define AS3935_I2C_ADDR       AS3935_ADD3

void AS3935_ISR();

DFRobot_AS3935_I2C  lightning0((uint8_t)IRQ_PIN, (uint8_t)AS3935_I2C_ADDR);

void setup()
{

  Serial.begin(115200);
  Serial.println("DFRobot AS3935 lightning sensor begin!");

  // Setup for the the I2C library: (enable pullups, set speed to 400kHz)
  I2c.begin();
  I2c.pullup(true);
  I2c.setSpeed(1);
  delay(2);

  // Set registers to default
  if(lightning0.defInit() != 0){
    Serial.println("I2C init fail");
    while(1){}  
  }
  // Configure sensor
  lightning0.manualCal(AS3935_CAPACITANCE, AS3935_MODE, AS3935_DIST);
  // Enable interrupt (connect IRQ pin IRQ_PIN: 2, default)

//  Connect the IRQ and GND pin to the oscilloscope.
//  uncomment the following sentences to fine tune the antenna for better performance.
//  This will dispaly the antenna's resonance frequency/16 on IRQ pin (The resonance frequency will be divided by 16 on this pin)
//  Tuning AS3935_CAPACITANCE to make the frequency within 500/16 kHz ± 3.5%
//  lightning0.setLcoFdiv(0);
//  lightning0.setIRQOutputSource(3);

  attachInterrupt(0, AS3935_ISR, RISING);

}

void loop()
{
  // It does nothing until an interrupt is detected on the IRQ pin.
  while (AS3935IsrTrig == 0) {}
  delay(5);

  // Reset interrupt flag
  AS3935IsrTrig = 0;

  // Get interrupt source
  uint8_t intSrc = lightning0.getInterruptSrc();
  if (intSrc == 1)
  {
    // Get rid of non-distance data
    uint8_t lightningDistKm = lightning0.getLightningDistKm();
    Serial.println("Lightning occurs!");
    Serial.print("Distance: ");
    Serial.print(lightningDistKm);
    Serial.println(" km");

    // Get lightning energy intensity
    uint32_t lightningEnergyVal = lightning0.getStrikeEnergyRaw();
    Serial.print("Intensity: ");
    Serial.print(lightningEnergyVal);
    Serial.println("");
  }
  else if (intSrc == 2)
  {
    Serial.println("Disturber discovered!");
  }
  else if (intSrc == 3)
  {
    Serial.println("Noise level too high!");
  }

}

//IRQ handler for AS3935 interrupts
void AS3935_ISR()
{
  AS3935IsrTrig = 1;
}

