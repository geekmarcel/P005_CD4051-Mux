/*--------------------------------------------------------------------------------------------------------------------------------------------------------
 * Project: 		Post 5 CD4051
 * Hardware:		Arduino UNO
 * Micro:			ATMEGA328P
 * IDE:			Atmel Studio 6.2
 *
 * Name:    		main.c
 * Purpose: 		LCD16x2 Example
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
	DDRD = 0b00000111;
}


/***************************************************************************
*  Function:		Main(void)
*  Description:		Main function of the program.
*  Receives:		Nothing
*  Returns:		Optionally the exit code.
***************************************************************************/
int main(void)
{
    while(1)
    {
        
    }
}