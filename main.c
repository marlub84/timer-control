/*
 * File:   main.c
 * Author: Mario
 *
 * Created on February 9, 2017, 3:23 AM
 */

#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/pin_manager.h"
#include "lcd.h"
#include "io.h"         // button definition
#include "timer.h"




int main(void)
{
    SYSTEM_Initialize();
    
    // Initialize display
    Initialization();
    Start_LCD();
    
    OUT_1 = 0;
    OUT_2 = 0;
    OUT_3 = 0;
    
    LCD_ON = 1;         // Backlight LCD
    eSIG_BUTTON button;
    eSIG_TIME showT = T0;
        
    // Prepare IO timer
    IO_Timer_Init(&Time1_ON);
    IO_Timer_Init(&Time2_ON);
    IO_Timer_Init(&Time3_ON);
    IO_Timer_Init(&Time1_OFF);
    IO_Timer_Init(&Time2_OFF);
    IO_Timer_Init(&Time3_OFF);
    
    // Timer start
    Timer_Init();    
    Timer_Set_Time();
    
    
    for(;;){
        
        
        // Read time data and show it
        Timer_Read_Time(TIMER_Hours);
        Timer_Read_Time(TIMER_Minuts);
        Timer_Read_Time(TIMER_Secunds);
        ShowTime(showT);
        Lcd_Front();
        
        // Check if time output is the same
        TimeControl();
        
        __delay_ms(100);
        button = Input_B();
        switch(button)
        {
            case LEFT:
                
                button = EMPTY;
                break;
            case DOWN:
                button = EMPTY;
                break;
            case RIGHT:
                Lcd_Menu();
                button = EMPTY;
                break;
            case UP:
                button = EMPTY;
                break;
            case EMPTY:
                // Nothing TODO
                break;
        }
    }

        
    return 0;
}
