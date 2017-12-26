#ifndef __Flash_25Q16_H__
#define __Flash_25Q16_H__

uint32_t SpiFlash_ReadMidDid(void);
void SpiFlash_ChipErase(void);
void SpiFlash_ChipSectorErase(uint32_t StartAddress);
uint32_t SpiFlash_ReadStatusReg1(void);
void SpiFlash_WaitReady(void);
void SpiFlash_PageProgram(uint8_t *DataBuffer, uint32_t StartAddress, uint32_t ByteCount);
void SpiFlash_ReadData(uint8_t *DataBuffer0, uint32_t StartAddress, uint32_t ByteCount);
void SPItest(uint32_t Counter);
#endif
