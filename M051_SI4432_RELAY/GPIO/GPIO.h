#ifndef _GPIO_H
#define _GPIO_H


#define GET_SDO   DrvGPIO_GetBit(E_PORT0, E_PIN6)

#define GET_NIRQ   DrvGPIO_GetBit(E_PORT3, E_PIN2)

#define SDI_UP    DrvGPIO_SetBit(E_PORT0, E_PIN5) 
#define SDI_DOWN  DrvGPIO_ClrBit(E_PORT0, E_PIN5)

#define SCK_UP    DrvGPIO_SetBit(E_PORT0, E_PIN7) 
#define SCK_DOWN  DrvGPIO_ClrBit(E_PORT0, E_PIN7)

#define nSEL_UP   DrvGPIO_SetBit(E_PORT0, E_PIN4) 
#define nSEL_DOWN DrvGPIO_ClrBit(E_PORT0, E_PIN4)

#define SDN_UP    DrvGPIO_SetBit(E_PORT4, E_PIN1) 
#define SDN_DOWN  DrvGPIO_ClrBit(E_PORT4, E_PIN1)


#define LED_UP    DrvGPIO_SetBit(E_PORT2, E_PIN7) 
#define LED_DOWN  DrvGPIO_ClrBit(E_PORT2, E_PIN7)

#define GET_BUTTON  DrvGPIO_GetBit(E_PORT4, E_PIN4)	


#define  MOS1_OPEN    DrvGPIO_SetBit(E_PORT1, E_PIN6) 
#define  MOS1_CLOSE   DrvGPIO_ClrBit(E_PORT1, E_PIN6)




		   
















	 
void initGPIO(void);
#endif

