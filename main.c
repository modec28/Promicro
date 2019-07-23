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
    uint16_t Rx_BIT_H=0;
    uint16_t Rx_BIT_L=0;
    uint16_t Rx_BIT_C=0;
	_init();
    
    while(1)
    {
        Rx_BIT_C = Receive_From_PC_And_CONCATE(Rx_BIT_H, Rx_BIT_L);
        Transmit_Config_Data_2_IQ_Baseband_Filter();
        Transmit_Config_Data_2_DAC_with_arg(Rx_BIT_C);
    }
}

