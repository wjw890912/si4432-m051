// File Name:SI4432_proto.C
// Author:小ARM菜菜&王德壮
// Date: 2012年
 //Q Q:925295580

#include "SI4432_proto.h"
#include "string.h"
#include "SI4432.H"
#include <stdio.h>
#include "M051Series.h"
#include "DrvSYS.h"
#include "DrvGPIO.h"
#include "GPIO.h"
#include "stdint.h"
#include "FMC.H"

uint32_t Authentication_ID=0;
extern uint32_t Authenticated[3];
SI4432Ctrl_Frame RX_SI4432_HADE;
unsigned char *PACK_HEADER = "HD";         /*ASCII码分别为 0X48 0X44*/
extern uint32_t UID;

void Light_State_Retrn (SI4432Ctrl_Frame *pFram,eChan_Num Channel,uint8_t Light_Bright)
{			static	uint8_t n;

					
              static SI4432Ctrl_Frame TX_STRUCT;
			   uint8_t Data[10]={0};
			   uint8_t  TX_STATE=0;

			    n=0;

				  TX_STRUCT.Switch_Addr[0]=pFram->Switch_Addr[0];
				  TX_STRUCT.Switch_Addr[1]=pFram->Switch_Addr[1];
				  TX_STRUCT.Switch_Addr[2]=pFram->Switch_Addr[2];
				  TX_STRUCT.Switch_Addr[3]=pFram->Switch_Addr[3];

				          
	              TX_STRUCT.Relay_Addr[0]=pFram->Relay_Addr[0]; 
				  TX_STRUCT.Relay_Addr[1]=pFram->Relay_Addr[1];
				  TX_STRUCT.Relay_Addr[2]=pFram->Relay_Addr[2];
				  TX_STRUCT.Relay_Addr[3]=pFram->Relay_Addr[3];
					  
		       TX_STRUCT.Dst_ID=Authenticated[0];
			   TX_STRUCT.Src_ID=UID;//本地ID
			   TX_STRUCT.Dev_Type=SWITCH_86;//设备类型


			   Data[0] =  Channel;

			   Data[1] =  0 ;
			   Data[2] =  4;

			   Data[3] = Light_Bright;

	send:	TX_STATE = SendCmd2SI4432(&TX_STRUCT, Data, 4);//发送成功
		    switch(TX_STATE)
			 {

			 	case TX_SUCCESS:{

						   break;	 }

				case TX_FAIL:{n++;if(n>2){return ;}goto send;}	//发送失败
				case TX_RSSI_CHANNLE_OCCUPANCY:{n++;if(n>2){return ;}goto send;}	//信道被占用
				case TX_TIMEOUT: {n++;if(n>2){return ;}goto send;}//超时

			 
			 
			 }




}


void SI4432_Process_86_cmd(eChan_Num channel,uint8_t Cmd)
{
	  switch(channel)
	  {
		case CHAN_1:{	
						 switch (Cmd)
						 {
						   case LIGHTCTRL_OPEN:{ 
				
							   	 
									MOS1_OPEN;
				
				                    Light_State_Retrn (&RX_SI4432_HADE,CHAN_1,100);
				
									break;
									    }
						   case LIGHTCTRL_CLOSE:{ 
						    
							
								   	MOS1_CLOSE;	  //关灯
									Light_State_Retrn (&RX_SI4432_HADE,CHAN_1,0);
				
									  break;
									  }
		 	 
		                  }

		
		
		
			
				 break;}

		

	  }

}
void Si4432_Process_86(uint8_t *pt_data,uint8_t leg)
{
		 
    			uint8_t cmd;
				cmd = *(pt_data+1);
			
			switch(*pt_data)
			{
				   case CHAN_1 : { SI4432_Process_86_cmd(CHAN_1, cmd);   break;}//一通道
			
			}




}



