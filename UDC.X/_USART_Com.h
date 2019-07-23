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
uint16_t Receive_From_PC_And_CONCATE(uint16_t High_BIT, uint16_t Low_BIT);

#endif	/* _USART_COM_H */

