
/*********************************************************************
 *
 *             Librería de funciones generales
 *
 *
 *********************************************************************
 * FileName:        utilidades.c
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC16Fxxx
 * Compiler:        MPLAB C 
 * Company:         EPJ S.A.
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Ernesto Pareja J     18 ene 2010  Crecación
 ********************************************************************/


/******************************************************************************
 * Function:        void DelayMs(char);
 * PreCondition:    None
 * Input:           the number of miliseconds to delay.
 * Output:          None
 * Side Effects:    None
 * Overview:        
 * Note:            None
 *                 
 *****************************************************************************/
 void DelayMs(unsigned int timeMs) {
  unsigned int i;
  timeMs=500*timeMs;
	for (i=0; i<timeMs; i++){
	
	}
}
