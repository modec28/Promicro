/* 
 * File:   _USART_Com.c
 * Author: Grant
 * E-mail : grant@tescom.org
 * Created on 2019-7-15 (mon), PM 5:06
 */
#include "_USART_Com.h"
#include "DefineScript.h"

unsigned char HEX_H[] = { 0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xa0, 0xb0, 0xc0, 0xd0, 0xe0, 0xf0};
unsigned char HEX_L[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
 
#define HEX_CONCAT_H(a,b) (HEX_H[(a)] + HEX_L[(b)])
#define HEX_CONCAT_L(a,b) (HEX_H[(a)] + HEX_L[(b)])

uint16_t __Hex(unsigned char *data)
{
    return (HEX_CONCAT_H(data[0],data[1])<<8)+HEX_CONCAT_L(data[2],data[3]);
}
inline void __Hex_Conv(unsigned char *Hex, unsigned char *Target)
{
    for(int i=0; i<SPI_DATA_LENGTH; i++)
    {
        //PC에서 오는 char자료형의 16진수 데이터는 0~9와 A~F로 이루어져있다.
        //PC에서 MCU로 전달되었을때 0~9와 A~F는 각각 48~57, 65~70의 값을 갖는다.
        //0~9의 경우 '0'(48)을 빼줌으로써 16진수 0~9로 만들어 줄수있다.
        //마찬가지로 A~F의 경우 '7'(55)를 빼줌으로써 16진수 10~15로 만들 수 있다.
        Hex[i] = Target[i] - ((Target[i]<'A')?'0':'7');
        
    }
}
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
    Rx_Flag = 1;
    return UDR1;
}
void Receive_From_PC_STR(unsigned char *str)
{
    int i=0;
    while((str[i++]=Receive_From_PC())!= '\n');
    
    str[i]='\0';
}
uint16_t Receive_From_PC_BIT(uint8_t *data)
{
    uint16_t Concat_Data;
    //unsigned char data_H, data_L;
    //data_H = (data&0xFF00)>>8;
    //data_L = (data&0x00FF);
    for(int i=0; i<2; i++)
    {
        data[i]=Receive_From_PC();
    }
    Concat_Data = data[0]+(data[1]<<8);
    //sprintf(&c, "%c", data);
    return Concat_Data;
}