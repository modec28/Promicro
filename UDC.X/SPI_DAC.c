/* 
 * File:   SPI_DAC.c
 * Author: Grant
 * E-mail : grant@tescom.org
 * Created on 2019-7-15 (mon), PM 5:06
 */

#include "DefineScript.h"
#include "SPI_DAC.h"
#include "Delay.h"

#define DAC_DATA_LENGTH 16

const uint8_t DAC_Data[] =
{
	//This_is_data_for_SDIO_pin
	
    //////////config///////////////
	//DAC_SELECT_A=0,_B=1
	0,
    //Don_care
    0,
	//OUTPUT_gain_Selection_1=1x,_0=2x
	0,
    //OUTPUT_Shutdown_control_bit_1_=_Vout_active,_0=_Vout_restrict
    0,
    ///////////////////////////////    
    //DAC_DATA
    0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0	
};

void Transmit_Config_Data_2_DAC()
{
    DAC_CS_L; //Ready to TX
    for(int index=0; index<DAC_DATA_LENGTH; index++)//1.Data 2.CLK
    {
		DAC_SDIO_D(DAC_Data[index]*BIT2); //Write to ADRF
	    DAC_SCLK_S; //CLK Rise
		DAC_SCLK_S; //CLK Fall
    }
    DAC_CS_H;
    
    //LDAC Pin assign to LOW after CS rising edge at least 40ns.
	DAC_LDAC_L; //LDAC PIN is LOW
	DELAY_US(1);
	DAC_LDAC_H; //LDAC PIN is HIGH
}
void Transmit_Config_Data_2_DAC_with_arg(uint16_t DAC_DATA_arg)
{
    int BIT_ARRAY[DAC_DATA_LENGTH] = {0};
    for(int index=0; index<DAC_DATA_LENGTH; index++)
    {
        BIT_ARRAY[index] = DAC_SDIO_D2ARRAY(DAC_DATA_arg<<index);
    }
    
	DAC_CS_L; //Ready to TX
    
	for(int index=0; index<DAC_DATA_LENGTH; index++)//1.Data 2.CLK
	{
		DAC_SDIO_D(BIT_ARRAY[index]*BIT2); //Write to ADRF
		DAC_SCLK_S; //CLK Rise
		DAC_SCLK_S; //CLK Fall
	}
    DAC_SDIO;
	DAC_CS_H;
	
	//LDAC
	DAC_LDAC_L; //LDAC PIN is LOW
	DELAY_US(1);
	DAC_LDAC_H; //LDAC PIN is HIGH
}