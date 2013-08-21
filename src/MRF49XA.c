/*********************************************************************
* FileName:		 MRF49XA.c 
* Dependencies:    See INCLUDES section below
* Processor:       
* Compiler:        
* Company:         Microchip Technology, Inc.
*
* Software License Agreement:
*
* The software supplied herewith by Microchip Technology Incorporated
* (the "Company") for its PICmicro® Microcontroller is intended and
* supplied to you, the Company's customer, for use solely and
* exclusively on Microchip PICmicro Microcontroller products. The
* software is owned by the Company and/or its supplier, and is
* protected under applicable copyright laws. All rights are reserved.
* Any use in violation of the foregoing restrictions may subject the
* user to criminal sanctions under applicable laws, as well as to
* civil liability for the breach of the terms and conditions of this
* license.
*
* THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
* TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
* IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
* CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
*********************************************************************
* File Description:
*
* Change History:
* Author               Cristian Toma
********************************************************************/
#include <xc.h>
#include "IOConfig.h"
#include "MRF49XA.h"
#include "utilidades.h"



volatile TTranseiverStatus TransceiverStatus;


//--------------------------------------------------------------------
// SPI_Read ()
//--------------------------------------------------------------------
unsigned int SPI_Read(void)
{
  char i;
  unsigned int spidata = 0;

  SPI_SDO = 0;
  SPI_SCK = 0;
  for (i=0;i<8;i=i+1) {
    spidata=spidata<<1;

	
		if(SPI_SDI)
		 spidata |= 0x01;
		else
		 spidata &= 0xFE;

    SPI_SCK = 1;
		Nop();
    SPI_SCK = 0;
  }
  return(spidata);
}

//--------------------------------------------------------------------
// SPI_Write ()
//--------------------------------------------------------------------
void SPI_Write(unsigned int spidata) {
	char i;
  
	SPI_SDO = 0;
	SPI_SCK = 0;
	for (i=0;i<8;i=i+1) {
		if(spidata & 0x80)
			SPI_SDO = 1;
		else
			SPI_SDO = 0;
      
		SPI_SCK = 1;			
		Nop();
		SPI_SCK = 0;
		spidata=spidata<<1;
	}
  
	SPI_SDO = 0;
	
}

//--------------------------------------------------------------------
// SPI_Command ()
//--------------------------------------------------------------------
void SPI_Command(unsigned int spicmd) {
	SPI_CS = 0;
	SPI_Write ((spicmd & 0xFF00) >> 8);
	SPI_Write ((spicmd & 0x00FF));
	SPI_CS = 1;
}

//--------------------------------------------------------------------
// SPI_Write16 ()
//--------------------------------------------------------------------
void SPI_Write16(unsigned int spicmd) {
	SPI_Write ((spicmd & 0xFF00) >> 8);
	SPI_Write ((spicmd & 0x00FF));
}

//--------------------------------------------------------------------
// FIFO syncron latch re-enable
//--------------------------------------------------------------------
void MRF49XA_Reset_Radio() {
	SPI_Command(PMCREG);			// turn off tx and rx
	SPI_Command(FIFORSTREG);		// reset FIFO
	SPI_Command(GENCREG);			// disable FIFO , Tx_latch
	SPI_Command(PMCREG | 0x0080);	// turn on receiver
	SPI_Command(GENCREG | 0x0040);	// enable the FIFO	
	SPI_Command(FIFORSTREG | 0x0002);   // FIFO syncron latch re-enable	
}

//--------------------------------------------------------------------
// Power down the radio chip
//--------------------------------------------------------------------
void MRF49XA_Power_Down(void) {
	SPI_Command(0x8201);
}

//--------------------------------------------------------------------
// MRF49XA_Init 
// Initializes the radio chip
//--------------------------------------------------------------------
void MRF49XA_Init(){

    unsigned long i, j = 0;
//	int delay;
	RF_RES = 0;
for(i=0;i<1000;i++)
    for(j=0;j<1000;j++)
        asm volatile("nop");

	Nop();
	RF_RES = 1; // Release the Reset Pin
for(i=0;i<1000;i++)
    for(j=0;j<1000;j++)
        asm volatile("nop");

//----  configuring the RF link --------------------------------

//---- Send init cmd
	SPI_Command( FIFORSTREG );
	SPI_Command( FIFORSTREG | 0x0002);
	SPI_Command( GENCREG);
	SPI_Command( AFCCREG);
	SPI_Command( CFSREG);
	SPI_Command( DRSREG);	
	SPI_Command( PMCREG);
	SPI_Command( RXCREG);
	SPI_Command( TXCREG);	
	SPI_Command(BBFCREG);

//---- antenna tunning
	SPI_Command( PMCREG | 0x0020);		// turn on tx
  DelayMs(5);
//---- end of antenna tunning
	SPI_Command( PMCREG | 0x0080);		// turn off Tx, turn on receiver
	SPI_Command( GENCREG | 0x0040);		// enable the FIFO
	SPI_Command( FIFORSTREG);
	SPI_Command( FIFORSTREG | 0x0002);	// enable syncron latch	
	RF_FSEL=1; // FSEL bit in 1 to enable FIFO in software
}

