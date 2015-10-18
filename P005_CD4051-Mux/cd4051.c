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
#include "util/delay.h"


/************************************************************************/
/* Structures				                                                                  */
/************************************************************************/
struct CD4051
{
	struct PinSettings inOut;
	struct PinSettings inh;
	struct PinSettings selectA;
	struct PinSettings selectB;
	struct PinSettings selectC;
	
	/* Specifies if the structure is initialized with the register addresses and pin numbers */
	BOOL isInitialized;
} cd4051;

/************************************************************************/
/* Functions				                                                                  */
/************************************************************************/

/***************************************************************************
*  Function:		InitializeCD4051(volatile BYTE* controlDirPort,
							   volatile BYTE* controlInputPort,
						          volatile BYTE* controlOutputPort,
					                 BYTE inOutPin,
					                 BYTE inhPin,
					                 BYTE selectAPin,
					                 BYTE selectBPin,
*					                 BYTE selectCPin)
*  Description:		Initializes the CD4051 structure with the given register addresses and port numbers.
*				After that the CD4051 API can be used without specifying addresses or pin numbers.
*
*  Receives:		BYTE* controlDirPort	:	Data direction port address
*				BYTE* controlInputPort	:	Input port address
*				BYTE* controlOutputPort:	Output port address
*				BYTE inOutPin,			:	inOut pin number	
*				BYTE inhPin,			:	Inhibit pin number	
*				BYTE selectAPin		:	SelectA pin number		
*				BYTE selectBPin		:	SelectB pin number
*				BYTE selectCPin		:	SelectC pin number

*  Returns:		Nothing
***************************************************************************/
void InitializeCD4051(volatile BYTE* controlDirPort,
				      volatile BYTE* controlInputPort,
				      volatile BYTE* controlOutputPort,
				      BYTE inOutPin,
				      BYTE inhPin,
				      BYTE selectAPin,
				      BYTE selectBPin,
				      BYTE selectCPin)
{
	/* Initialize structure */
	cd4051.inOut.dirPort = controlDirPort;
	cd4051.inOut.outputPort = controlOutputPort;
	cd4051.inOut.inputPort = controlInputPort;
	cd4051.inOut.pin = inOutPin;
	
	cd4051.inh.outputPort = controlOutputPort;
	cd4051.inh.inputPort = controlInputPort;
	cd4051.inh.pin = inhPin;
	
	cd4051.selectA.outputPort = controlOutputPort;
	cd4051.selectA.inputPort = controlInputPort;
	cd4051.selectA.pin = selectAPin;
	
	cd4051.selectB.outputPort = controlOutputPort;
	cd4051.selectB.inputPort = controlInputPort;
	cd4051.selectB.pin = selectBPin;
	
	cd4051.selectC.outputPort = controlOutputPort;
	cd4051.selectC.inputPort = controlInputPort;
	cd4051.selectC.pin = selectCPin;
	
	/* Set initialized to true */
	cd4051.isInitialized = TRUE;
}

/***************************************************************************
*  Function:		WriteChannel(ChannelNoType channel, BOOL channelValue)
*  Description:		Writes the given value to the channel, after the call the channel will
*				remain selected and the IC enabled.
*				Note an the usage, the written value will only be available on the channel output
*				as long as the channel remains active.
*				Calling the ReadChannel or this function again with a different channel number
*				will clear the channel output and put it into tristate
*
*  Receives:		ChannelNoType channel	:	Channel to select.
*				BOOL channelValue		:	Value to set.
*  Returns:		Nothing
***************************************************************************/
void WriteChannel(ChannelNoType channel, BOOL channelValue)
{
	if(cd4051.isInitialized == TRUE)
	{
		/* Disable multiplexer, inhibit is low active*/
		SET_BIT(cd4051.inh.outputPort, cd4051.inh.inputPort, cd4051.inh.pin);
	
		/* Set channel address */
		SelectChannel(channel);
	
		/* Set InOut direction to output */
		SET_BIT(cd4051.inOut.dirPort, cd4051.inOut.dirPort, cd4051.inOut.pin);
	
		/* Enable multiplexer, inhibit is low active */
		CLEAR_BIT(cd4051.inh.outputPort, cd4051.inh.inputPort, cd4051.inh.pin);
	
		/* Delay a short while so the port can switch and the chip can be enabled (Propagation Delay Inhibit)*/
		_delay_us(2);
		
		/* Set value to channel */
		if(channelValue == TRUE)
		{
			SET_BIT(cd4051.inOut.outputPort, cd4051.inOut.inputPort, cd4051.inOut.pin);
		}
		else
		{
			CLEAR_BIT(cd4051.inOut.outputPort, cd4051.inOut.inputPort, cd4051.inOut.pin);
		}
	}
}

