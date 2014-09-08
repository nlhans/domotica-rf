#include "bsp/softI2c.h"

void SoftI2cNop()
{
    uint8_t i;
    // 10=24.5kHz
    // 50=7kHz
    // 500 = 700Hz or so
    // 8 = 43kHz RX clock (which is marginal)
    // Risetime of 100k pullups on this board with all devices fitted is 8us.
    // The negative width of each pulse is about 8us now.
    // @ 16MHz PIC
    __delay_us(8);
}

void SoftI2cInit(void)
{
    // Write '0' (=HIGH)
    I2C_SCL = I2C_HIGH;
    I2C_SDA = I2C_HIGH;
    
    // Configure as inputs
    TRIS_I2C_SCL = OUTPUT_PIN;
    TRIS_I2C_SDA = OUTPUT_PIN;

    // Enable weak pullups
    // Should be disabled during sleep
#ifdef WP_I2C_SDA
    WP_I2C_SDA = 0; // SDA
    WP_I2C_SCL = 0; // SCL
#endif
    
    SoftI2cStart();
    SoftI2cTxByte(0x00);
    SoftI2cStop();
    
}

void SoftI2cStart(void)
{
    TRIS_I2C_SDA = OUTPUT_PIN;

    I2C_SCL = I2C_HIGH;
    SoftI2cNop();

    I2C_SDA = I2C_LOW;
    SoftI2cNop();
    I2C_SCL = I2C_LOW;
    SoftI2cNop();

}

void SoftI2cRepeatedStart(void)
{
    TRIS_I2C_SDA = OUTPUT_PIN;

    I2C_SCL = I2C_LOW;
    SoftI2cNop();
    
    I2C_SDA = I2C_HIGH;
    SoftI2cNop();
    
    I2C_SCL = I2C_HIGH;
    SoftI2cNop();

    I2C_SDA = I2C_LOW;
    SoftI2cNop();
    
    I2C_SCL = I2C_LOW;
    SoftI2cNop();

}

void SoftI2cStop(void)
{
    TRIS_I2C_SDA = OUTPUT_PIN;
    
    I2C_SDA = I2C_LOW;
    SoftI2cNop();
    
    I2C_SCL = I2C_HIGH;
    SoftI2cNop();
    I2C_SDA = I2C_HIGH;
    SoftI2cNop();
    SoftI2cNop();
}

UI08_t SoftI2cTxByte(UI08_t data)
{
    UI08_t i;

    for(i = 0x80; i != 0; i >>= 1)
    {
        I2C_SCL = I2C_LOW;
        SoftI2cNop();

        if(data & i)
            I2C_SDA = I2C_HIGH;
        else
            I2C_SDA = I2C_LOW;
        TRIS_I2C_SDA = OUTPUT_PIN;

        SoftI2cNop();

        I2C_SCL = I2C_HIGH;
        SoftI2cNop();

        // TODO: Support clock stretching?
        //while((SCLPIN & (1<<SCL))==0);
    }

    //The 9th clock (ACK Phase)
    I2C_SCL = I2C_LOW;
    SoftI2cNop();

    TRIS_I2C_SDA = INPUT_PIN;
    
    I2C_SCL = I2C_HIGH;
    SoftI2cNop();

    UI08_t ack = !I2C_SDA_READ;

    I2C_SCL = I2C_LOW;
    SoftI2cNop();

    return ack;

}

UI08_t SoftI2cRxByte(UI08_t ack)
{
    UI08_t data=0x00;
    UI08_t i;

    I2C_SCL = I2C_LOW;
    SoftI2cNop();
    TRIS_I2C_SDA = INPUT_PIN;
    I2C_SDA = I2C_HIGH;
    
    for (i = 0x80; i != 0; i >>= 1)
    {
        I2C_SCL = I2C_LOW;
        SoftI2cNop();
        I2C_SCL = I2C_HIGH;
        SoftI2cNop();

        //Support clock stretching?
        //while((SCLPIN & (1<<SCL))==0);

        if(I2C_SDA_READ != 0)
            data |= i;

    }

    I2C_SCL = I2C_LOW;
    SoftI2cNop();

    TRIS_I2C_SDA = OUTPUT_PIN;
    if(ack)
    {
        I2C_SDA = I2C_LOW;
    }
    else
    {
        I2C_SDA = I2C_HIGH;
    }
    SoftI2cNop();

    I2C_SCL = I2C_HIGH;
    SoftI2cNop();

    I2C_SCL = I2C_LOW;
    SoftI2cNop();
    
    return data;

}




