#ifndef __ADS1220_H__
#define __ADS1220_H__

#include "main.h"
#include "stm32f407xx.h"

extern int adc_data;

#define ADS1220_RESET 0X06
#define ADS1220_START 0X08
#define ADS1220_POWERDOWN 0X02
#define ADS1220_RDATA 0X10
#define ADS1220_RREG 0X20
#define ADS1220_WREG 0X40


/* 引脚定义 - 根据实际接线修改 */
/*
SCK     PC10
MOSI    PC12
MISO    PC11
CS      PC9
DRDI    PC8
*/
#define SIM_SPI_PORT     GPIOC
#define SPI_SCK_PIN      ADS_SCK_Pin
#define SPI_MOSI_PIN     ADS_MOSI_Pin
#define SPI_MISO_PIN     ADS_MISO_Pin
#define SPI_CS_PIN       ADS_CS_Pin
#define SPI_DRDI_PIN     ADS_DRDY_Pin

/* SPI时序延时（根据主频调整）*/
#define SPI_DELAY(x)  HAL_Delay(x)

/* GPIO操作宏 */
#define SPI_SCK_HIGH()  HAL_GPIO_WritePin(SIM_SPI_PORT, SPI_SCK_PIN, GPIO_PIN_SET)
#define SPI_SCK_LOW()   HAL_GPIO_WritePin(SIM_SPI_PORT, SPI_SCK_PIN, GPIO_PIN_RESET)
#define SPI_MOSI_HIGH() HAL_GPIO_WritePin(SIM_SPI_PORT, SPI_MOSI_PIN, GPIO_PIN_SET)
#define SPI_MOSI_LOW()  HAL_GPIO_WritePin(SIM_SPI_PORT, SPI_MOSI_PIN, GPIO_PIN_RESET)
#define SPI_CS_HIGH()   HAL_GPIO_WritePin(SIM_SPI_PORT, SPI_CS_PIN, GPIO_PIN_SET)
#define SPI_CS_LOW()    HAL_GPIO_WritePin(SIM_SPI_PORT, SPI_CS_PIN, GPIO_PIN_RESET)

#define SPI_MISO_READ() HAL_GPIO_ReadPin(SIM_SPI_PORT, SPI_MISO_PIN)

void ADS1220_Init(void);
uint8_t ADS1220_SPI_ReadWriteByte(uint8_t tx_data) ;
void ADS1220_WriteCommand(uint8_t cmd);
void ADS1220_WriteRegister(uint8_t reg_addr, uint8_t reg_num,uint8_t *data);
int32_t ADS1220_ReadData(void);


#endif









