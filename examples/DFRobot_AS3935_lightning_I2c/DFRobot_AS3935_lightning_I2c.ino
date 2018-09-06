/*!
 * file as3935_lightning_i2c_nocal.ino
 *
 * On The Lightning Sensor 
 * This sensor can detect lightning and display the distance and intensity of the lightning without the
 * disturbance of electric arc and noise.It can be set as indoor or outdoor mode.
 * The module has three I2C, the addresses are:
 *   0x03   A0-High  A1-High
 *   0x02   A0-Low   A1-High 
 *   0x01   A0-High  A1-Low
 *
 * Copyright    [DFRobot](http://www.dfrobot.com), 2018
 * Copyright    GNU Lesser General Public License
 * 
 * version  V0.1
 * date  2018-9-6
 */

#include "I2C.h"
#include "DFRobot_AS3935_I2C.h"
     
volatile int8_t AS3935_ISR_Trig = 0;

#define SI_PIN               9
#define IRQ_PIN              2        

#define AS3935_CAPACITANCE   72      

#define AS3935_INDOORS       0
#define AS3935_OUTDOORS      1
#define AS3935_DIST_DIS      0
#define AS3935_DIST_EN       1

void AS3935_ISR();

DF_AS3935_I2C  lightning0((uint8_t)IRQ_PIN, (uint8_t)SI_PIN, (uint8_t)AS3935_ADD3);

void setup()
{
  
  Serial.begin(115200);
  Serial.println("Playing With DFRobot: AS3935 Lightning Sensor");
  Serial.println("beginning boot procedure....");
  
  // Setup for the the I2C library: (enable pullups, set speed to 400kHz)
  I2c.begin();
  I2c.pullup(true);
  I2c.setSpeed(1); 
  delay(2);

  //lightning0.AS3935_I2CAddress(AS3935_ADD1);  // x01 - A0->high A1->low
  //lightning0.AS3935_I2CAddress(AS3935_ADD2);  // x02 - A0->low  A1->high
  //lightning0.AS3935_I2CAddress(AS3935_ADD3);  // x03 - A0->high A1->high
  lightning0.AS3935_SetI2CAddress(AS3935_ADD3);
  
  // Set registers to default  
  lightning0.AS3935_DefInit();   
  // Now update sensor cal for your application and power up chip
  lightning0.AS3935_ManualCal(AS3935_CAPACITANCE, AS3935_INDOORS, AS3935_DIST_EN);
  // Enable interrupt (hook IRQ pin to Arduino Uno/Mega interrupt input: 0 -> pin 2, 1 -> pin 3 )
  attachInterrupt(0, AS3935_ISR, RISING);
  // For debug, view register data
  lightning0.AS3935_PrintAllRegs();
  // Clear trigger
  AS3935_ISR_Trig = 0;           

}

void loop()
{
  // It does nothing until an interrupt is detected on the IRQ pin.
  while(0 == AS3935_ISR_Trig){}
  delay(5);
  
  // Reset interrupt flag
  AS3935_ISR_Trig = 0;
  
  // Now get interrupt source
  uint8_t int_src = lightning0.AS3935_GetInterruptSrc();
  if(1 == int_src)
  {
	// Get rid of non-distance data
    uint8_t lightning_dist_km = lightning0.AS3935_GetLightningDistKm();
    Serial.print("发生闪电啦! 闪电发生距离: ");
    Serial.print(lightning_dist_km);
    Serial.println(" km");
    // Get lightning energy intensity
    uint32_t lightning_energy_val = lightning0.AS3935_GetStrikeEnergyRaw();
    Serial.print("雷电强度：");
    Serial.print(lightning_energy_val);
    Serial.println("");
  }
  else if(2 == int_src)
  {
    Serial.println("发现干扰源");
  }
  else if(3 == int_src)
  {
    Serial.println("噪音强度过高");
  }
  lightning0.AS3935_PrintAllRegs(); 
  Serial.println("");
}

// This is irq handler for AS3935 interrupts, has to return void and take no arguments
// always make code in interrupt handlers fast and short
void AS3935_ISR()
{
  AS3935_ISR_Trig = 1;
}

