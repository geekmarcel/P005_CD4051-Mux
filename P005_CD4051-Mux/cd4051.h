/*--------------------------------------------------------------------------------------------------------------------------------------------------------
 * Project: 		CD4051 library
 * Hardware:		Arduino UNO
 * Micro:			ATMEGA328P
 * IDE:			Atmel Studio 6.2
 *
 * Name:    		cd4051.h
 * Purpose: 		CD4051 CMOS IC Header file for library
 * Date:			09-10-2015
 * Author:		Marcel van der Ven
 *
 * Hardware setup:	
 *
 * Note(s):
 *--------------------------------------------------------------------------------------------------------------------------------------------------------*/


#ifndef CD4051_H_
#define CD4051_H_

/************************************************************************/
/* Includes				                                                                  */
/************************************************************************/
#include "common.h"


/************************************************************************/
/* Enumerations			                                                                  */
/************************************************************************/
typedef enum {ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN}	ChannelNoType;
typedef enum {INPUT, OUTPUT}							ChannelType;
	
/************************************************************************/
/* Structures				                                                                  */
/************************************************************************/		


/************************************************************************/
/* Function prototypes		                                                                  */
/************************************************************************/
void InitializeMux(volatile BYTE* inOutDirReg,
				   volatile BYTE* inOutInputReg,
				   volatile BYTE* inOutPort,
				   BYTE inOutPin,
				   volatile BYTE* controlOutputPort,
				   volatile BYTE* controlInputPort,
				   BYTE inhPin,
				   BYTE selectAPin,
				   BYTE selectBPin,
				   BYTE selectCPin);
void WriteChannel(ChannelNoType channel, BOOL channelValue);
BOOL ReadChannel(ChannelNoType channel);
void SelectChannel(ChannelNoType channel);

#endif /* CD4051_H_ */