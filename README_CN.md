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
3.检测云对地和云内(云对云)闪烁
4. 嵌入人工干扰抑制算法
5. 可编程检测水平使阈值设置为最佳控制
6. 三个i2c接口，自由切换避免站点冲突

## 库安装

使用此库前，请首先下载库文件，将其粘贴到\Arduino\libraries目录中，然后打开examples文件夹并在该文件夹中运行演示。

## 方法

```C++
  /**
  * @fn begin
  * @brief I2C初始化
  * @return uint8_t 类型, 表示初始化状态
  * @retval 0 成功 
  * @retval 1 失败
  */
  uint8_t begin(void);

 /**
  * @brief 设置 i2c 地址
  * @param devAddx     i2c 地址  
  */
  void setI2CAddress(uint8_t devAddx);

  /**
   * @fn manualCal
   * @brief 配置传感器
   * @param capacitance    天线调谐电容(必须是8,8 - 120pf的整数倍)
   * @param location       室内或室外模式选择
   * @param disturber      启用/禁用干扰发射机检测
   * @return None
   */
  void manualCal(uint8_t capacitance, uint8_t location, uint8_t disturber);

 /**
  * @fn defInit
  * @brief 将寄存器重置为默认值
  * @return int 类型,表示rest状态
  * @return 0 成功
  */
  int defInit(void);

 /**
  * @fn disturberEn
  * @brief 中断检测使能
  * @return None
  */
  void disturberEn(void);

 /**
  * @fn disturberDis
  * @brief 中断检测失能
  * @return None
  */
  void disturberDis(void);

 /**
  * @fn setIRQOutputSource
  * @brief 设置中断源
  * @param irqSelect 0 = NONE, 1 = TRCO, 2 = SRCO, 3 = LCO
  * @return None
  */
  void setIRQOutputSource(uint8_t irqSelect);

 /**
  * @fn setTuningCaps
   * @brief 设置容量
   * @param capVal 容量大小
   * @return None
   */
  void setTuningCaps(uint8_t capVal);

 /**
  * @fn getInterruptSrc
  * @brief 获取中断源
  * @return uint8_t类型，返回中断源类型
  * @retval 0    没有中断
  * @retval 1    闪电引起的中断
  * @retval 2    干扰中断
  * @retval 3    噪声量太高
  */
  uint8_t getInterruptSrc(void);

 /**
  * @fn getLightningDistKm
  * @brief 获取闪电距离
  * @return 闪电距离(单位公里)
  */
  uint8_t getLightningDistKm(void);

 /**
  * @fn getStrikeEnergyRaw
  * @brief 获取闪电能力强度
  * @return 闪电能力强度(0-1000)
  */
  uint32_t getStrikeEnergyRaw(void);

 /**
  * @fn setIndoors
  * @brief 设置为室内模式
  * @return None
  */
  void setIndoors(void);

 /**
  * @fn setOutdoors
  * @brief 设置为室外模式
  * @return None
  */
  void setOutdoors(void);

 /**
  * @fn getNoiseFloorLvl
  * @brief 获取噪音等级
  * @return 返回噪声等级
  */
  uint8_t getNoiseFloorLvl(void);

 /**
  * @fn setNoiseFloorLvl
  * @brief 设置噪音等级
  * @param nfSel 0~7,大于7将使用默认值:2
  * @return None
  */
  void setNoiseFloorLvl(uint8_t nfSel);

 /**
  * @fn getWatchdogThreshold
  * @brief 获取干扰等级
  * @return 返回干扰等级
  */
  uint8_t getWatchdogThreshold(void);

 /**
  * @fn setWatchdogThreshold
  * @brief 设置干扰等级
  * @param wdth 0~7,大于7将使用默认值:2
  * @return None
  */
  void setWatchdogThreshold(uint8_t wdth);

 /**
  * @fn getSpikeRejection
  * @brief 获取 SREJ (毛刺抑制)
  * @return 返回SREJ值
  */
  uint8_t getSpikeRejection(void);

 /**
  * @fn setSpikeRejection
  * @brief 修改 SREJ (毛刺抑制)
  * @param 0~7,大于7将使用默认值:2
  */
  void setSpikeRejection(uint8_t srej);

 /**
  * @fn setLcoFdiv
  * @brief 设置 LCO_FDIV 寄存器
  * @param fdiv 设置0, 1, 2或3的比率分别为16,32,64和128
  * @return None
  */
  void setLcoFdiv(uint8_t fdiv);

 /**
  * @fn printAllRegs
  * @brief 查看注册数据
  * @return None
  */
  void printAllRegs(void);

 /**
  * @fn powerUp
  * @brief 配置传感器电源
  * @return None
  */
  void powerUp(void);
```
## 兼容性

主板               | 通过  | 未通过   | 未测试   | 备注
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno |       √      |             |            |
  esp8266   |       √      |             |            | 

## 历史

- 2021/09/30 - 1.0.2 版本
- 2021/08/24 - 1.0.1 版本
- 2019/09/28 - 1.0.0 版本

## 创作者

Written by TangJie(jie.Tang@dfrobot.com), 2019. (Welcome to our [website](https://www.dfrobot.com/))
