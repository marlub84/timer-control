/* 
 * File:   lcd.c
 * Author: mario
 *
 * Created on 
 */

#include <xc.h>
#include "i2c.h"
#include "mcc_generated_files/mcc.h"
#include <stdint.h>

void I2C_Initialize()
{
    SSPCON1 = 0x28;
    SSPADD = 0x27;              // Bound rate clock generator, 100kH
    
    
}

void I2C_Write(uint8_t data)
{
    I2C_Wait();
    SSPBUF = data;
    I2C_Wait();
}

void I2C_Wait()
{
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
    __delay_us(5);
}

void I2C_Stop()
{
    STOP_BIT = 1;
    while(STOP_BIT == 1);
}