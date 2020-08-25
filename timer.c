/* 
 * File:   lcd.c
 * Author: mario
 *
 * Created on 
 */

#include <xc.h>
#include "timer.h"
#include "i2c.h"
#include "mcc_generated_files/mcc.h"
#include "io.h"


void Timer_Init()
{
    START_BIT = 1;
    I2C_Write(TIMER_Write);
    
    I2C_Write(0x00);            //Configure address
    I2C_Write(0x80);            //Configure timer 1000 0000 stop count
    
    I2C_Stop();
}

void Timer_Set_Time()
{
    // Set time
    
    uint8_t tmpH, tmpM, tmpS;
    tmpH = ASCI_BCD(TimeS.sHH, TimeS.sHL);
    tmpM = ASCI_BCD(TimeS.sMH, TimeS.sML);
    tmpS = ASCI_BCD(TimeS.sSH, TimeS.sSL);      // secund
       
    START_BIT = 1;
    I2C_Write(TIMER_Write);
    I2C_Write(TIMER_Secunds);
       
    // Time data
    
    I2C_Write(tmpS);
    I2C_Write(tmpM);
    I2C_Write(tmpH);
    
    I2C_Stop();
    
    // Start counting
    START_BIT = 1;
    I2C_Write(TIMER_Write);
    I2C_Write(0x00);            //Configure address    
    I2C_Write(0x00);            //Configure timer 0000 0000
    I2C_Stop();
}

void Timer_Read_Time(uint8_t address)
{
    // Read all time 
    // and write to global high and low variable
    uint8_t tmp;
    START_BIT = 1;
    I2C_Write(TIMER_Write);
    
    // Write address to slave
    I2C_Write(address);
    
    START_BIT = 1;
    // Send address to read to slave
    I2C_Write(TIMER_Read);

    // Set master as receive and
    // wait to buffer full and receive is finish
    RCV_BIT = 1;
    while ((BF_BIT == 0) && RCV_BIT == 1);    
    tmp = SSPBUF;
    
    // send stop bit and wait for clear
    I2C_Stop();
    
    // Check address and convert data
    if (address == TIMER_Hours){
        BCD_ASCI(tmp, &TimeS.sHH, &TimeS.sHL);
    }
    else if (address == TIMER_Minuts){
        BCD_ASCI(tmp, &TimeS.sMH, &TimeS.sML);
    }
    else if (address == TIMER_Secunds){
        BCD_ASCI(tmp, &TimeS.sSH, &TimeS.sSL);
    }
    
}

void BCD_ASCI(uint8_t iData, uint8_t *Nhigh, uint8_t *Nlow)
{
    /* Function convert 8 bit number to 4 bit low and high bits
     * 
     */
    
    uint8_t tmp;
    // jednotky, posun 4 do leva a posun 4 do prava
    tmp = iData;
    tmp <<= 4;
    tmp >>= 4;
    *Nlow = tmp;
    // desitky, posun 4 do prava
    tmp = iData;
    tmp >>= 4;
    *Nhigh = tmp;
}

uint8_t ASCI_BCD(uint8_t Ntens, uint8_t Nunits)
{
    uint8_t iVar;
    uint8_t tmp;
    tmp = Ntens;
    tmp <<= 4;
    iVar = tmp | Nunits;
    return iVar;
}


sTime* SignToTimer(eSIG_TIME t)
{
        // Control with timer is choice
    if (t == T0){
        return &TimeS;
    }else if (t == T1_ON){
        return &Time1_ON;
    }else if (t == T2_ON){
        return &Time2_ON;
    }else if (t == T3_ON){
        return &Time3_ON;
    }else if (t == T1_OFF){
        return &Time1_OFF;
    }else if (t == T2_OFF){
        return &Time2_OFF;
    }else if (t == T3_OFF){
        return &Time3_OFF;
    }
    // If something is bad back system time
    return &TimeS;
}

void TimeControl()
{
    /* Function control system time with timer of output
     * and turn ON/OFF output port 
     * */
    
    // Check time ON
    if (Time1_ON.sHH == TimeS.sHH && Time1_ON.sHL == TimeS.sHL){
        // if hours is the same check minutes
        if (Time1_ON.sMH == TimeS.sMH && Time1_ON.sML == TimeS.sML)
        {
            // Turn output 2 ON
            OUT_1 = 1;
        }
    }
    if (Time2_ON.sHH == TimeS.sHH && Time2_ON.sHL == TimeS.sHL){
        // if hours is the same check minutes
        if (Time2_ON.sMH == TimeS.sMH && Time2_ON.sML == TimeS.sML)
        {
            // Turn output 1 ON
            OUT_2 = 1;
        }
    }
    if (Time3_ON.sHH == TimeS.sHH && Time3_ON.sHL == TimeS.sHL){
        // if hours is the same check minutes
        if (Time3_ON.sMH == TimeS.sMH && Time3_ON.sML == TimeS.sML)
        {
            // Turn output 3 ON
            OUT_3 = 1;
        }
    }
    
    // Check timer OFF
    else if (Time1_OFF.sHH == TimeS.sHH && Time1_OFF.sHL == TimeS.sHL){
        // if hours is the same check minutes
        if (Time1_OFF.sMH == TimeS.sMH && Time1_OFF.sML == TimeS.sML)
        {
            // Turn output 2 ON
            OUT_1 = 0;
        }
    }
    else if (Time2_OFF.sHH == TimeS.sHH && Time2_OFF.sHL == TimeS.sHL){
        // if hours is the same check minutes
        if (Time2_OFF.sMH == TimeS.sMH && Time2_OFF.sML == TimeS.sML)
        {
            // Turn output 1 ON
            OUT_2 = 0;
        }
    }
    else if (Time3_OFF.sHH == TimeS.sHH && Time3_OFF.sHL == TimeS.sHL){
        // if hours is the same check minutes
        if (Time3_OFF.sMH == TimeS.sMH && Time3_OFF.sML == TimeS.sML)
        {
            // Turn output 3 ON
            OUT_3 = 0;
        }
    }
}