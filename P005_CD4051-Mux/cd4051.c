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
#include "common.h"


/************************************************************************/
/* Structures				                                                                  */
/************************************************************************/
struct CD4051
{
	volatile BYTE* inOutOutputReg;
	volatile BYTE* inOutDirReg;
	volatile BYTE* inOutInputReg;
	struct ControlPin inOut;
	struct ControlPin inh;
	struct ControlPin selectA;
	struct ControlPin selectB;
	struct ControlPin selectC;
	
	/* Specifies if the structure is initialized with the register addresses and pin numbers */
	BOOL isInitialized;
} cd4051;

/************************************************************************/
/* Functions				                                                                  */
/************************************************************************/

/***************************************************************************
*  Function:		InitializeMux(volatile BYTE* inOutOutputReg,
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
*					            BYTE selectCPin)
*  Description:		Initializes the CD4051 structure with the given register addresses and port numbers.
*				After that the CD4051 API can be used without specifying addresses or pin numbers.
*
*  Receives:		BYTE* inOutOutputReg	:	Dataregister port address for the inOut pin
*				BYTE* inOutDirReg		:	Data direction register for the inOut pin
*				BYTE* inOutInputReg	:	Input register for the inOutPin
*				BYTE inOutPin,			:	inOut pin number	
*				BYTE* inhPort			:	Inhibit port address			
*				BYTE inhPin,			:	Inhibit pin number	
*				BYTE* selectAPort		:	SelectA port address
*				BYTE selectAPin		:	SelectA pin number		
*				BYTE* selectBPort		:	SelectB port address	
*				BYTE selectBPin		:	SelectB pin number
*				BYTE* selectCPort		:	SelectC port address
*				BYTE selectCPin		:	SelectC pin number

*  Returns:		Nothing
***************************************************************************/
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
	/* Initialize structure */
	cd4051.inOutOutputReg = inOutOutputReg;
	cd4051.inOutDirReg = inOutDirReg;
	cd4051.inOutInputReg = inOutInputReg;
	cd4051.inOut.pin = inOutPin;
	cd4051.inh.port = inhPort;
	cd4051.inh.pin = inhPin;
	cd4051.selectA.port = selectAPort;
	cd4051.selectA.pin = selectAPin;
	cd4051.selectB.port = selectBPort;
	cd4051.selectB.pin = selectBPin;
	cd4051.selectC.port = selectCPort;
	cd4051.selectC.pin = selectCPin;
	
	/* Set initialized to true */
	cd4051.isInitialized = TRUE;
}

/***************************************************************************
*  Function:		WriteChannel(ChannelNo channel, BOOL channelValue)
*  Description:		Writes the given value to the channel, after the call the channel will
*				remain selected and the IC enabled.
*				Note an the usage, the written value will only be available on the channel output
*				as long as the channel remains active.
*				Calling the ReadChannel or this function again with a different channel number
*				will clear the channel output and put it into tristate
*
*  Receives:		ChannelNo channel		:	Channel to select.
*				BOOL channelValue		:	Value to set.
*  Returns:		Nothing
***************************************************************************/
void WriteChannel(ChannelNoType channel, BOOL channelValue)
{
	/* Disable multiplexer */
	CLEAR_BIT(cd4051.inh.port, cd4051.inh.pin);
	
	/* Set channel address */
	SelectChannel(channel);
	
	/* Set InOut direction to output */
	SET_BIT(cd4051.inOutDirReg, cd4051.inOut.pin);
	
	/* Enable multiplexer */
	SET_BIT(cd4051.inh.port, cd4051.inh.pin);
	
	/* Set value to channel */
	if(channelValue == TRUE)
	{
		SET_BIT(cd4051.inOutOutputReg, cd4051.inOut.pin);
	}
	else
	{
		CLEAR_BIT(cd4051.inOutOutputReg, cd4051.inOut.pin);
	}
}

/***************************************************************************
*  Function:		BOOL ReadChannel(ChannelNo channel)
*  Description:		Reads the given channel by first selecting it and then reading it.
*				After the call the channel will remain selected and the IC enabled.
*
*  Receives:		ChannelNo channel		:	Channel to select.
*  Returns:		Current state of the channel, high (TRUE) or low (FALSE).
***************************************************************************/
BOOL ReadChannel(ChannelNoType channel)
{
	/* Disable multiplexer */
	CLEAR_BIT(cd4051.inh.port, cd4051.inh.pin);
	
	/* Set channel address */
	SelectChannel(channel);
	
	/* Set InOut direction to input */
	CLEAR_BIT(cd4051.inOutDirReg, cd4051.inOut.pin);
	
	/* Enable multiplexer */
	SET_BIT(cd4051.inh.port, cd4051.inh.pin);
	
	/* Read Channel */
	/* Shift the read value to the first bit position, this depends on which pin the inOut signal is connected */
	/* And it with 0x01, to get only the first bit and ignore the others */
	BOOL inputVal = (*cd4051.inOutInputReg >> cd4051.inOut.pin) & 0x01;	
	
	return inputVal;
}

/***************************************************************************
*  Function:		SelectChannel(ChannelNo channel)
*  Description:		This function will select the channel by setting the Select A, B and C
*				signals to 0 or 1.
*
*  Receives:		ChannelNo channel		:	Channel to select
*  Returns:		Nothing
***************************************************************************/
void SelectChannel(ChannelNoType channel)
{
	if(cd4051.isInitialized == TRUE)
	{
		/* Set Select signal A */
		if((channel & 0x01) == 0x01)
		{
			SET_BIT(cd4051.selectA.port, cd4051.selectA.pin);
		}
		else
		{
			CLEAR_BIT(cd4051.selectA.port, cd4051.selectA.pin);
		}
		
		/* Set Select signal B */
		if((channel & 0x02) == 0x02)
		{
			SET_BIT(cd4051.selectB.port, cd4051.selectB.pin);
		}
		else
		{
			CLEAR_BIT(cd4051.selectB.port, cd4051.selectB.pin);
		}
		
		/* Set Select signal C */
		if((channel & 0x04) == 0x04)
		{
			SET_BIT(cd4051.selectC.port, cd4051.selectC.pin);
		}
		else
		{
			CLEAR_BIT(cd4051.selectC.port, cd4051.selectC.pin);
		}
	}
}