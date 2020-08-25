/* 
 * File:   io.c
 * Author: mario
 *
 * Created on 
 */

#include <xc.h>
#include <stdint.h>
#include "mcc_generated_files/mcc.h"        // clock definition
#include "io.h"
#include "timer.h"
#include "lcd.h"


eSIG_BUTTON Input_B()
{
    // Input button
    static eSIG_BUTTON tmp;
    tmp = EMPTY;
    
    if (BI_1 == 0 || BI_2 == 0 || BI_3 == 0 || BI_4 == 0)
    {
        __delay_ms(100);
        if (BI_2 == 0){ 
            tmp = DOWN;
        }
        if (BI_3 == 0){              
            tmp = RIGHT;
        }
        if (BI_4 == 0){
            tmp = UP;
        }
        if (BI_1 == 0){                
            tmp = LEFT;
        }   
    }
    else tmp = EMPTY;
    return tmp;
}

void IO_Timer_Init(sTime *setTime)
{
    sTime *tmp = setTime;
       
    tmp->sHH = 0;
    tmp->sHL = 6;
    tmp->sMH = 0;
    tmp->sML = 0;
    tmp->sSH = 0;
    tmp->sSL = 0;
      
}

void Test_IO()
{
    // Manual test 
    Clear();
    eSIG_BUTTON button;
    int8_t page;
    
    for(;;)
    {
        // Write menu corresponding to output
        
        if (page == 0)
        {
            LCD_D = 0x80;            // Line 1
            Enab();
            Write_LCD(0x20);
            Write_LCD(0x56);
            Write_LCD(0x79);
            Write_LCD(0x73);
            Write_LCD(0x74);
            Write_LCD(0x75);
            Write_LCD(0x70);
            Write_LCD(0x20);
            Write_LCD(0x31);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            if (OUT_1 == 1){
                ON();
            }else OFF();
        }
        else if (page == 1)
        {
            LCD_D = 0x80;
            Enab();
            Write_LCD(0x20);
            Write_LCD(0x56);
            Write_LCD(0x79);
            Write_LCD(0x73);
            Write_LCD(0x74);
            Write_LCD(0x75);
            Write_LCD(0x70);
            Write_LCD(0x20);
            Write_LCD(0x32);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            if (OUT_2 == 1){
                ON();
            }else OFF();
        }
        else if (page == 2)
        {
            LCD_D = 0x80;
            Enab();
            Write_LCD(0x20);
            Write_LCD(0x56);
            Write_LCD(0x79);
            Write_LCD(0x73);
            Write_LCD(0x74);
            Write_LCD(0x75);
            Write_LCD(0x70);
            Write_LCD(0x20);
            Write_LCD(0x33);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            if (OUT_3 == 1){
                ON();
            }else OFF();
        }
        __delay_ms(200);
        button = Input_B();
        switch(button)
        {
            case LEFT:
                // Clear display and go back to front
                Clear();
                return;
                //break;
            case DOWN:
                page += 1;
                break;
            case RIGHT:
                // On/Off output
                switch(page)
                {
                    case 0:
                        if (OUT_1 == 1){
                            OUT_1 = 0;                           
                        }else {
                            OUT_1 = 1;
                        }
                        break;
                    case 1:
                        if (OUT_2 == 1){
                            OUT_2 = 0;                           
                        }else {
                            OUT_2 = 1;                            
                        }
                        break;
                    case 2:
                        if (OUT_3 == 1){
                            OUT_3 = 0;                            
                        }else {
                            OUT_3 = 1;                            
                        }
                        break;
                }
                
                break;
            case UP:
                page -= 1;
                break;
            case EMPTY:
                // Nothing TODO
                break;
        }
        if (page > 2){
            page = 0;
        }else if (page < 0){
            page = 2;
        }
        
    }// end for
    
}