/*无线协议封装函数*/
unsigned char  SendCmd2SI4432(SI4432Ctrl_Frame *pFrame, uint8_t *pExt, uint8_t ExtLen)
{


	uint8_t sedbuf[50] = {0};

	uint8_t i = 0;
	SI4432Ctrl_Frame *pFrameBuf = pFrame;
	
	/*填写包头*/
	memcpy(sedbuf, PACK_HEADER, 2);


				  	/*处理变长部分*/
	if(ExtLen > 0)
	{
		memcpy(&sedbuf[23], pExt, ExtLen);
        pFrameBuf->Ext_Len = ExtLen;
	}
	else if(ExtLen == 0)
	{
		pFrameBuf->Ext_Len = ExtLen;
	}


	/*填写校验值*/
	pFrameBuf->Crc_Sum = 0;

	for(i=0; i<(20+ExtLen); i++)
	{
		pFrameBuf->Crc_Sum += sedbuf[i+2];
	}

	  /*拷贝帧*/
	memcpy(&sedbuf[2], pFrame, 20);

	/*发送*/ 
	return 	(tx_data(sedbuf, (23+ExtLen)));


}



/*解析无线协议帧函数*/
unsigned char RecvCmdFromSI4432(uint8_t *pBuf,uint8_t leg)
{
	 	SI4432Ctrl_Frame  *pFrameBuf = &RX_SI4432_HADE;

				  leg=leg;

	/*检测包头是否为"HD"*/
	if((pBuf[0] == 'H') && (pBuf[1] == 'D'))
	{
	
			pFrameBuf->	Switch_Addr[0] = pBuf[2];
			pFrameBuf->	Switch_Addr[1] = pBuf[3];
			pFrameBuf->	Switch_Addr[2] = pBuf[4];
			pFrameBuf->	Switch_Addr[3] = pBuf[5];


			pFrameBuf->	Relay_Addr[0] = pBuf[6];
			pFrameBuf->	Relay_Addr[1] = pBuf[7];
			pFrameBuf->	Relay_Addr[2] = pBuf[8];
			pFrameBuf->	Relay_Addr[3] = pBuf[9];

					

		    pFrameBuf->	Dst_ID =(((uint32_t)pBuf[13])<<24)+(((uint32_t)pBuf[12])<<16)+(((uint32_t)pBuf[11])<<8)+pBuf[10];//小段

			pFrameBuf->	Src_ID =(((uint32_t)pBuf[17])<<24)+(((uint32_t)pBuf[16])<<16)+(((uint32_t)pBuf[15])<<8)+pBuf[14];//小段

			pFrameBuf-> Dev_Type = (((uint16_t)pBuf[19])<<8)+pBuf[18];//小段

			pFrameBuf-> Ext_Len	 = 	pBuf[20]; //leg

			pFrameBuf-> Crc_Sum  =	(((uint16_t)pBuf[22])<<8)+pBuf[21];//小段



	if(pFrameBuf->Dst_ID != UID)
	{
		return 0;  //不是给本机的数据包
	}


	switch (pFrameBuf->Dev_Type)
	{
		case SWITCH_86:	{//86盒
						 //认证
		Lode_Authenticated_Add(Authenticated);//取出认证地址
       if((Authenticated[0]==pFrameBuf->Src_ID)||(Authenticated[1]==pFrameBuf->Src_ID)||(Authenticated[2]==pFrameBuf->Src_ID))
				 {
  	       Si4432_Process_86(&pBuf[23],	pFrameBuf-> Ext_Len);//数据处理
					}
	                     break;
	                     }


		case STM32_SWITCH:
	                 	{

					//	 if( (pBuf[23]==CHAN_ALL)&&(pBuf[24]==LIGHTCTRL_LEARN_OK ))	 //交换机返回的命令
					//	 {
						 
					   Save_Authentication_Add(pFrameBuf->Src_ID);
						Authenticated[0]=pFrameBuf->Src_ID;
						 
						// }
		   
						break;
						}
		default:
			break;
	}

	return 1;




		}
	return 0;//不是公司协议
}


