#include "sdk_project_config.h"
#include "string.h"
#include<stdint.h>
#define EEPROM_SIZE 512U
#define page_size 8U
#define total_pages (EEPROM_SIZE/page_size)
#define EEPROM_ADDR (0xA0U >>1) //0x50
lpi2c_master_state_t lpi2c1MasterState;
void EEPROM_Write(uint16_t memAddr,  uint8_t *data,   uint8_t len){
	uint8_t slaveAddr;
	uint8_t wordAddr;
	slaveAddr = EEPROM_ADDR | ((memAddr >> 7U) & 0x02U);
	wordAddr = (uint8_t)(memAddr & 0xFFU);
	uint8_t buf[16];
	buf[0] = wordAddr;
	for(uint8_t i=0;i<len;i++)
		buf[i+1]=data[i];
	LPI2C_DRV_MasterSetSlaveAddr(0, slaveAddr, false);
	LPI2C_DRV_MasterSendDataBlocking(0,buf,len+1,true,100);
	OSIF_TimeDelay(10);
}
void EEPROM_Read(uint16_t memAddr,uint8_t *data,uint8_t len){
    uint8_t slaveAddr;
    uint8_t wordAddr;
    slaveAddr = EEPROM_ADDR | ((memAddr >> 7U) & 0x02U);
    wordAddr = (uint8_t)(memAddr & 0xFFU);
    LPI2C_DRV_MasterSetSlaveAddr(0, slaveAddr, false);
	LPI2C_DRV_MasterSendDataBlocking(0,&wordAddr,1,false,100);
	LPI2C_DRV_MasterReceiveDataBlocking(0,data,len,true,100);
}
void NvM_ErasePage(uint8_t PageNum)
{
    uint16_t StartAddress;
    uint8_t EraseData[page_size];
    uint8_t ReadData[page_size];
    PINS_DRV_WritePin(PTD,16,1);
    if (PageNum >= total_pages)
    {
        PINS_DRV_WritePin(PTD,16,0);
        return;
    }
    StartAddress = (uint16_t)PageNum * page_size;
    for (uint8_t i = 0U; i < page_size; i++)
    {
        EraseData[i] = 0xFFU;
    }
    EEPROM_Write(StartAddress, EraseData, page_size);

    for (uint8_t i = 0U; i < page_size; i++)
    {
        if (ReadData[i] != 0xFFU)
        {
            PINS_DRV_WritePin(PTD,16,0);
            return;
        }

    }
}
int main(void)
{
  CLOCK_DRV_Init(&clockMan1_InitConfig0);
  PINS_DRV_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);
  LPI2C_DRV_MasterInit(0,&lpi2c0_MasterConfig0,&lpi2c1MasterState);
  NvM_ErasePage(2U);
  while(1)
  {

  }
}
