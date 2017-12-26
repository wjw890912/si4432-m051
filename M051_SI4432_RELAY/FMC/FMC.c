// File Name:DrvFMC.C
// Author:小ARM菜菜
// Date: 2012年
 //Q Q:925295580
#include "DrvSYS.h"
#include "DrvFMC.h"
#include "FMC.h"
 /******************************************************************************************
 ****
 ****
 ****
 ****	         DATA FLASH操作
 ****
 ****
 ****
 ******************************************************************
 **********************************************************************************************/
 void initFMC()
 {
 	 //API要求关闭寄存器保护
DrvSYS_UnlockProtectedReg();//关闭寄存器保护
DrvFMC_EnableISP();//开启ISP
DrvSYS_LockProtectedReg();//开启寄存器保护
 
 }

 void write_ISP_DATA_FLASH(uint32_t  ADDR,uint32_t DATA )
 {
 
      DrvSYS_UnlockProtectedReg();//关闭寄存器保护
	  DrvFMC_Write(ADDR, DATA);
	  DrvSYS_LockProtectedReg();//开启寄存器保护
 
 }
 uint32_t read_ISP_DATA_FLASH(uint32_t ADDR)
 {
 		 uint32_t da;
 
 	  DrvSYS_UnlockProtectedReg();//关闭寄存器保护
	  DrvFMC_Read( ADDR, &da);
	  DrvSYS_LockProtectedReg();//开启寄存器保护
 		 return da;
 }
 uint32_t Read_UID_M0(uint32_t addr)
 {			
 			  uint32_t da;
			  	addr=addr;
 	DrvSYS_UnlockProtectedReg();//关闭寄存器保护
DrvFMC_ReadUID(addr, &da);

	  DrvSYS_LockProtectedReg();//开启寄存器保护
	return da;

 }
 void Erase_ISP_DATA_FLASH(uint32_t ADDR)
 {
 
 	
 	  DrvSYS_UnlockProtectedReg();//关闭寄存器保护
      DrvFMC_Erase(ADDR);
	  DrvSYS_LockProtectedReg();//开启寄存器保护
 
 }

 unsigned char Lode_Authenticated_Add(uint32_t *padd_group)
 {
 			   uint32_t temp;
 
 	
		
		   
		       temp  = 	read_ISP_DATA_FLASH(ADD1) ;
			   //if(temp!=0xFFFFFFFF){
			   *padd_group = temp;
				 return 1;
			   //}
			 /*  temp  = 	read_ISP_DATA_FLASH(ADD1) ;
			   if(temp!=0xFFFFFFFF){
			   *(padd_group+1) = temp;
			   }
			   temp  = 	read_ISP_DATA_FLASH(ADD2) ;
			   if(temp!=0xFFFFFFFF){
			   *(padd_group+2) = temp;
			   }*/
			 /*  temp  = 	read_ISP_DATA_FLASH(ADD3) ;
			   if(temp!=0xFFFFFFFF){
			   *add_group = temp;
			   }
			   temp  = 	read_ISP_DATA_FLASH(ADD4) ;
			   if(temp!=0xFFFFFFFF){
			   *add_group = temp;
			   }
			   temp  = 	read_ISP_DATA_FLASH(ADD5) ;
			   if(temp!=0xFFFFFFFF){
			   *add_group = temp;
			   }
			   temp  = 	read_ISP_DATA_FLASH(ADD6) ;
			   if(temp!=0xFFFFFFFF){
			   *add_group = temp;
			   }
			   temp  = 	read_ISP_DATA_FLASH(ADD7) ;
			   if(temp!=0xFFFFFFFF){
			   *add_group = temp;
			   }
		
				  */
		
		
		
			


// 	  return 1;
 
 } 
 unsigned char Save_Authentication_Add(uint32_t data)
 {
 

		Erase_ISP_DATA_FLASH(ADD0);
 	   //if(read_ISP_DATA_FLASH(ADD0)==0xFFFFFFFF)
	  // {
	   write_ISP_DATA_FLASH(ADD1,data);
	   	 return 1;
	  // }
	   //else
	 /*  if(read_ISP_DATA_FLASH(ADD1)==0xFFFFFFFF)
	   {
	   write_ISP_DATA_FLASH(ADD1,data);
	   	   return 1;
	   }
	   else
	   if(read_ISP_DATA_FLASH(ADD2)==0xFFFFFFFF)
	   {
	   write_ISP_DATA_FLASH(ADD2,data);
	   		return 1;
	   }
 	   */
 
 //	return 0;
 

 
 }
