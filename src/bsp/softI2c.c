#include "bsp/softI2c.h"

void SoftI2cInit(void)
{
    // Configure as inputs
    TRIS_I2C_SCL = OUTPUT_PIN;
    TRIS_I2C_SDA = OUTPUT_PIN;

#ifdef I2C_PK2_MIRROR
    TRIS_I2C_MIRROR_SCL = OUTPUT_PIN;
    TRIS_I2C_MIRROR_SDA = OUTPUT_PIN;
#endif

    // Write '0' (=HIGH)
    I2C_SCL = I2C_HIGH;
    I2C_SDA = I2C_HIGH;

    // Enable weak pullups
    // Should be disabled during sleep
    WP_I2C_SDA = 1; // SDA
    WP_I2C_SCL = 0; // SCL
}

void SoftI2cNop(void)
{
    I2C_MIRROR();
    __delay_us(50);
    I2C_MIRROR();
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
    SoftI2cNop();
    SoftI2cNop();
    SoftI2cNop();
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

    I2C_SDA = I2C_HIGH;
    TRIS_I2C_SDA = INPUT_PIN;
    SoftI2cNop();

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




