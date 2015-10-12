/*--------------------------------------------------------------------------------------------------------------------------------------------------------
 * Project: 		CD4051 Library
 * Hardware:		Arduino UNO
 * Micro:			ATMEGA328P
 * IDE:			Atmel Studio 6.2
 *
 * Name:			cd4051.c
 * Purpose: 		CMOS CD4051 Library functions
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
#include "cd4051.h"

/************************************************************************/
/* Structures				                                                                  */
/************************************************************************/
struct CD4051
{
	struct ControlPin inOut;
	struct ControlPin inh;
	struct ControlPin selectA;
	struct ControlPin selectB;
	struct ControlPin selectC;
	
	BOOL isInitialized;
	BOOL setupCompleted;
} cd4051;
/************************************************************************/
/* Functions				                                                                  */
/************************************************************************/

void Initialize(volatile BYTE* inOutOutputReg,
				volatile BYTE* inOutDirReg,
				volatile BYTE* inOutInputReg,
				BYTE inOutPin,
				volatile BYTE* inhPort,
				BYTE inhPin,
				volatile BYTE* selectAPort,
				BYTE selectAPin,
				volatile BYTE* selectBPort,
				BYTE selectBPin,
				volatile BYTE* selectCPort,
				BYTE selectCPin)
{
	cd4051.inOut.pin = inOutPin;
	//cd4051.inOut
	
	
	/* Set initialized to true */
	cd4051.isInitialized = true;
}

void SetupChannels()
{
	Channels c
}
/***************************************************************************
*  Function:		ScanChannels(void)
*  Description:		
*  Receives:		Nothing
*  Returns:		Nothing
***************************************************************************/
void ScanChannels(void)
{
	
}