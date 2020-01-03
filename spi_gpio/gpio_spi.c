#include "s3c24xx.h"
#include "udelay.h"
void GPIO_SPI_Init()
{
/*
 *GPF1作为OLED片选引脚，设置为输出；
 */
 
  GPFCON &= ~(3<<(1*2));
  GPFCON |= (1<<(1*2));
  GPFDAT |= (1<<1);
	
/*
 *GPG2作为FLASH片选引脚，设置为输出；
 *GPG4作为OLED的数据(Data)/命令(Command)选择引脚，设置为输出；
 *GPG5作为SPI的MISO，设置为输入；
 *GPG6作为SPI的MOSI，设置为输出；
 *GPG7作为SPI的时钟CLK，设置为输出；		
 */
	GPGCON &= ~((3<<(2*2)) | (3<<(4*2)) | (3<<(5*2)) | (3<<(6*2)) | (3<<(7*2)));
    GPGCON |= ((1<<(2*2)) | (1<<(4*2)) | (1<<(6*2)) | (1<<(7*2)));
    GPGDAT |= (1<<2);
}

static void SetCLK(int polar)
{
	if(0 == polar)
	{
		GPGDAT &= ~(1<<7);
	}
	else{
	GPGDAT |= (1<<7);
	}
}

static int GetMiso()
{
	if(GPGDAT & (1<<5))
		return 1;
	else
		return 0;
}
/*spi mode0 cpol=0 cpha=0*/
void SPI_SendByte(unsigned char c)
{
	int i;
	for(i = 0; i < 8; i++)
	{
		SetCLK(0);
		if(c & (1<<7))
		{
			GPGDAT |= (1<<6);
		}
		else{
			GPGDAT &= ~(1<<6);
		}
		SetCLK(1);
		c <<= 1;
		udelay(5);
	}
}

/**/
unsigned char SPI_RevByte()
{
	int data = 0;
	int i;
	for(i = 0; i < 8; i++)
	{
		data <<= 1;
		SetCLK(0);
		if(GetMiso())
		{
			data |= 1;
		}
		udelay(5);
		SetCLK(1);
		udelay(5);
	
		
	}
	return data;
}