/***************************************************************************
*  Function:		BOOL ReadChannel(ChannelNoType channel)
*  Description:		Reads the given channel by first selecting it and then reading it.
*				After the call the channel will remain selected and the IC enabled.
*
*  Receives:		ChannelNoType channel	:	Channel to select.
*  Returns:		Current state of the channel, high (TRUE) or low (FALSE).
***************************************************************************/
BOOL ReadChannel(ChannelNoType channel)
{
	BOOL inputVal = 0;
	
	if(cd4051.isInitialized == TRUE)
	{
		/* Disable multiplexer, inhibit is low active */
		SET_BIT(cd4051.inh.outputPort, cd4051.inh.inputPort, cd4051.inh.pin);
	
		/* Set channel address */
		SelectChannel(channel);
	
		/* Set InOut direction to input */
		CLEAR_BIT(cd4051.inOut.dirPort, cd4051.inOut.dirPort, cd4051.inOut.pin);
	
		/* Enable multiplexer, inhibit is low active */
		CLEAR_BIT(cd4051.inh.outputPort, cd4051.inh.inputPort, cd4051.inh.pin);
	
		/* Delay a short while so the port can switch and the chip can be enabled (Propagation Delay Inhibit)*/
		_delay_us(2);
	
		/* Read Channel */
		/* Shift the read value to the first bit position */
		/* And the value with 0x01, to get only the first bit and ignore the others */
		inputVal = (*cd4051.inOut.inputPort >> cd4051.inOut.pin) & 0x01;	
	}
	return inputVal;
}

/***************************************************************************
*  Function:		SelectChannel(ChannelNoType channel)
*  Description:		This function will select the channel by setting the Select A, B and C
*				signals to 0 or 1.
*
*  Receives:		ChannelNoType channel	:	Channel to select
*  Returns:		Nothing
***************************************************************************/
void SelectChannel(ChannelNoType channel)
{
	if(cd4051.isInitialized == TRUE)
	{
		/* Set Select signal A */
		if((channel & 0x01) == 0x01)
		{
			SET_BIT(cd4051.selectA.outputPort, cd4051.selectA.inputPort, cd4051.selectA.pin);
		}
		else
		{
			CLEAR_BIT(cd4051.selectA.outputPort, cd4051.selectA.inputPort, cd4051.selectA.pin);
		}
		
		/* Set Select signal B */
		if((channel & 0x02) == 0x02)
		{
			SET_BIT(cd4051.selectB.outputPort, cd4051.selectB.inputPort, cd4051.selectB.pin);
		}
		else
		{
			CLEAR_BIT(cd4051.selectB.outputPort, cd4051.selectB.inputPort, cd4051.selectB.pin);
		}
		
		/* Set Select signal C */
		if((channel & 0x04) == 0x04)
		{
			SET_BIT(cd4051.selectC.outputPort, cd4051.selectC.inputPort, cd4051.selectC.pin);
		}
		else
		{
			CLEAR_BIT(cd4051.selectC.outputPort, cd4051.selectC.inputPort, cd4051.selectC.pin);
		}
	}
}