/* 
 * File:   _USART_Com.h
 * Author: Grant
 * E-mail : grant@tescom.org
 *
 * Created on 2019년 7월 18일 (목), 오후 4:01
 */

#ifndef _USART_COM_H
#define	_USART_COM_H

#include <stdio.h>

#define SPI_DATA_LENGTH 4

void USART_INIT();
void Transmit_To_PC_CHAR(unsigned char data);
uint16_t Receive_From_PC();
void Receive_From_PC_STR(unsigned char *str);
unsigned char Rx_Flag;
unsigned int PC_Transmit_2_USART_INT();
uint16_t __Hex(unsigned char *data);
void __Hex_Conv(unsigned char *Hex, unsigned char *Target);
uint16_t Receive_From_PC_BIT(uint8_t *data);
#endif	/* _USART_COM_H */