//--------------------------------------------------------------------
// MRF49XA_Send_Packet
// Sends a data packet
//--------------------------------------------------------------------
void MRF49XA_Send_Packet(TRFData *RFData){

	unsigned char len;
        unsigned char checksum;
	BYTE a;
	
	//---- turn off receiver , enable Tx register
	SPI_Command(PMCREG);				// turn off the transmitter and receiver
	SPI_Command(GENCREG | 0x0080);		// Enable the Tx register
	//---- Packet transmission
	// Reset value of the Tx regs are [AA AA], we can start transmission
	//---- Enable Tx
	SPI_Command(PMCREG |0x0020);		// turn on tx

		SPI_CS=0;						// chip select low
		while(!SPI_SDI){}
			SPI_Write16(TXBREG | 0xAA);	// preamble 
		while(!SPI_SDI){}
			SPI_Write(0xAA);	// preamble 
		while(!SPI_SDI){}
			SPI_Write(0x2D);	// sync pattern 1st byte
		while(!SPI_SDI){}
			SPI_Write(0xD4);	// sync pattern 2nd byte
		len = RFData->index;
		while(!SPI_SDI){}		
			SPI_Write(len + 1);	// Include in the payload the Checksum byte at the end

		for (a=0;a<len;a++){				// send payload
			while(!SPI_SDI){}				// wait for SDO, when buffer data <=8 bits
			SPI_Write(RFData->buffer[a]); // write a byte to tx register
		}

                checksum = CalChkSum(RFData->buffer,len);

		while(!SPI_SDI){}				
			SPI_Write(checksum);	// write a dummy byte since the previous byte is still in buffer

		while(!SPI_SDI){}
			SPI_Write(0x00);	// write a dummy byte since the previous byte is still in buffer
		while(!SPI_SDI){}
			SPI_Write(0x00);	// write a dummy byte since the previous byte is still in buffer
		while(!SPI_SDI){}
			SPI_Write(0x00);	// write a dummy byte since the previous byte is still in buffer
		while(!SPI_SDI){}
			SPI_Write(0x00);	// write a dummy byte since the previous byte is still in buffer
		while(!SPI_SDI){}
			SPI_Write(0x00);	// write a dummy byte since the previous byte is still in buffer
		while(!SPI_SDI){}
			SPI_Write(0x00);	// write a dummy byte since the previous byte is still in buffer 	
		while (!SPI_SDI){}				// wait for the last byte transmission end
		SPI_CS=1;						// chip select high, end transmission
		
	//---- Turn off Tx disable the Tx register
		SPI_Command(FIFORSTREG);   // FIFO Reset
		SPI_Command(PMCREG | 0x0080);	// turn on receiver
		SPI_Command(GENCREG | 0x0040);	// enable the FIFO	
		SPI_Command(FIFORSTREG | 0x0002);   // FIFO syncron latch re-enable

	
}

//--------------------------------------------------------------------
// MRF49XA_Receive_Packet
// Receives a data packet
// This function should be called periodically until it returns
// a valid data packet
// The return values are (see MRF49XA.h) :
// NODATA 			0			no data received
// DATA_RECEIVED 		1			data received, data capture in progress
// PACKET_RECEIVED	2			data received, data packet received ok
//
// This function should be called periodically , at least once every 800us for 9600bps.
// For higher speed, the function should be called more rapidly.
// When a complete packet has been received, the function returns a PACKET_RECEIVED.
// In order to "re-arm" the receiver to receive a new packet call the 
// MRF49XA_Reset_Radio function.
//
// Use a call similar to :
// if ( MRF49XA_Receive_Packet(dataPacket,&length) == PACKET_RECEIVED)
// { 
//   .... do something with the received packet....
// }
// // re-arm for next packet
// MRF49XA_Reset_Radio();
//
//--------------------------------------------------------------------
unsigned int MRF49XA_Receive_Packet( TRFData *RFData){

//	static unsigned char PacketLen =0;
	unsigned char bl;
	
	SPI_SDO = 0;
	SPI_CS	=0;							// chip select low
	Nop();
	if(SPI_SDI) {								// in case of FINT then read out

		SPI_CS=1;	
		RF_FSEL = 0;			// FIFO Select
		if(RFData->len) {	// is this the first byte? go on if not
			Nop();
			AddRFData(RFData,SPI_Read());// read the data byte and stores it in the buffer
			Nop();
			if (RFData->index >= RFData->len) {   // end of packet
				
				RF_FSEL=1;
				MRF49XA_Reset_Radio();
				// whole packet received
				
				RFData->len = RFData->index;				// assing the received length of the packet
				return PACKET_RECEIVED;	
			}
		}
		else {	// the first byte received
			bl=SPI_Read(); // number of bytes in payload is the first byte
                        
			if((bl>0) && (bl<PAYLOAD_MAX)) {   // check if correct number of bytes in payload
				RFData->len=bl;
				RFData->index=0; 
			}
			else {		
				RF_FSEL=1;						// bad packet length
				MRF49XA_Reset_Radio();
				return NODATA;
			}
		}
		
		RF_FSEL=1;
		return DATA_RECEIVED;
	}
	else {
            
		SPI_CS = 1;
		return NODATA;  
	} 
}



