#ifndef SOFT_I2C_H
#define SOFT_I2C_H

#include "stddefs.h"
#define I2C_HIGH 1
#define I2C_LOW 0
//#define I2C_PK2_DEBUG
#define I2C_PK2_MIRROR

#ifdef I2C_PK2_MIRROR
#define I2C_MIRROR() do { I2C_MIRROR_SCL = (I2C_SCL != 0)?1:0; \
I2C_MIRROR_SDA = (I2C_SDA_READ != 0)?1:0; } while(0);

#define I2C_MIRROR_SCL LATAbits.LATA0
#define I2C_MIRROR_SDA LATAbits.LATA1

#define TRIS_I2C_MIRROR_SCL TRISAbits.TRISA1           // RA1 = SCL
#define TRIS_I2C_MIRROR_SDA TRISAbits.TRISA0           // RA0 = SDA
#else
#define I2C_MIRROR() // Nothing

#endif

#ifdef I2C_PK2_DEBUG
#define TRIS_I2C_SCL TRISAbits.TRISA1           // RA1 = SCL
#define TRIS_I2C_SDA TRISAbits.TRISA0           // RA0 = SDA

#define I2C_SCL LATAbits.LATA1
#define I2C_SDA LATAbits.LATA0
#define I2C_SDA_READ PORTAbits.RA0

#define WP_I2C_SCL  WPUAbits.WPUA1
#define WP_I2C_SDA  WPUAbits.WPUA0

#else
#define TRIS_I2C_SCL TRISBbits.TRISB6
#define TRIS_I2C_SDA TRISBbits.TRISB4

#define I2C_SCL LATBbits.LATB6
#define I2C_SDA LATBbits.LATB4
#define I2C_SDA_READ PORTBbits.RB4

#define WP_I2C_SCL  WPUBbits.WPUB6
#define WP_I2C_SDA  WPUBbits.WPUB4
#endif
void SoftI2cInit(void);
void SoftI2cRepeatedStart(void);
void SoftI2cNop(void);


void SoftI2cStart(void);
UI08_t SoftI2cRxByte(UI08_t ack);
UI08_t SoftI2cTxByte(UI08_t data);
void SoftI2cStop(void);

#endif