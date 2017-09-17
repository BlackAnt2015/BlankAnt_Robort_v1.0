#ifndef _BSP_UART_H
#define  _BSP_UART_H

#include "Common.h"

#define Tx_Array_Size 			 	 50	                //发送缓存区大小
#define Rx_Array_Size 			 	 50		              //接受缓存区大小

#define FRAME_HEAD_SIZE		1 //1字节
#define LOCAL_ADDR_SIZE     1
#define MASSAGE_H_SIZE      1
#define MASSAGE_L_SIZE      1
#define CMD_TYPE_SIZE       1
#define CRC_H_SIZE			1
#define CRC_L_SIZE			1
#define FRAME_INFO_SIZE     (FRAME_HEAD_SIZE+LOCAL_ADDR_SIZE+MASSAGE_H_SIZE+MASSAGE_L_SIZE+\
							 CMD_TYPE_SIZE+CRC_H_SIZE+CRC_L_SIZE)\


typedef enum
{
    STM32_UART1  = 0,
    STM32_UART2,
    STM32_UART3,
    STM32_UART4
}UART_NO_TAG;


void STM32_UART_Init(void);
void UART_Rx_process(void);
void STM32_UART_Write(u8 uartNo, void *src, u16 len);
 u8 STM32_UART_Read(u8 uartNo, void *dst, u16 len);
void DMA_Uart1_Init( void);
void STM32_UART1_Write(u8* Tx_Buff,u8 Data_Len);
void Upload_ProcessDMAIRQ( void);
//void DMA1_DATA_Trans_Task_ON();
//void DMA1_DATA_Trans_Task_OFF();
u8 DMA1_Uart1_Status_Get( void);

extern unsigned char Task_Uart1_Rx;


#endif























/*********************************************END OF FILE**********************/