/******************************************************************************
 * Function:        void AddRFData(TRFData *RFData, unsigned char data)
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Side Effects:    None
 * Overview:        Adds a byte into the buffer and calculates the CheckSum 
 *
 * Note:            None
 *****************************************************************************/
void AddRFData(TRFData *RFData, unsigned char data){
    
    RFData->buffer[RFData->index] = data;
    RFData->index++;
    RFData->ChkSum = RFData->ChkSum ^ data;
}


/*********************************************************************
 * void StatusRead(void)
 *
 * Overview:        
 *              This function read the status register and output the
 *              status in the global variable TransceiverStatus.
 *
 * PreCondition:    
 *              MRF49XA transceiver has been properly initialized
 *
 * Input:       None   
 *
 * Output:      None    
 *
 * Side Effects:    Global variable TransceiverStatus has been modified
 *
 ********************************************************************/
void StatusRead(void) {
	unsigned char	preRF_FSEL = RF_FSEL;
	unsigned char	preSPI_CS = SPI_CS;
	
	RF_FSEL = 1;
	SPI_CS = 0;
	
	SPI_SDO = 0;
	
	TransceiverStatus.bits.RG_FF_IT = SPI_SDI;    
	SPI_SCK = 1;
	SPI_SCK = 0;
	
	TransceiverStatus.bits.POR = SPI_SDI;
	SPI_SCK = 1;
	SPI_SCK = 0;
	
	TransceiverStatus.bits.RGUR_FFOV = SPI_SDI;
	SPI_SCK = 1;
	SPI_SCK = 0;
	
	TransceiverStatus.bits.WKUP = SPI_SDI;
	SPI_SCK = 1;
	SPI_SCK = 0;
	
	TransceiverStatus.bits.EXT = SPI_SDI;
	SPI_SCK = 1;
	SPI_SCK = 0;
	
	TransceiverStatus.bits.LBD = SPI_SDI;
	SPI_SCK = 1;
	SPI_SCK = 0;
	
	TransceiverStatus.bits.FFEM = SPI_SDI;
	SPI_SCK = 1;
	SPI_SCK = 0;
	
	TransceiverStatus.bits.RSSI_ATS = SPI_SDI;
	SPI_SCK = 1;
	SPI_SCK = 0;
	   
	TransceiverStatus.bits.DQD = SPI_SDI;
	SPI_SCK = 1;
	SPI_SCK = 0;
	
	TransceiverStatus.bits.CRL = SPI_SDI;
	SPI_SCK = 1;
	SPI_SCK = 0;
	
	TransceiverStatus.bits.ATGL = SPI_SDI;
	SPI_SCK = 1;
	SPI_SCK = 0;

	RF_FSEL = preRF_FSEL;
	SPI_CS = preSPI_CS;
	
}


/******************************************************************************
 * Function:        void AddRFData(TRFData *RFData, unsigned char data)
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Side Effects:    None
 * Overview:        Adds a byte into the buffer and calculates the CheckSum 
 *
 * Note:            None
 *****************************************************************************/
void InitRFData(TRFData *RFData){
	RFData->index=0;
	RFData->len = 0;
	RFData->ChkSum=0;
}


/******************************************************************************
 * Function:        unsigned char CalChkSum(unsigned char *buffer, len)
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Side Effects:    None
 * Overview:        Calculates the CheckSum 
 *
 * Note:            None
 *****************************************************************************/
unsigned char CalChkSum(unsigned char *buffer, unsigned char len){
  unsigned char i;
  unsigned char Received = 0;
  
  for (i=0;i<len;i++) {
  	Received = Received ^ buffer[i];
  }
  return Received;

}

