/*
 * UDC.c
 *
 * Created: 2019-07-05 오후 3:52:00
 * Author : Grant
 * E-mail : grant@tescom.org
 */ 

#include "UDC.X/SPI_ADRF.h"
#include "UDC.X/SPI_DAC.h"
#include "UDC.X/_USART_Com.h"
#include "UDC.X/Delay.h"


void _init()
{
    //initialize
    ADRF_DAC_INIT();
	USART_INIT(51);
}
int main(void)
{
    unsigned char Rx_Buffer[SPI_DATA_LENGTH];
    unsigned char Rx_Hex[SPI_DATA_LENGTH];
    uint16_t Rx_BIT_H, Rx_BIT_L, Rx_BIT_C;
    //uint16_t Rx_CONCATBIT;
	_init();
    
    //Transmit_Config_Data_2_IQ_Baseband_Filter();
    //Transmit_Config_Data_2_DAC();
    //Transmit_Config_Data_2_DAC_with_arg(0xCDCC);
    
    //Receive_From_PC_STR(Rx_Buffer); //Input_16Bit_HEX_Serial_Data
    //__Hex_Conv(Rx_Hex, Rx_Buffer);
    
    //Transmit_Config_Data_2_IQ_Baseband_Filter();
    //Transmit_Config_Data_2_DAC_with_arg(__Hex(Rx_Hex));
    
    Rx_BIT_H = Receive_From_PC();
    Rx_BIT_L = Receive_From_PC();
    Rx_BIT_C = (Rx_BIT_H<<8)+Rx_BIT_L;
    Transmit_Config_Data_2_IQ_Baseband_Filter();
    Transmit_Config_Data_2_DAC_with_arg(Rx_BIT_C);
    
    while(1)
    {
        //if(!strcmp(Rx_Buffer,"asdfg\n"))
        //{
        //    Transmit_To_PC_CHAR('1');
        //}
    }
}

