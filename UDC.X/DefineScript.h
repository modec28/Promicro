/* 
 * File:   DefineScript.h
 * Author: Grant
 * E-mail : grant@tescom.org
 *
 * Created on 2019년 7월 9일 (화), 오후 1:50
 */

#ifndef DEFINESCRIPT_H
#define	DEFINESCRIPT_H

#include <stdio.h>
#include "../../../../../../../../Program Files (x86)/Atmel/Studio/7.0/toolchain/avr8/avr8-gnu-toolchain/avr/include/avr/io.h"
#include "../../../../../../../../Program Files (x86)/Atmel/Studio/7.0/toolchain/avr8/avr8-gnu-toolchain/avr/include/avr/interrupt.h"


//////////**BIT define**////////////
#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80
////////////////////////////////////

//////////DAC_SPI_PIN////////////////
#define DAC_LDAC_Dir (DDRB |= BIT6)
#define DAC_SCLK_Dir (DDRB |= BIT3)
#define DAC_SDIO_Dir_IN (DDRB &= ~BIT2)
#define DAC_SDIO_Dir_OUT (DDRB |= BIT2)
#define DAC_CS_Dir (DDRB |= BIT1)

#define DAC_LDAC_H (PORTB |= BIT6)
#define DAC_LDAC_L (PORTB &= ~BIT6)
#define DAC_SCLK (PORTB &= ~BIT3)
#define DAC_SCLK_S (PORTB ^= BIT3)
#define DAC_SDIO (PORTB &= ~BIT2)
#define DAC_CS_H (PORTB |= BIT1)
#define DAC_CS_L (PORTB &= ~BIT1)

#define SDIO_PIN BIT2
#define DAC_SDIO_D(x) ((PORTB&SDIO_PIN)!=SDIO_PIN)?(PORTB ^= x):(x==0x00)?(PORTB^=SDIO_PIN):(PORTB |= x);
#define DAC_SDIO_D2BIT(x) ((x&0x8000)==0x8000)?(PORTB|=BIT2):(PORTB&=~BIT2);
#define DAC_SDIO_D2ARRAY(x) ((x&0x8000)==0x8000)?1:0;
/////////////////////////////////////



#endif	/* DEFINESCRIPT_H */

