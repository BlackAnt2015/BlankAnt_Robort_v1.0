#ifndef _COMMON_H_
#define _COMMON_H_

//***************************************头文件包含区***********************************************

#include "stm32f10x.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BSP_Led.h"
#include "BSP_Timer.h"
#include "BSP_Systick.h"
#include "BSP_Uart.h"
#include "BSP_Pwm.h"
#include "BSP_Pantilt.h"
#include "BSP_ADC.h"


//***************************************变量类型定义 ***********************************************
#define uchar 	unsigned char
#define uint8 	unsigned char
#define uint16 	unsigned short
#define uint32 	unsigned int
#define uint  	unsigned int
#define ulong 	unsigned long

/* The definition of protocol */
typedef struct
{
	uint8 Frame_Head;       //0xff
	uint8 Addr;             //robort local address
	uint8 Msg_L;            //Data[] length LSB
	uint8 Msg_H;            //Data[] length MSB
	uint8 Cmd;              //Command type
	uint8 *pMsg;    		//msg buffer size
	uint8 Crc_L;            //crc check LSB
	uint8 Crc_H;            //crc check MSB
}App_Robort_Dat_Tag;

#endif

