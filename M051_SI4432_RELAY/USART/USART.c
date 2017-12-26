#include <stdio.h>
#include "M051Series.h"
#include "DrvGPIO.h"
#include "DrvSYS.h"
#include "DrvUART.h"
#include "DrvFMC.h"
#include "USART.h"

extern uint32_t  u32Count;//串口计数
extern uint8_t   uart_flage;
extern uint8_t   tabuart[10];//接收串口数据
STR_UART_T  config;	//串口配置
void funcallback(uint32_t uartstart)
 {		   
		UART_T * tUART;
 		    tUART = (UART_T *)(uint32_t)UART0 ; 
 		  if(uartstart!=NULL)
		  {

	             tabuart[u32Count] = tUART->DATA;	                       
         	     u32Count++;	  //接受计数
			  if(u32Count==7)	  //接受数据
				 {
				 u32Count=0;	  //串口计数清零
				 uart_flage=1;//接受完毕
				 }   
		   

		  } 
					
					
					  
		   
 
 
 }
 void inituart()
 {


      DrvSYS_SetIPClock(E_SYS_UART0_CLK,1);//使能UART0时钟
	
      while(DrvSYS_SetClockDivider(E_SYS_HCLK_DIV, 0)!=FALSE); //1分频HCLK
      while(DrvSYS_SetClockDivider(E_SYS_UART_DIV, 0)!=FALSE); //1分频UART
	  DrvSYS_SelectIPClockSource(E_SYS_UART_CLKSRC, 0);//UART选择外部12Mhz的时钟源
	  DrvGPIO_InitFunction(E_FUNC_UART0);//复用IO编程UART模式
		   /*关闭所有串口中断*/
      DrvUART_DisableInt (UART_PORT0,DRVUART_WAKEUPINT|
                                        DRVUART_RLSINT|
								        DRVUART_MOSINT|
								       DRVUART_THREINT| 
								       DRVUART_TOUTINT);	 
									
    
	 
				/*设置串口参数*/
		config.u32BaudRate=9600;//波特率38400
		config.u8cDataBits=DRVUART_DATABITS_8 ;//数据位8位
		config.u8cStopBits=DRVUART_STOPBITS_1; //停止位1位
		config.u8cParity=DRVUART_PARITY_NONE ; //NONE校验
		config.u8cRxTriggerLevel=DRVUART_FIFO_1BYTES;//接受FIFO 8字节

    DrvUART_Open(UART_PORT0, &config);//开启UART端口

			/*安装回调函数，开启串口数据中断，事实证明，此函数调用之前必须使用开启端口命令*/
    DrvUART_EnableInt(	UART_PORT0,DRVUART_RDAINT,funcallback);
}


