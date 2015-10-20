/*--------------------------------------------------------------------------------------------------------------------------------------------------------
 * Project: 		Post 5 CD4051
 * Hardware:		Arduino UNO
 * Micro:			ATMEGA328P
 * IDE:			Atmel Studio 6.2
 *
 * Name:    		main.c
 * Purpose: 		CD4051 Example
 * Date:			09-10-2015
 * Author:		Marcel van der Ven
 *
 * Hardware setup:		PORTD0		:	Select A signal, pin 11 of CD4051
 *					PORTD1		:	Select B signal, pin 10 of CD4051
 *					PORTD2		:	Select C signal, pin 9 of CD4051
 *					PORTD3		:	Inhibit signal, pin 6 of CD4051
 *					PORTD4		:	In/Out signal, pin 3 of CD4051	
 *
 * Note(s):
 *--------------------------------------------------------------------------------------------------------------------------------------------------------*/

/************************************************************************/
/* Defines				                                                                  */
/************************************************************************/
#define F_CPU	16000000UL

/************************************************************************/
/* Includes				                                                                  */
/************************************************************************/
#include <avr/io.h>
#include "util/delay.h"
#include "common.h"
#include "cd4051.h"

/***************************************************************************
*  Function:		Setup()
*  Description:		Setup PORTD, this function need to be called at
*				the beginning of main.
*  Receives:		Nothing
*  Returns:		Nothing
***************************************************************************/
void Setup()
{
	/* Setup Port D */
	/* Pins 0,1,2 and 3 as outputs, pin 4 till 5 as input */
	DDRD = 0b00001111;
}

/***************************************************************************
*  Function:		Main(void)
*  Description:		Main function of the program.
*  Receives:		Nothing
*  Returns:		Optionally the exit code.
***************************************************************************/
int main(void)
{
	/* Setup and initialization */
	Setup();
	InitializeCD4051(&DDRD,
				     &PIND,
				     &PORTD,
				     PORTD4,
				     PORTD3,
				     PORTD0,
				     PORTD1,
				     PORTD2);
	
    while(1)
    {
		BYTE inputState = 0x00;
		
        /* Read input channels, this are channel 0 and 1*/
		for(int i = 0; i < 2; i++)
		{
			/* Read the channel and store the current state on the bit position in the inputState variable */
			inputState |= (ReadChannel(i) << i);
		}
		
		/* Using the inputState variable determine which LED should go on */
		/* We can only switch on 1 LED at a time, if both buttons are pressed only the first LED will go on */
		if((inputState & 0x01) == 0x01)		
			WriteChannel(TWO, HIGH);
		else if((inputState & 0x02) == 0x02)	
			WriteChannel(THREE, HIGH);
				
		/* Delay a short while */
		_delay_ms(50);
    }
}