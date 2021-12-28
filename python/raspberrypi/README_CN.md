# DFRobot_AS3935

* [English Version](./README.md)
  
AS3935雷电传感器可以检测雷电，显示雷电的距离和强度，不受电弧和噪声的干扰
可设置为室内或室外模式

![Product Image](./resources/images/SEN0290.png)

## 产品链接（https://www.dfrobot.com.cn/goods-1889.html）

    SKU：SEN0290

## 目录

  * [概述](#概述)
  * [库安装](#库安装)
  * [方法](#方法)
  * [兼容性](#兼容性)
  * [历史](#历史)
  * [创作者](#创作者)
  
## 概述

从AS3935模块中输入命令和读取数据

1. 闪电传感器对半径40公里以内的雷暴活动发出警报
2. 从头顶到风暴顶部的距离估计为40公里，每15步
3. 检测云对地和云内(云对云)闪烁
4. 嵌入人工干扰抑制算法
5. 可编程检测水平使阈值设置为最佳控制
6. 三个i2c接口，自由切换避免站点冲突

## 库安装

要使用这个库，首先将库下载到Raspberry Pi，然后打开例程文件夹。要执行一个例程demox.py，请在命令行中输入python demox.py。例如，要执行control_led.py例程，你需要输入:

```python
python DFRobot_AS3935_detailed.py
```

## 方法

```python
  '''
    @brief 传感器重启
  '''
  def reset(self);

  '''
    @brief 配置传感器 
    @param capacitance 天线调谐电容(必须是8,8 - 120pf的整数倍)
    @param location    室内或室外模式选择
    @param disturber   启用/禁用干扰发射机检测
  '''
  def manual_cal(self, capacitance, location, disturber);

  '''
    @brief Get mid-range type
    @return 返回中断状态
    @retval  0  Unknown src
    @retval  1  Lightning detected
    @retval  2  Disturber
    @retval  3  Noise level too high
  '''
  def get_interrupt_src(self);

  '''
    @brief 获取闪电距离 
    @return 闪电距离(单位公里）
  '''
  def get_lightning_distKm(self);

  '''
    @brief 获取闪电能力强度 
    @return 闪电能力强度(0-1000)
  '''
  def get_strike_energy_raw(self);

  '''
    @brief 设置 LCO_FDIV 寄存器
    @param fdiv 设置0, 1, 2或3的比率分别为16,32,64和128
  '''
  def set_lco_fdiv(self,fdiv);

  '''
    @brief 设置中断源
    @param irqSelect 0 = NONE, 1 = TRCO, 2 = SRCO, 3 = LCO
  '''
  def set_irq_output_source(self, irqSelect);

  '''
    @brief 设置为室外模式
  '''
  def set_outdoors(self);

  '''
    @brief 设置为室内模式
  '''
  def set_indoors(self);

  '''
    @brief 中断检测使能
  '''
  def disturber_en(self);

  '''
    @brief 中断检测失能
  '''
  def disturber_dis(self);

  '''
    @brief 设置噪音等级
    @param 0~7,大于7将使用默认值:2
  '''
  def set_noise_floor_lv1(self, nfSel);

  '''
    @brief 获取噪音等级
    @return 0~7
  '''
  def get_noise_floor_lv1(self);

  '''
    @brief 设置抗干扰等级
    @param 0~7,大于7将使用默认值:2  
  '''
  def set_watchdog_threshold(self, wdth);

  '''
    @brief 获取抗干扰等级
    @return 0~7
  '''
  def get_watchdog_threshold(self);

  '''
    @brief 修改 SREJ (毛刺抑制)
    @param 0~7,大于7将使用默认值:2
  '''
  def set_spike_rejection(self, srej);

  '''
    @brief r获取ead SREJ (毛刺抑制)
    @return 0~7
  '''
  def get_spike_rejection(self);
```
## 兼容性

* 树莓派版本

| Board        |    通过   |    未通过   |   未测试 |   备注   |
| ------------ | :-------: | :--------: | :------: | ------- |
| RaspberryPi2 |           |            |    √     |         |
| RaspberryPi3 |           |            |    √     |         |
| RaspberryPi4 |     √     |            |          |         |

* Python 版本

| Python  |   通过    |    未通过   |  未测试  |   备注   |
| ------- | :-------: | :--------: | :------: | ------- |
| Python2 |     √     |            |          |         |
| Python3 |     √     |            |          |         |

## 历史

- 2021/09/30 - 1.0.2 版本
- 2021/08/24 - 1.0.1 版本
- 2019/09/28 - 1.0.0 版本

## 创作者

Written by TangJie(jie.Tang@dfrobot.com), 2019. (Welcome to our [website](https://www.dfrobot.com/))
