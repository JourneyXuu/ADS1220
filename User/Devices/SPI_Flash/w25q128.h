#ifndef __W25Q128_H__
#define __W25Q128_H__

#include "main.h"
#include "sys.h"
#include "gpio.h"

// CS    --  PA4
// SCK   --  PA5
// MOSI  --  PA7
// MISO  --  PA6

//位带操作
// #define W25QXX_CS_ON(x)			PBout(4)=x
#define FLASH_CS_SET()		    PBout(4)=1
#define FLASH_CS_CLR()		    PBout(4)=0

// #define W25QXX_SCK_ON(x)		PBout(5)=x
#define FLASH_SCK_SET()		PBout(5)=1
#define FLASH_SCK_CLR()		PBout(5)=0

#define FLASH_MISO_ON()		PBin(6) //读取MISO引脚的值

// #define W25QXX_MOSI_ON(x)		PBout(7)=x
#define FLASH_MOSI_SET()		PBout(7)=1
#define FLASH_MOSI_CLR()		PBout(7)=0

void flash_spi_init(void);
uint8_t flash_read_write_byte(uint8_t dat);


uint8_t spi_read_write_byte(uint8_t dat);
uint16_t GD25Q32_readID(void);
void GD25Q32_write_enable(void);
void GD25Q32_wait_busy(void);
void GD25Q32_erase_sector(uint32_t addr);
void GD25Q32_write(uint8_t* buffer, uint32_t addr, uint16_t numbyte);
void GD25Q32_read(uint8_t* buffer,uint32_t read_addr,uint16_t read_length);




#endif




