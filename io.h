/* 
 * File:   config.h
 * Author: mario
 *
 * Created on 25. ?ervence 2017, 17:48
 */

#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "timer.h"
/*
 * INPUT key definition
 */
    
#define BI_1 PORTAbits.RA0         // Left
#define BI_2 PORTAbits.RA1         // Right
#define BI_3 PORTAbits.RA2         // Down
#define BI_4 PORTAbits.RA3         // Up
    
#define OUT_1 LATAbits.LATA4      
#define OUT_2 LATAbits.LATA5
#define OUT_3 LATCbits.LATC5    
    
    // Signals from button
    typedef enum {LEFT = 0, DOWN, RIGHT, UP, EMPTY} eSIG_BUTTON; 

    
#define INT_TIMER LATCbits.LATC0
    
    // Input from button
    eSIG_BUTTON Input_B();
    void IO_Timer_Init(sTime *);
    void Test_IO();
    

#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

