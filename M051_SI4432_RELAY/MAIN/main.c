/*
 *文件名：MAIN.C
 *
 *作者：小ARM菜菜
 *
 * Q Q:925295580     ^_^



 对应2012年12月25日的刘洪武板子
 *
*/


#include <stdio.h>
#include "M051Series.h"
#include "DrvSYS.h"
#include "DrvUART.h"
#include "DrvFMC.h"
#include "DrvGPIO.h"
#include "main.h"
#include "USART.h"
#include "GPIO.h"
#include "DrvTIMER.h"
#include"SI4432.H"
#include "FMC.H"
#include "SI4432_proto.h"


  
   
uint8_t RX_BUF[100];
uint32_t UID;
uint8_t ID_TIME_OUT_EN=0;
uint8_t ID_TIME_OUT=0;
uint32_t Authenticated[3];
extern  unsigned char tx_timeout_en=0,tx_timeout=0;	//超时变量

 uint8_t SI433_ST1=0x88;;
 uint8_t SI433_ST2;
 uint8_t SI433_ST3=0x88;



 void time1_callback(uint32_t pad)
{


		 if(pad)
		 {


		 }

}

void time0_callback(uint32_t pad)
{


		 if(pad)
		 {
			 
			   if(tx_timeout_en)
			   {
			   	  tx_timeout++;
			   }

			   if(ID_TIME_OUT_EN ){

					  ID_TIME_OUT++;
					  
					  }

          }


}


//滑动平均滤波算法（递推平均滤波法）
int FilterI=0;
//ADNum为获得的AD数
//n为数组value_buf[]的元素个数。该函数主要被调用，利用参数的数组传值
int GlideFilterAD(int value_buf[],int n,int ADNum)
{
  int sum=0;
  int count;
  value_buf[FilterI++]=ADNum;
  if(FilterI==n)
   { FilterI=0; //先进先出，再求平均值
  for(count=0;count<n;count++)
    sum+=value_buf[count];
  return (int)(sum/n);
   }
}




int  main(void)
{

uint16_t adc;
uint16_t adc_buf[100];
uint16_t result;
	
unsigned int sum;//定义32位的无符号变量
unsigned char buf[10]; //8位无符号变量
unsigned char res;//8位无符号变量
//求1+2+3=6的补码

	   buf[0]=1;
	   buf[1]=2;
	   buf[2]=3;


	  //求和
	  sum =	 buf[0] + buf[1] + buf[2];
	  sum = ~sum;  //取反
	  sum+=1;	  //+1
	  sum=sum&0x000000ff;//保留最低位
	  res = sum; //取得校验值





		res++;



//initsys();
while(1)
{
		   adc=4096;
  result = GlideFilterAD((int*)adc_buf,10,(int)adc);
	   adc_buf[80]=result ;

	    adc_buf[80]=  sum;

		adc_buf[80]=  res;
}											                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    

}



 /*---------------------------------------------------------------------------------------------------------*/
/* initalization system  function  系统初始化                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/  
 void initsys()
 {
 	
	while(DrvSYS_SetOscCtrl(E_SYS_XTL12M, 1)!=FALSE);  //使能外部12MHZ晶振
    while( DrvSYS_SelectHCLKSource(0) !=FALSE);  //HCLK=12MHZ
	DrvSYS_SetClockDivider(E_SYS_HCLK_DIV , 0);  //HCLK1分频
	while(DrvSYS_SelectSysTickSource(0)!=FALSE);  //选择系统嘀嗒时钟源为外部12MHZ晶振
 	
 }

 void initTMR0()
 {
  DrvSYS_SetIPClock(E_SYS_TMR0_CLK,1); //使能始终
  DrvSYS_SelectIPClockSource(E_SYS_TMR0_CLKSRC,2 );//这个TIM0是接到APB总线，不可以用外部晶振，手册的是错误的，应该看下面的APBPCLK的时钟
  DrvTIMER_Init();

  DrvTIMER_Open(E_TMR0,10,E_PERIODIC_MODE);	//100MS
  DrvTIMER_EnableInt(E_TMR0);  
  DrvTIMER_SetTimerEvent(E_TMR0, 1, time0_callback, 1);//1s
  DrvTIMER_Start(E_TMR0);
 
 }
  void initTMR1()
 {
  DrvSYS_SetIPClock(E_SYS_TMR1_CLK,1); //使能始终
  DrvSYS_SelectIPClockSource(E_SYS_TMR1_CLKSRC,2 );//这个TIM1是接到APB总线，不可以用外部晶振，手册的是错误的，应该看下面的APBPCLK的时钟
  DrvTIMER_Init();
  DrvTIMER_Open(E_TMR1,10,E_PERIODIC_MODE);	//10MS
  DrvTIMER_EnableInt(E_TMR1);  
  DrvTIMER_SetTimerEvent(E_TMR1, 2, time1_callback, 1);//20ms事件发
  DrvTIMER_Start(E_TMR1);
 
 }





























