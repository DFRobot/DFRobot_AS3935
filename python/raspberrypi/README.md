# DFRobot_AS3935

  * [中文版](./README_CN.md)
  
AS3935 Lightning Sensor can detect lightning and display the distance and intensity of the lightning without the disturbance of electric arc and noise.
It can be set as indoor or outdoor mode.

![Product Image](./resources/images/SEN0290.png)

## 产品链接（https://www.dfrobot.com/product-1828.html）

    SKU：SEN0290

## Table of Contents
  
  * [Summary](#summary)
  * [Installation](#Installation)
  * [Methods](#Methods)
  * [Compatibility](#compatibility)
  * [History](#history)
  * [Credits](#credits)

## Summary

Input commands and read data from AS3935 modules

1. Lightning sensor warns of lightning storm activity within a radius of 40km 
2. Distance estimation to the head of the storm from overhead to 40km in 15 steps 
3. Detects both cloud-to-ground and intra-cloud(cloud-to-cloud) flashes 
4. Embedded man-made disturber rejection algorithm 
5. Programmable detection levels enable threshold setting for optimal controls 
6. Three i2c interfaces, switch freely to avoid site conflicts 

## Installation

To use the library, first download it to Raspberry Pi, then open the routines folder.To execute a routine demox.py, type Python demox.py on the command line.For example, to execute the control_LEd.py routine, you need to enter:

```python
python DFRobot_AS3935_detailed.py
```

## Methods

```python
  '''
    @brief Sensor reset
  '''
  def reset(self);

  '''
    @brief Configure sensor 
    @param capacitance Antenna tuning capcitance (must be integer multiple of 8, 8 - 120 pf)
    @param location    Indoor/outdoor mode selection
    @param disturber   Enable/disable disturber detection
  '''
  def manual_cal(self, capacitance, location, disturber);

  '''
    @brief Get mid-range type
    @return Return to interrupted state
    @retval  0  Unknown src
    @retval  1  Lightning detected
    @retval  2  Disturber
    @retval  3  Noise level too high
  '''
  def get_interrupt_src(self);

  '''
    @brief get lightning distance 
    @return unit kilometer
  '''
  def get_lightning_distKm(self);

  '''
    @brief get lightning energy intensity 
    @return lightning energy intensity(0-1000)
  '''
  def get_strike_energy_raw(self);

  '''
    @brief Sets LCO_FDIV register
    @param fdiv Set 0, 1, 2 or 3 for ratios of 16, 32, 64 and 128, respectively
  '''
  def set_lco_fdiv(self,fdiv);

  '''
    @brief Set interrupt source
    @param irqSelect 0 = NONE, 1 = TRCO, 2 = SRCO, 3 = LCO
  '''
  def set_irq_output_source(self, irqSelect);

  '''
    @brief Set to the outdoor model
  '''
  def set_outdoors(self);

  '''
    @brief Set to the indoor model
  '''
  def set_indoors(self);

  '''
    @brief Disturber detection enabled
  '''
  def disturber_en(self);

  '''
    @brief Disturber detection disenabled
  '''
  def disturber_dis(self);

  '''
    @brief Set the noise level
    @param 0~7,More than 7 will use the default value:2
  '''
  def set_noise_floor_lv1(self, nfSel);

  '''
    @brief Get the noise level
    @return 0~7
  '''
  def get_noise_floor_lv1(self);

  '''
    @brief Set an anti-interference rating
    @param 0~7,More than 7 will use the default value:2
  '''
  def set_watchdog_threshold(self, wdth);

  '''
    @brief read WDTH
    @return 0~7
  '''
  def get_watchdog_threshold(self);

  '''
    @brief Modify SREJ (spike rejection)
    @param 0~7,More than 7 will use the default value:2
  '''
  def set_spike_rejection(self, srej);

  '''
    @brief read SREJ (spike rejection)
    @return 0~7
  '''
  def get_spike_rejection(self);
```
## Compatibility

* RaspberryPi Version

| Board        | Work Well | Work Wrong | Untested | Remarks |
| ------------ | :-------: | :--------: | :------: | ------- |
| RaspberryPi2 |           |            |    √     |         |
| RaspberryPi3 |           |            |    √     |         |
| RaspberryPi4 |     √     |            |          |         |

* Python Version

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :-------: | :--------: | :------: | ------- |
| Python2 |     √     |            |          |         |
| Python3 |     √     |            |          |         |
## History

- 2021/09/30 - Version 1.0.2 released.
- 2021/08/24 - Version 1.0.1 released.
- 2019/09/28 - Version 1.0.0 released.
  
## Credits

Written by TangJie(jie.Tang@dfrobot.com), 2019. (Welcome to our [website](https://www.dfrobot.com/))







