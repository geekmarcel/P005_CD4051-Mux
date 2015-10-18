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
 * Hardware setup:	
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
*  Function:		Setup(int number)
*  Description:		Setup PORTD and the timer, this function need to be called at
*				the beginning of main.
*  Receives:		Nothing
*  Returns:		Nothing
***************************************************************************/
void Setup()
{
	/* Setup Port D */
	/* Pins 0,1,2 as outputs, pin 3 till 5 as input */
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
	InitializeMux(&DDRD,
				  &PIND,
				  &PORTD,
				  PORTD4,
				  &PORTD,
				  &PIND,
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
		/* We can only switch on one LED at a time, so if both buttons are pressed only the first LED will go on */
		if((inputState & 0x01) == 0x01)		
			WriteChannel(TWO, HIGH);
		else if((inputState & 0x02) == 0x02)	
			WriteChannel(THREE, HIGH);
				
		/* Delay a short while */
		_delay_ms(50);
    }
}