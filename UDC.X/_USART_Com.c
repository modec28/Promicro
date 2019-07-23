/* 
 * File:   _USART_Com.c
 * Author: Grant
 * E-mail : grant@tescom.org
 * Created on 2019-7-15 (mon), PM 5:06
 */
#include "_USART_Com.h"
#include "DefineScript.h"

void USART_INIT(unsigned int baud)
{
	UBRR1H = (unsigned char)(baud>>8);
    UBRR1L = (unsigned char)baud;
	UCSR1B = (1<<RXEN1) | (1<<TXEN1); // TX, RX ENB
	//8bit, 1stopbit
}
void Transmit_To_PC_CHAR(unsigned char data)
{
	while(!(UCSR1A&(1<<UDRE1)));
	
	UDR1 = data;
}
uint16_t Receive_From_PC()
{
    while(!(UCSR1A&(1<<RXC1)));
    
    return UDR1;
}
uint16_t Receive_From_PC_And_CONCATE(uint16_t High_BIT, uint16_t Low_BIT)
{
    High_BIT = Receive_From_PC();
    Low_BIT = Receive_From_PC();
    return (High_BIT<<8)+Low_BIT;
}