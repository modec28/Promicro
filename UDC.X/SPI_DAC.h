/* 
 * File:   SPI_DAC.h
 * Author: Grant
 * E-mail : grant@tescom.org
 *
 * Created on 2019년 7월 15일 (월), 오후 6:07
 */

#ifndef SPI_DAC_H
#define	SPI_DAC_H

#include <stdio.h>

void Transmit_Config_Data_2_DAC();
void Transmit_Config_Data_2_DAC_with_arg(uint16_t DAC_DATA_arg);

#endif	/* SPI_DAC_H */

