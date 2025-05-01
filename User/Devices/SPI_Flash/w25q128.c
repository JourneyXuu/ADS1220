#include "w25q128.h"

/*
 *@brief:      W25Q128 SPI Flash初始化
*/
void flash_spi_init(void)
{
    FLASH_CS_SET(); 	// 片选拉高
    FLASH_SCK_SET(); 	// 时钟拉高
}
/*
 *@brief:spi写命令后读
*/
// uint8_t spi_read_write_byte(uint8_t dat)
uint8_t flash_read_write_byte(uint8_t dat)
{
	uint8_t i;
	uint8_t rxData = 0;

	for(i = 0; i < 8; i++)
	{
        FLASH_SCK_CLR(); 
		delay_us(1);
		
		//数据发送
		if(dat & 0x80)  {   FLASH_MOSI_SET();}
		else            {   FLASH_MOSI_CLR();}
		dat <<= 1;
		delay_us(1);

        FLASH_SCK_SET();
		delay_us(1);
		//数据接收
		rxData <<= 1;
		if( FLASH_MISO_ON() )
		{
			rxData |= 0x01;
		}
		delay_us(1);
	}
    FLASH_SCK_SET(); 
    
	return rxData;
}

//读取芯片ID          
//读取设备ID
/*
 *@brief:读取设备ID
*/
uint16_t Flash_spi_readID(void)
{
    uint16_t  temp = 0;     
    //将CS端拉低为低电平     
    FLASH_CS_CLR(); 
    //发送指令90h    
    flash_read_write_byte(0x90);
    //发送地址  000000H  
    flash_read_write_byte(0x00);
    flash_read_write_byte(0x00);
    flash_read_write_byte(0x00);

    //接收数据
    //接收制造商ID
    temp |= flash_read_write_byte(0xFF)<<8;
    //接收设备ID
    temp |= flash_read_write_byte(0xFF);  
    FLASH_CS_SET();
    return temp;
}
/*
 *@biref:发送写使能
*/
void Flash_write_enable(void)
{
    FLASH_CS_CLR();
    flash_read_write_byte(0x86);
    FLASH_CS_SET();
}
/*
 *@biref:检测线路是否繁忙
*/
void Flash_wait_busy(void)
{
    unsigned char byte = 0;
    do
    { 
        //拉低CS端为低电平
        FLASH_CS_CLR();
        //发送指令05h                     
        flash_read_write_byte(0x05);
        //接收状态寄存器值
        byte = flash_read_write_byte(0Xff);       
        //恢复CS端为高电平
        FLASH_CS_SET();      
     //判断BUSY位是否为1 如果为1说明在忙，重新读写BUSY位直到为0   
    }while( ( byte & 0x01 ) == 1 );  
}


/**********************************************************
 * 函 数 名 称：GD25Q32_erase_sector
 * 函 数 功 能：擦除一个扇区
 * 传 入 参 数：addr=擦除的扇区号
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：addr=擦除的扇区号，范围=0~15
**********************************************************/
void GD25Q32_erase_sector(uint32_t addr)   
{
        //计算扇区号，一个扇区4KB=4096
        addr *= 4096;
        GD25Q32_write_enable();  //写使能   
        GD25Q32_wait_busy();     //判断忙，如果忙则一直等待
        //拉低CS端为低电平
        W25QXX_CS_ON(0);  
        //发送指令20h                                     
        spi_read_write_byte(0x20);
        //发送24位扇区地址的高8位                
        spi_read_write_byte((uint8_t)((addr)>>16));      
        //发送24位扇区地址的中8位    
        spi_read_write_byte((uint8_t)((addr)>>8));   
        //发送24位扇区地址的低8位    
        spi_read_write_byte((uint8_t)addr);
        //恢复CS端为高电平  
        W25QXX_CS_ON(1);                  
        //等待擦除完成                                                  
        GD25Q32_wait_busy();   
}

/**********************************************************
 * 函 数 名 称：GD25Q32_write
 * 函 数 功 能：写数据到GD25Q32进行保存
 * 传 入 参 数：buffer=写入的数据内容        addr=写入地址        numbyte=写入数据的长度
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
**********************************************************/
void GD25Q32_write(uint8_t* buffer, uint32_t addr, uint16_t numbyte)
{    
    unsigned int i = 0;
    //擦除扇区数据
    GD25Q32_erase_sector(addr/4096);
    //写使能 
    GD25Q32_write_enable();  
    //忙检测  
    GD25Q32_wait_busy();    
    //写入数据
    //拉低CS端为低电平
    W25QXX_CS_ON(0);         
    //发送指令02h                              
    spi_read_write_byte(0x02);                 
    //发送写入的24位地址中的高8位   
    spi_read_write_byte((uint8_t)((addr)>>16));  
    //发送写入的24位地址中的中8位
    spi_read_write_byte((uint8_t)((addr)>>8));   
    //发送写入的24位地址中的低8位
    spi_read_write_byte((uint8_t)addr);   
    //根据写入的字节长度连续写入数据buffer
    for(i=0;i<numbyte;i++)
    {
        spi_read_write_byte(buffer[i]);  
    }
    //恢复CS端为高电平
    W25QXX_CS_ON(1);
    //忙检测 
    GD25Q32_wait_busy();      
}

/**********************************************************
 * 函 数 名 称：GD25Q32_read
 * 函 数 功 能：读取GD25Q32的数据
 * 传 入 参 数：buffer=读出数据的保存地址  read_addr=读取地址   read_length=读去长度
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
**********************************************************/
void GD25Q32_read(uint8_t* buffer,uint32_t read_addr,uint16_t read_length)   
{ 
        uint16_t i;                   
        //拉低CS端为低电平
        W25QXX_CS_ON(0);    
        //发送指令03h        
        spi_read_write_byte(0x03);  
        //发送24位读取数据地址的高8位                         
        spi_read_write_byte((uint8_t)((read_addr)>>16));     
        //发送24位读取数据地址的中8位      
        spi_read_write_byte((uint8_t)((read_addr)>>8));   
        //发送24位读取数据地址的低8位
        spi_read_write_byte((uint8_t)read_addr);   
        //根据读取长度读取出地址保存到buffer中
        for(i=0;i<read_length;i++)
        { 
            buffer[i]= spi_read_write_byte(0XFF);  
        }
        //恢复CS端为高电平
        W25QXX_CS_ON(1);                                    
}





