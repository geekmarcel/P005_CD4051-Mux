/*--------------------------------------------------------------------------------------------------------------------------------------------------------
 * Project: 		Common library
 * Hardware:		Arduino UNO
 * Micro:			ATMEGA328P
 * IDE:			Atmel Studio 6.2
 *
 * Name:    		common.h
 * Purpose: 		Common functions and definition library.
 * Date:			01-10-2015
 * Author:		Marcel van der Ven
 *
 * Hardware setup:	
 *
 * Releases:		Oct 9 2015 - 1.1:	Added High - Low defines
 *				
 *				Oct. 1 2015 - 1.0 Initial release
 * Note(s):
 *--------------------------------------------------------------------------------------------------------------------------------------------------------*/


#ifndef COMMON_H_
#define COMMON_H_

#include <stdint.h>

/************************************************************************/
/* Defines				                                                                  */
/************************************************************************/
typedef uint8_t		BYTE;
typedef	uint8_t		BOOL;

#define TRUE		1
#define FALSE		0
#define HIGH		1
#define LOW			0

/************************************************************************/
/* Structures				                                                                  */
/************************************************************************/
struct ControlPin
{
	volatile BYTE* port;
	volatile BYTE pin;
};


/************************************************************************/
/* Macros				                                                                  */
/************************************************************************/
#define SET_BIT(y, mask)        ( *y |=  (mask) )
#define CLEAR_BIT(y, mask)      ( *y &= ~(mask) )
#define FLIP_BIT(y, mask)       ( *y ^=  (mask) )


/************************************************************************/
/* Functions				                                                                  */
/************************************************************************/


#endif /* COMMON_H_ */