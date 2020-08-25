/* 
 * File:   i2c.h
 * Author: mario
 *
 * Created on 7. zá?í 2017, 8:31
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif
#define ACKSTAT     SSPCON2bits.ACKSTAT
#define ACKDT       SSPCON2bits.ACKDT
#define START_BIT   SSPCON2bits.SEN             // Start condition bit
#define STOP_BIT    SSPCON2bits.PEN             // Start Stop condition bit
#define ACK_BIT     SSPCON2bits.ACKEN           // Start ACK condition bit
#define RCV_BIT     SSPCON2bits.RCEN            // Enables receiver mode
#define BF_BIT      SSPSTATbits.BF              // Buffer is full
    
    
#include <stdint.h>
    
    void I2C_Initialize();
    void I2C_Write(uint8_t );
    void I2C_Wait();
    void I2C_Stop();
    


#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

