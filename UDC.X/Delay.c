/* 
 * File:   Delay.c
 * Author: Grant
 * E-mail : grant@tescom.org
 *
 * Created on 2019-07-15
 */
#include "Delay.h"

void DELAY_US(unsigned int Delta_Time)
{
	register unsigned int i;
	for(i=0; i<Delta_Time; i++)
	{
		/*
		asm volatile("PUSH R0");
		asm volatile("POP R0");
		*/
		asm volatile("nop");
	}
}