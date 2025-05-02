#include "ads1220.h"

int adc_data;

/* 初始化配置 */
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


/* @brief: 读取数据
 * @return: 返回读取的24位数据
 */
int32_t ADS1220_ReadData(void) {
    uint8_t rx_buf[3] = {0};
    int32_t result = 0;
    
    SPI_CS_LOW();
    ADS1220_SPI_ReadWriteByte(ADS1220_RDATA); // RDATA命令
    rx_buf[0] = ADS1220_SPI_ReadWriteByte(0xFF);
    rx_buf[1] = ADS1220_SPI_ReadWriteByte(0xFF);
    rx_buf[2] = ADS1220_SPI_ReadWriteByte(0xFF);
    SPI_CS_HIGH();

    result = (rx_buf[0] << 16) | (rx_buf[1] << 8) | rx_buf[2];
    if(result & 0x00800000) { // 符号位扩展
        result |= 0xFF000000;
    }
    return result;
}



