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
/* Enumerations			                                                                  */
/************************************************************************/
enum ChannelNo{ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN};
enum ChannelType{INPUT, OUTPUT};
	
/************************************************************************/
/* Structures				                                                                  */
/************************************************************************/		


/************************************************************************/
/* Function prototypes		                                                                  */
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
				BYTE selectCPin);
void WriteChannel(ChannelNo channel, BOOL channelValue);
BOOL ReadChannel(ChannelNo channel);
void SelectChannel(ChannelNo channel);

#endif /* CD4051_H_ */