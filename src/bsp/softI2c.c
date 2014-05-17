#include "bsp/softI2c.h"

void SoftI2cNop()
{
    // 10=24.5kHz
    // 50=7kHz
    // 500 = 700Hz or so
    // @ 16MHz PIC
    __delay_us(10);
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

    for(i = 0; i < 8; i++)
    {
        I2C_SCL = I2C_LOW;
        SoftI2cNop();

        if(data & 0x80)
            I2C_SDA = I2C_HIGH;
        else
            I2C_SDA = I2C_LOW;
        TRIS_I2C_SDA = OUTPUT_PIN;

        SoftI2cNop();

        I2C_SCL = I2C_HIGH;
        SoftI2cNop();

        //while((SCLPIN & (1<<SCL))==0);

        data = data << 1;
    }

    //The 9th clock (ACK Phase)
    I2C_SCL = I2C_LOW;
    SoftI2cNop();

    //I2C_SDA = I2C_HIGH;
    TRIS_I2C_SDA = INPUT_PIN;
    
    I2C_SCL = I2C_HIGH;
    SoftI2cNop();

    UI08_t ack= !I2C_SDA_READ;

    I2C_SCL = I2C_LOW;
    SoftI2cNop();
    SoftI2cNop();
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
    
    for(i = 0; i < 8; i++)
    {
        I2C_SCL = I2C_LOW;
        SoftI2cNop();
        I2C_SCL = I2C_HIGH;
        SoftI2cNop();

        //while((SCLPIN & (1<<SCL))==0);

        if(I2C_SDA_READ != 0)
            data |= (0x80 >> i);

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
    SoftI2cNop();
    SoftI2cNop();

    return data;

}




