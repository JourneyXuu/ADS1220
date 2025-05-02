## **0.0 项目简介**
**github开源链接：**
   https://github.com/JourneyXuu/ADS1220  
   
**立创开源链接:**
https://oshwhub.com/xu_duoduo/ads1220-module-24-bit  

![image](https://github.com/user-attachments/assets/766d81c6-8e8d-4942-afdc-7c30b89e6542)
 
## **0.1 ADS1220 核心功能**

### 1. 信号采集能力
- **多通道输入**  ：支持2路差分/4路单端输入，灵活配置传感器接口
- **高分辨率ADC**  ：24位Δ-Σ架构，20位有效分辨率（@20SPS）
- **宽增益范围**  ：集成PGA（1-128倍可调），支持μV级信号放大

### 2. 集成化设计
- **双匹配电流源**  ：10μA-1.5mA 7档可编程IDAC，精度±1%
- **基准电压源**  ： 内置2.048V基准，低温漂（5ppm/℃）
- **数字滤波器**  ：单周期稳定，支持50/60Hz工频抑制（＞105dB）

### 3. 低功耗特性
- 工作电流：  
  - 正常模式：340μA @3.3V  
  - 待机模式：0.1μA
- 电源范围：2.3-5.5V宽压供电

### 4.IO管脚
![image](https://github.com/user-attachments/assets/4af52ae1-76d5-4224-b140-3ed232fd9103)

```
CS:         片选,拉低使能通信
SCLK:       SPI的时钟引脚
DOUT/DRDY:  SPI的MISO
DIN:        SPI的MOSI
DRDY:       当ADS1220完成数据转换以后就会产生下降沿跳变,
            处理器(MCU)可以将其接到对应的外部中断脚上来读取ADS1220是否准备好数据
```


## **1. 项目功能**
使用双级电源输入（DC-DC+LDO）：
* DC-DC将电源输入转为3.6V
* LDO将3.6V转化为3.3V，效率为91.67%
* 使用TL431作为板级基准电源（难点）


### **1.1模块介绍**
**1.1.1 功能框图**
![image](https://github.com/user-attachments/assets/cebcd36b-8c2c-4304-8cee-fc6babd1ff68)
该设备包含一个非常灵活的输入多路复用器。
可以测量四个单端信号、两个差分信号或两个单端信号和一个差分信号的组合。
**组合1：四个单端信号：**
AIN0 AIN1 AIN2 AIN3
**组合2：两个差分信号：**
( REFP0,REFN0 )( REFP1,REFN1 )
**组合3：两个单端信号+一个差分信号**

#### **1.1.2 ADS1220.多路选择器**
```
该设备包含一个非常灵活的输入多路复用器，如图38所示。
可以测量四个单端信号、两个差分信号或两个单端讯号和一个差分讯号的组合。
```
![image](https://github.com/user-attachments/assets/1eae8ca8-81c3-40d6-a9bb-1ca157e2744c)

 

#### **1.1.3 ADS1220.可编程增益放大器(PGA)**
```
PGA:programmable gain amplifier (PGA)
PGA可以被设置为1,2,4,8,16,32,64,128
为了保证PGA工作在线性工作区，运放输出信号必须满足：
```
![image](https://github.com/user-attachments/assets/744970d3-c0e5-45ab-a844-62492c4fc8c4)

 
 ```
 由运放的输出信号就可以根据PGA反算出输入信号的范围
 ```
**量程**
![image](https://github.com/user-attachments/assets/85fa1920-3739-4cc9-a549-c7fb9f0cf7bc)




## **2 原理解析（硬件说明）**
### **2.1 板级电源方案**
该方案适配各种对于电源纹波精度要求高、高效率的场合。、
```
**DC-DC+LDO的电源供电**
TPS536201将输入5V转化为3.6V
TPS7A2033PDBVR将输入3.6V转为3.3V，效率为91.67%，降低纹波
```
#### **2.1.1 TPS536201**
![image](https://github.com/user-attachments/assets/cc8aba2e-6216-4f51-a01e-8a9999c7ce32)

 
```
宽输入电压: 4.5V--17V
输出电压范围:0.76V--7V
低导通MOS电阻
VB反馈电压0.768V
```

**(1) 推荐的电感电容值**
![image](https://github.com/user-attachments/assets/37296613-0e62-41a9-ba2c-245b485b542c)


**（2） 手册上对双极点频率和D-CAP2补偿机制的**
![image](https://github.com/user-attachments/assets/1e0066d3-fa80-498f-a8d9-4102f4dfcad6)

 下面为翻译
 ```
 在低频下，整体环路增益由输出设定点电阻分压器网络和设备的内部增益设置。低频相位为180°。
 在输出滤波器极点频率下，增益以每十个单位-40 dB的速率下降，相位迅速下降。
 D-CAP2引入了一个高频零点，将增益滚降降低到每十个单位-20 dB，
 并将相位裕度增加到零频率以上每10个单位的90°。
 必须选择输出滤波器的电感器和电容器，使方程3的双极位于高频零点以下，
 但足够接近，以便高频零点提供的相位升压为稳定电路提供足够的相位裕度。
 为了满足这一要求，请使用表2中推荐的值。
 ```
**（3） 谈谈开关电源LC滤波器的双极点频率和D-CAP2补偿机制**
![image](https://github.com/user-attachments/assets/b14885af-cd85-4f3c-b714-4e37e4f882b6)

```
这部分的内容主要涉及到《自动控制原理》
```
**（4） 整体环路增益(overall loop gain)**
DC-DC的其中一个测试项是环路稳定性（环路增益）。
```
测试方式如下图：
在电源环路中串联入一个小电阻（图中的R5）
在电阻上施加一个微小的交流信号
测量电阻两端电压的幅值和相位
改变交流信号的频率，获得环路增益的幅频和相频曲线
```
![image](https://github.com/user-attachments/assets/20cc45eb-f6ca-4a24-ad3c-8157c72d2d0c)

 
 ```
环路增益定义为T(s)=G(s)H(s)，是环路中所有环节的乘积
T(s)的特性（增益、相位）影响负反馈系统的稳定性
工程上要求：
    相位裕度40-60
    幅值裕度>6dB
```
**（5） LC滤波器的双极点威胁稳定性**

```
系统的环路增益：
1.低频段（）<1khz）:
恒定高增益（80-100dB）：由反馈电阻和芯片内部增益决定
2.在双极点频率(fp)：
在 fp处增益以-40 dB/十倍频程下降
```

**（6） D-CAP2通过高频零点补偿相位滞后**
```
引入零点提升相位，对抗极点的作用
在零点频率（fz）以上，增益滚降减缓至-20 dB/十倍频程
```
#### **2.1.2 TPS7A2033PDBVR**
![image](https://github.com/user-attachments/assets/64946530-abbb-4908-90ac-6ad94777a171)

 
```
超低压差：
  300mA下位140mV（0.14V）
  高 PSRR：1kHz 时为 95dB
  低输出电压噪声：7u Vrms
```
**（1） 谈谈PSRR**
```
PSRR(电源抑制比)：Power Supply RejecTIon RaTIo
 是衡量电路对电源噪声抑制能力的指标，表示输入电源的噪声被输出端衰减的程度。
 其数学定义为：
```
![image](https://github.com/user-attachments/assets/7d7bd9ef-abf6-4f3b-9786-ac49fa5aada2)

 
```

1kHz时的PSRR为95dB 说明在1kHz频率下，
电路对电源噪声的抑制能力最强
输入电源的噪声在输出端被抑制了约 5.6万倍
```

## **3 软件代码**
**寄存器配置**
参考@CSDN 三石君
https://blog.csdn.net/weixin_45165549/article/details/127892341

#### **3.1 配置寄存器0**
![image](https://github.com/user-attachments/assets/970e9f94-bc60-4ac0-9857-7cc3faa1b7e4)

 
 ```
 MUX[3:0]   : 0000 默认双端输入
 GAIN[2:0]  : 000 默认增益1
 PGA_BYPASS : 0 失能PGA旁路控制器，
 cofig[0] = 0000 0000 = 0x00
 ```
 
 #### **3.2 配置寄存器1**
![image](https://github.com/user-attachments/assets/f3468765-72cc-45e5-b643-7558305bd20f)

![image](https://github.com/user-attachments/assets/a3444e2f-faac-4963-b5cd-82aa82af2e17)

  
**3.2.1 烧毁检测电流源**
![image](https://github.com/user-attachments/assets/c668641f-3db1-476e-8636-bb62381fb3c8)

   
**3.2.2 SPS**
SPS（Samples Per Second）是每秒采样次数的缩写，表示ADC每秒钟采集的数据点数

```
DR[2:0]   :  100 每秒采集330次
MODE[1:0] :  00  正常模式（256kHz调制器时钟）
CM        :  1   连续转换
TS        :  0   禁用温度传感器
BCS       :  0   禁用烧毁检测电流源
cofig[1] = 1000 0100 = 0x14
```

 #### **3.3 配置寄存器2**
![image](https://github.com/user-attachments/assets/9ca2e2f7-c2a2-46c8-bc30-ba15f647095b)

   
#### **3.3.1 IDAC**

IDAC（可编程激励电流源） 是ADS1220的双通道匹配恒流源
10μA~1500μA（7档可编程）
可编程（从AINP流出或AINN流入）
#### **3.3.2 PSW**
![image](https://github.com/user-attachments/assets/4cacc29e-e26f-470b-afd7-9dd8b5985277)


```
VREF[1:0]  :  11 使用基准模拟电压AVDD（3.3V）
50/60[1:0] :  10 滤除工频干扰源50HZ
PSW        :  0 禁用低侧电源
IDAC[2:0]  :  000 关断
cofig[2] = 1110 0000 = 0xE0
```

 #### **3.4 配置寄存器3**
![image](https://github.com/user-attachments/assets/4667dcc1-e1a9-4334-93a4-6c2e42f15f3c)

   
```
I1MUX[2:0]   :  000 失能恒流源1
I2MUX[2:0]   :  000 失能恒流源2
DRDYM        :  0 只有DRDT这一位用于指示数据就绪
Reserverd    :  0 保留位，总为0
cofig[3] = 0000 0000 = 0x00
```   
### **3.5.1 时序代码**
 
![image](https://github.com/user-attachments/assets/bcb8b254-5aa0-4fef-b47f-9ccfc6e2e906)

 
**由于发送命令完可能还要接收CS，所以不在最基础的时序中做CS翻转处理，而是在外面**
```
 /*
 *@biref:模拟SPI单字节读写
 *@return: 返回接收到的数据
 *@备注:
*/
uint8_t ADS1220_SPI_ReadWriteByte(uint8_t tx_data) {
    uint8_t rx_data = 0;
    
    for(uint8_t i=0; i<8; i++) {
        // 下降沿发送数据
        if(tx_data & 0x80) SPI_MOSI_HIGH();
        else SPI_MOSI_LOW();
        tx_data <<= 1;
        
        SPI_DELAY(1);
        SPI_SCK_HIGH();  // 产生上升沿（数据采样）
        SPI_DELAY(1);
        
        // 读取MISO数据（在时钟上升沿后采样）
        rx_data <<= 1;
        if(SPI_MISO_READ()) rx_data |= 0x01;
        
        SPI_SCK_LOW();   // 恢复低电平
        SPI_DELAY(1);
    }
    return rx_data;
}
```
 #### **3.5.2 通讯代码**
 
 
![image](https://github.com/user-attachments/assets/b88162e9-15d2-43b9-b65c-a2627a8ce8e1)

   
#### **3.5.3 重点解释三条指令**
![image](https://github.com/user-attachments/assets/a94e9bdb-178f-499d-9ab0-2f2e85ba375a)

   
#### **RDATA（读取数据指令）**:0001 xxxx
1. 将 **最新的ADC转换结果** 加载到输出移位寄存器中。
            当未监控 DOUT/DRDY 或 DRDY 引脚时，可通过此命令主动读取数据。
2. 若在发送 RDATA 命令期间 **新转换完成**；
**DRDY保持低电平**：表示旧结果未被读取，新结果未加载。
**DRDY变为高电平**：表示新结果已加载。

#### **RREG（读寄存器指令）**:0010 rr nn
**rr**:    起始寄存器地址（2位，范围 00-11，对应地址 0x00-0x03）。
**nn**:    读取的寄存器数量减1（2位，范围 00~11，即最多读4个寄存器）。
1. **从指定寄存器地址开始，读取 n+1 个寄存器的值。**
2. 0010 0110→ 十六进制 0x26    从寄存器地址 0x01 开始读取3个寄存器：


#### **WREG（写寄存器指令）**:0100 rr nn
1. 向从**指定地址开始的 n+1 个寄存器**写入数据。
2. **寄存器更新时机**:在最后一个SCLK的下降沿更新配置。
3. 0100 00 01 从地址 0x00 开始写入2个寄存器：
```
/*
 *@biref:模拟SPI单字节读写
 *@return: 返回接收到的数据
 *@备注:
*/
uint8_t ADS1220_SPI_ReadWriteByte(uint8_t tx_data) {
    uint8_t rx_data = 0;
    
    for(uint8_t i=0; i<8; i++) {
        // 下降沿发送数据
        if(tx_data & 0x80) SPI_MOSI_HIGH();
        else SPI_MOSI_LOW();
        tx_data <<= 1;
        
        SPI_DELAY(1);
        SPI_SCK_HIGH();  // 产生上升沿（数据采样）
        SPI_DELAY(1);
        
        // 读取MISO数据（在时钟上升沿后采样）
        rx_data <<= 1;
        if(SPI_MISO_READ()) rx_data |= 0x01;
        
        SPI_SCK_LOW();   // 恢复低电平
        SPI_DELAY(1);
    }
    return rx_data;
}

/* @brief: 发送命令到ADS1220
 * @param: cmd: 命令字节
 * @note:   0000 011x 复位命令
 *          0x00 100x 启动命令
 *          0x00 001x 断电命令(停止)
 * 
 */
void ADS1220_WriteCommand(uint8_t cmd) {
    SPI_CS_LOW();
    ADS1220_SPI_ReadWriteByte(cmd);
    SPI_CS_HIGH();
}


/*
 *@biref:写寄存器 
 *@param: reg_addr: 起始寄存器地址（范围 0x00~0x03，对应 ADS1220 的 4 个配置寄存器）
 *@param: reg_num:  要写入的寄存器数量（范围 1~4）
 *@param: data:     待写入的数据指针（数据长度必须 ≥ reg_num）
 *@note:    RREG命令：0010 rrnn
            WREG命令：0100 rrnn
            rr: 起始寄存器地址（范围 0x00~0x03，对应 ADS1220 的 4 个配置寄存器）
            nn: 要写入的寄存器数量（范围 1~4）
 *@example: ADS1220_WriteRegister(0x00, 0x04, data); 
 */

 uint8_t cmd;
void ADS1220_WriteRegister(uint8_t reg_addr, uint8_t reg_num,uint8_t *data) {
    // if (reg_num < 1 || reg_num > 4) return;  // 错误处理
    SPI_CS_LOW();
    cmd = ADS1220_WREG | (((reg_addr << 2) & 0x0c) | ((reg_num - 1) & 0x03));   
    ADS1220_SPI_ReadWriteByte(cmd);  // 写寄存器命令 0100 rrnn
    while(reg_num--) {//往寄存器rr
        ADS1220_SPI_ReadWriteByte(*data++);
    }
    SPI_CS_HIGH();
}
```

![image](https://github.com/user-attachments/assets/fd113bc8-9c3c-4d1a-be79-9f3e0926e25a)

解释:
![image](https://github.com/user-attachments/assets/655872c7-820d-4c20-80d1-fe6b98d70c80)

上图为初始化函数发送的数据,以下为初始化函数
![image](https://github.com/user-attachments/assets/aa14ad83-c00b-4fcd-b437-50e5f73b5f45)


```
void ADS1220_Init(void) {
    SPI_CS_HIGH();  // 初始置高CS
    SPI_SCK_LOW();  // 空闲时钟低电平

    ADS1220_WriteCommand(ADS1220_RESET);        // 复位芯片
    SPI_DELAY(1);
    
    uint8_t config[] = {
        0x00, // REG0: AIN0+AIN1差分，增益1
        0x14, // REG1: 330SPS,连续采样
        0xE0, // REG2: 50Hz抑制
        0x00  // REG3: 禁用IDAC
    };
    ADS1220_WriteRegister(0x00,4,config);//0100 0000

    // 启动连续转换
    ADS1220_WriteCommand(ADS1220_START);        // 启动芯片
}
```
**github开源链接：**
   https://github.com/JourneyXuu/ADS1220
调试通讯成功，由于缺少射频座子就不焊了，提供完整调试代码
![image](https://github.com/user-attachments/assets/07ec06cc-4ae7-49ae-8d0d-11328f5f4629)



## **注意事项**
TL431有两种形式
#### **1. TI的TL431**

**1.1 TL431封装**

![image](https://github.com/user-attachments/assets/9e387060-6784-44c3-8c79-d20e27cacb6a)


**1.2 国内原产的TL431基本都是TI的TL432封装**

![image](https://github.com/user-attachments/assets/9a05a5d4-b9eb-4529-a187-3494b0fe99f6)

  
 ```
 CATHODE:阴极
 REF:参考极（2.5V）
 ANODE:阳极
 ```
![image](https://github.com/user-attachments/assets/2c98e8ca-1c6e-4e1a-9312-6435b90fca34)

   注意：下面是我绘制的第一版，第一版有错误，导致短路，电流大，第二版是对的
           
**1.2.1 第一版**
![image](https://github.com/user-attachments/assets/d282372f-d623-4991-8a4c-e9d5713fadb0)

**1.2.2 第二版**
![image](https://github.com/user-attachments/assets/a8be0e96-a066-4a75-8945-502cca513bdd)



## **实物图**
此处可放入组装完成后完整实物图
图1：正面图

![image](https://github.com/user-attachments/assets/5aeaa8af-be2b-4094-97c0-c7484c423dd4)

 
图2：正反面图

![image](https://github.com/user-attachments/assets/b11b5453-7a36-43a8-b081-84966ca82c9c)


## **电源测试**
不知道为啥，可能是示波器的探头有点老，导致噪声非常大
图1：开关电源TPS536201输出纹波

![image](https://github.com/user-attachments/assets/6e4a5981-ced3-4f38-9f06-9f62f9dfdb92)

图2：LDO输出纹波，经过π型滤波后

![image](https://github.com/user-attachments/assets/484f77ec-1f13-4d4f-9450-98ef4f4991cc)


 
 
## 参考链接：
ads1220的github参考链接：
https://github.com/Protocentral/Protocentral_ADS1220?tab=readme-ov-file
buck电路系统函数csdn链接：
https://blog.csdn.net/weixin_42005993/article/details/124056723?ops_request_misc=&request_id=&biz_id=102&utm_term=buck%E7%94%B5%E8%B7%AF%E7%9A%84%E4%BC%A0%E9%80%92%E5%87%BD%E6%95%B0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-5-124056723.142^v102^pc_search_result_base7&spm=1018.2226.3001.4187
环路增益csdn链接：
https://blog.csdn.net/qq_34181877/article/details/123558106#:~:text=%E7%8E%AF%E8%B7%AF%E5%A2%9E%E7%9B%8A%E5%AE%9A%E4%B9%89%E4%B8%BA%20T%28s%29%3DG%28s%29H%28s%29%EF%BC%8C%E6%98%AF%E7%8E%AF%E8%B7%AF%E4%B8%AD%E6%89%80%E6%9C%89%E7%8E%AF%E8%8A%82%E7%9A%84%E4%B9%98%E7%A7%AF%E3%80%82%20%E5%BD%93%E7%8E%AF%E8%B7%AF%E5%A2%9E%E7%9B%8A%E7%9A%84%E5%B9%85%E5%80%BC%20%7CT%28S%29%7C%3E%3E1,%E6%97%B6%EF%BC%8C%E6%9C%89%201%2BT%28S%29%E2%89%88T%28S%29%EF%BC%8C%E5%9B%A0%E6%AD%A4%20C%28s%29%2FR%28s%29%3D1%2FH%28s%29%EF%BC%8C%E5%8D%B3%E8%BE%93%E5%87%BA%E4%BB%85%E4%B8%8E%E5%8F%8D%E9%A6%88%E7%B3%BB%E6%95%B0%20H%28s%29%20%E6%9C%89%E5%85%B3%E3%80%82
ads1220代码开发：
https://blog.csdn.net/weixin_45165549/article/details/127892341
