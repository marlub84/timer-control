/* 
 * File:   timer.h
 * Author: mario
 *
 * Created on 7. zá?í 2017, 9:43
 */

#ifndef TIMER_H
#define	TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdint.h>
    // Global variable 
    // System time storage

    // Signals to different time setting
    /*  T1 correspond to OUT_1
     *  T2 to OUT_2
     *  T3 to OUT_3
     *  T0 to system time
     * */
    typedef enum {T0, T1_ON, T2_ON, T3_ON, T1_OFF, T2_OFF, T3_OFF} eSIG_TIME;
    
    // Time storage for input
    typedef struct { uint8_t sHH;
                     uint8_t sHL;
                     uint8_t sMH;
                     uint8_t sML;
                     uint8_t sSH;
                     uint8_t sSL;
    }sTime;
    
    sTime TimeS;
    sTime Time1_ON;
    sTime Time2_ON;
    sTime Time3_ON;
    sTime Time1_OFF;
    sTime Time2_OFF;
    sTime Time3_OFF;
    
#define TIMER_Read              0b10100001
#define TIMER_Write             0b10100000
    
// Timer address
    
#define TIMER_Hours             0x04
#define TIMER_Minuts            0x03
#define TIMER_Secunds           0x02
    

    void Timer_Init();
    void Timer_Set_Time();
    void Timer_Read_Time(uint8_t);
        
    void BCD_ASCI(uint8_t iData, uint8_t *Nhigh, uint8_t *Nlow);
    uint8_t ASCI_BCD(uint8_t Ntens, uint8_t Nunits);
    // Control signal and back choiced timer
    sTime* SignToTimer(eSIG_TIME);
    
    void TimeControl();
    
    


#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */

