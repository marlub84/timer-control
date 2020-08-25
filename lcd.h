/* 
 * File:   lcd.h
 * Author: mario
 *
 * Created on 25. ?ervence 2017, 18:09
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "timer.h"
 /*
 * OUTPUT LCD definition
 */
   
    
#define LCD_D           LATB 
#define RW              LATCbits.LATC6
#define RS              LATCbits.LATC2
#define LCD_ON          LATCbits.LATC1
#define Enable          LATCbits.LATC7
    
    // Address position
    
#define addr_Hours      0x83
#define addr_Minuts     0x86
#define addr_Secund     0x89
#define addr_sep1       0x85
#define addr_sep2       0x88
#define separator       0x3A

        
    void Enab(void);
    void Initialization(void);
    void Clear(void);
    void Write_LCD(uint8_t);
    void Start_LCD(void);
    void ShowTime(eSIG_TIME);
    uint8_t NumToLcd(uint8_t);
    void Lcd_Menu();
    void Lcd_Front();
    void Lcd_MenuIN(int, eSIG_TIME *);
    void Lcd_Set_Time(eSIG_TIME);
    void ON();
    void OFF();


#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

