/* 
 * File:   SPI_ADRF.c
 * Author: Grant
 * E-mail : grant@tescom.org
 *
 * Created on 2019년 7월 9일 (화), 오후 2:20
 */

#include "DefineScript.h"
#include "SPI_ADRF.h"
#include "Delay.h"

#define ADRF_RST_Dir (DDRD |= BIT7)
#define ADRF_SCLK_Dir (DDRE |= BIT6)
#define ADRF_SDIO_Dir_IN (DDRB &= ~BIT4)
#define ADRF_SDIO_Dir_OUT (DDRB |= BIT4)
#define ADRF_CS_Dir (DDRB |= BIT5)

#define ADRF_RST_H (PORTD |= BIT7)
#define ADRF_RST_L (PORTD &= ~BIT7)
#define ADRF_SCLK (PORTE &= ~BIT6)
#define ADRF_SCLK_S (PORTE ^= BIT6)
#define ADRF_SDIO (PORTB &= ~BIT4)
#define ADRF_CS_H (PORTB |= BIT5)
#define ADRF_CS_L (PORTB &= ~BIT5)

#define ADRF_PIN BIT4
#define ADRF_SDIO_D(x) ((PORTB&ADRF_PIN)!=ADRF_PIN)?(PORTB ^= x):(x==0x00)?(PORTB^=ADRF_PIN):(PORTB |= x);

#define ADRF_DATA_LENGTH 24

void ADRF_DAC_INIT()
{
    ///////////ADRF////////////////
    
    //OUTPUT
    ADRF_CS_Dir; //CS PIN is OUTPUT 
    ADRF_RST_Dir; //RST PIN is OUTPUT 
    ADRF_SCLK_Dir; //SCLK PIN is OUTPUT 
    ADRF_SDIO_Dir_OUT; //SDIO PIN is OUTPUT 
    
    //Idle
    ADRF_CS_H; //CS PIN is HIGH
    ADRF_SCLK; //SCLK PIN is LOW at first
    ADRF_SDIO; //SDIO PIN is LOW
	
    ///////////////DAC////////////////
	//OUTPUT
    DAC_CS_Dir; //CS PIN is OUTPUT 
    DAC_LDAC_Dir; //RST PIN is OUTPUT 
    DAC_SCLK_Dir; //SCLK PIN is OUTPUT 
    DAC_SDIO_Dir_OUT; //SDIO PIN is OUTPUT 
    
    //Idle
    DAC_CS_H; //CS PIN is HIGH
    DAC_SCLK; //SCLK PIN is LOW at first
    DAC_SDIO; //SDIO PIN is LOW
	DAC_LDAC_H; //LDAC PIN is HIGH    
}

const uint8_t ADRF_Data[] =
{
	//This is data for SDIO pin
	
	//Read=1, Write=0
	0,
	//Address
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
	//Data
	1, 0, 0, 0, 0, 0, 1, 0 //144Mhz, DCoffset_Disable	
};

void Transmit_Config_Data_2_IQ_Baseband_Filter()
{
    //Reset
    ADRF_RST_H; //RST PIN is HIGH
	DELAY_US(1);
	ADRF_RST_L; //RST PIN is LOW
	DELAY_US(1);
	ADRF_RST_H; //RST PIN is HIGH
    ADRF_CS_L; //Ready to TX
    for(int index=0; index<ADRF_DATA_LENGTH; index++)//1.Data 2.CLK
    {
		ADRF_SDIO_D(ADRF_Data[index]*BIT4); //Write to ADRF
        
        ////_ Delay for Data setup time>(Clock Period/4) _///
        asm volatile("PUSH R0");
		asm volatile("POP R0");
        asm volatile("nop");
        ///////////////////////////////
        
	    ADRF_SCLK_S; //CLK Rise
		ADRF_SCLK_S; //CLK Fall
    }
    ADRF_CS_H;
}