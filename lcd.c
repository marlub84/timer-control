/* 
 * File:   lcd.c
 * Author: mario
 *
 * Created on 25. ?ervence 2017, 18:09
 */

#include <xc.h>

#include "mcc_generated_files/mcc.h"
#include "lcd.h"
#include "timer.h"
#include "io.h"



void Enab(void)
{
    Enable = 1;
    __delay_us(1);
    Enable = 0;
    __delay_us(40);
    
}

void Clear(void)
{
    RS = 0;
    RW = 0;
    LCD_D = 0x01;
    Enab();
    __delay_ms(1.70); 
}

void Initialization(void)
{
    /*
     * Display initialize
     */
    __delay_ms(50);
    RS = 0;
    RW = 0;    
    LCD_D = 0b00111100;               // Set 8-bit system 
    Enab();
    /*
    LCD_D = 0b00011000;         // Cursor and shift
    Enab();*/
    LCD_D = 0x0E;               // Display ON, cursor ON, brinking ON
    Enab();
    
    LCD_D = 0b00000110;         // Mode set, increment, shifted
    Enab();
    /*
    LCD_D = 0b00000010;         // Cursor at home   
    Enab();
    __delay_ms(1.70);    
    LCD_D = 0b00000001;         // Clear display  
    Enab();
    __delay_ms(1.70); 
    */
}

void Write_LCD(uint8_t symbol)
{
    // Write data
    RS = 1;
    LCD_D = symbol;   
    Enab();
    RS = 0;
    
    // End write
}

void Start_LCD(void)
{
    //uint8_t i = 0;
        
    /*LCD_D = 0x08;           // Turn off display and cursor
    Enab();
    // Write text*/
    LCD_D = 0x80;            // Line 1
    Enab();
    // Pic 16f ver. 1.0
    Write_LCD(0x50);
    Write_LCD(0x69);
    Write_LCD(0x63);
    Write_LCD(0x20);
    Write_LCD(0x31);
    Write_LCD(0x36);
    Write_LCD(0x66);
    Write_LCD(0x20);
    Write_LCD(0x76);
    Write_LCD(0x65);
    Write_LCD(0x72);
    Write_LCD(0x2E);
    Write_LCD(0x20);
    Write_LCD(0x31);
    Write_LCD(0x2E);
    Write_LCD(0x30);

    LCD_D = 0xC0;           // Line 2
    Enab();
    // Author M.Lubina
    Write_LCD(0x41);
    Write_LCD(0x75);
    Write_LCD(0x74);
    Write_LCD(0x68);
    Write_LCD(0x6F);
    Write_LCD(0x72);
    Write_LCD(0x20);
    Write_LCD(0x4D);
    Write_LCD(0x2E);
    Write_LCD(0x4C);
    Write_LCD(0x75);
    Write_LCD(0x62);
    Write_LCD(0x69);
    Write_LCD(0x6E);
    Write_LCD(0x61);
    Write_LCD(0x20);
        
    /*LCD_D = 0x0C;           // Display ON
    Enab();*/
    __delay_ms(3000);
    LCD_D = 0x01;           // Clear display
    Enab();
    __delay_ms(1.7);
    LCD_D = 0x02;           // Cursor at home
    __delay_ms(1.7);
}

uint8_t NumToLcd(uint8_t iNum)
{
    // Convert number to LCD character
    uint8_t iConvert = 0;
    
    if (iNum <= 9)
    {
      switch (iNum)
      {
          case 0:
            iConvert = 0x30;
            break;
          case 1:
            iConvert = 0x31;
            break;
          case 2:
            iConvert = 0x32;
            break;
          case 3:
            iConvert = 0x33;
            break;
          case 4:
            iConvert = 0x34;
            break;
          case 5:
            iConvert = 0x35;
            break;
          case 6:
            iConvert = 0x36;
            break;
          case 7:
            iConvert = 0x37;
            break;
          case 8:
            iConvert = 0x38;
            break;
          case 9:
            iConvert = 0x39;
            break;
          default:
              iConvert = 0x30;
              break;
      }
    }
    else if (iNum >= 10)
    {
        iConvert = 0x30;
    }
    
    return iConvert;
}


void ShowTime(eSIG_TIME time)
{
    // Take data from timer and show
    // Set position of hours, minutes and secund
    
    sTime *tmp;
    // Control with timer is choice
    tmp = SignToTimer(time);
    // Show time from the input variable
    uint8_t symLcd;
    // show separator
    
    LCD_D = addr_sep1;
    Enab();
    Write_LCD(separator);
    
    LCD_D = addr_sep2;
    Enab();
    Write_LCD(separator);
    
    // Hours
    
    // Set hours position
    LCD_D = addr_Hours;
    Enab();
    if (tmp->sHH == 0)
    {
        Write_LCD(0x20);            // space symbol
        symLcd = NumToLcd(tmp->sHL);
        Write_LCD(symLcd);
    }else {
        symLcd = NumToLcd(tmp->sHH);
        Write_LCD(symLcd);            // number one
        symLcd = NumToLcd(tmp->sHL);
        Write_LCD(symLcd);
    }
    
    // Minutes 
     
    // Set separator
    LCD_D = addr_Minuts;                  
    Enab();
    symLcd = NumToLcd(tmp->sMH);
    Write_LCD(symLcd);            // number one
    symLcd = NumToLcd(tmp->sML);
    Write_LCD(symLcd);
            
    LCD_D = addr_Secund;
    Enab();
    symLcd = NumToLcd(tmp->sSH);
    Write_LCD(symLcd);            // number one
    symLcd = NumToLcd(tmp->sSL);
    Write_LCD(symLcd);
          
}

void Lcd_Menu()
{
    
    eSIG_BUTTON ebtn;
    int page = 0;
    eSIG_TIME setTime = 0;
    Clear();

    
    for(;;){
         /* Time setting
         * Time ON/OFF IO setting
         * TEST IO
         * 
         */ 
        LCD_D = 0x80;            // Line 1
        Enab();
        Write_LCD(0x20);
        Write_LCD(0x20);
        Write_LCD(0x20);
        Write_LCD(0x20);
        Write_LCD(0x20);
        Write_LCD(0x4D);        // M
        Write_LCD(0x45);        // E
        Write_LCD(0x4E);        // N
        Write_LCD(0x55);        // U
        Write_LCD(0x20);
        Write_LCD(0x20);
        Write_LCD(0x20);
        Write_LCD(0x20);
        Write_LCD(0x20);
        Write_LCD(0x20);
        
        Lcd_MenuIN(page, &setTime);
        
        // Check input
        __delay_ms(100);
        ebtn = Input_B();
        switch(ebtn)
        {
            case LEFT:
                // Clear display and go back to front
                Clear();
                ebtn = EMPTY;
                return;
            case DOWN:
                ebtn = EMPTY;
                page++;
                break;
            case RIGHT:
                // Choice setting
                switch(page)
                {
                    case 0:
                        Lcd_Set_Time(setTime);
                        Timer_Set_Time();
                        break;
                    case 1:
                        // Set time ON
                        Clear();
                        LCD_D = 0xC0;           // Line 2
                        Enab();
                        Write_LCD(0x20);
                        Write_LCD(0x43);
                        Write_LCD(0x61);
                        Write_LCD(0x73);
                        Write_LCD(0x6F);
                        Write_LCD(0x76);
                        Write_LCD(0x61);
                        Write_LCD(0x63);
                        Write_LCD(0x20);
                        Write_LCD(0x31);
                        Write_LCD(0x20);
                        Write_LCD(0x4F);
                        Write_LCD(0x4E);
                        Write_LCD(0x20);
                        Write_LCD(0x20);
                        Write_LCD(0x20);
                        Lcd_Set_Time(setTime);
                        setTime = T1_OFF;
                        Clear();
                        LCD_D = 0xC0;           // Line 2
                        Enab();
                        Write_LCD(0x20);
                        Write_LCD(0x43);
                        Write_LCD(0x61);
                        Write_LCD(0x73);
                        Write_LCD(0x6F);
                        Write_LCD(0x76);
                        Write_LCD(0x61);
                        Write_LCD(0x63);
                        Write_LCD(0x20);
                        Write_LCD(0x31);
                        Write_LCD(0x20);
                        Write_LCD(0x4F);
                        Write_LCD(0x46);
                        Write_LCD(0x46);
                        Write_LCD(0x20);
                        Write_LCD(0x20);
                        Lcd_Set_Time(setTime);
                        break;
                    case 2:
                        Clear();
                        LCD_D = 0xC0;           // Line 2
                        Enab();
                        Write_LCD(0x20);
                        Write_LCD(0x43);
                        Write_LCD(0x61);
                        Write_LCD(0x73);
                        Write_LCD(0x6F);
                        Write_LCD(0x76);
                        Write_LCD(0x61);
                        Write_LCD(0x63);
                        Write_LCD(0x20);
                        Write_LCD(0x32);
                        Write_LCD(0x20);
                        Write_LCD(0x4F);
                        Write_LCD(0x4E);
                        Write_LCD(0x20);
                        Write_LCD(0x20);
                        Write_LCD(0x20);
                        Lcd_Set_Time(setTime);
                        setTime = T2_OFF;
                        Clear();
                        LCD_D = 0xC0;           // Line 2
                        Enab();
                        Write_LCD(0x20);
                        Write_LCD(0x43);
                        Write_LCD(0x61);
                        Write_LCD(0x73);
                        Write_LCD(0x6F);
                        Write_LCD(0x76);
                        Write_LCD(0x61);
                        Write_LCD(0x63);
                        Write_LCD(0x20);
                        Write_LCD(0x32);
                        Write_LCD(0x20);
                        Write_LCD(0x4F);
                        Write_LCD(0x46);
                        Write_LCD(0x46);
                        Write_LCD(0x20);
                        Write_LCD(0x20);
                        Lcd_Set_Time(setTime);
                        break;
                    case 3:
                        Clear();
                        LCD_D = 0xC0;           // Line 2
                        Enab();
                        Write_LCD(0x20);
                        Write_LCD(0x43);
                        Write_LCD(0x61);
                        Write_LCD(0x73);
                        Write_LCD(0x6F);
                        Write_LCD(0x76);
                        Write_LCD(0x61);
                        Write_LCD(0x63);
                        Write_LCD(0x20);
                        Write_LCD(0x33);
                        Write_LCD(0x20);
                        Write_LCD(0x4F);
                        Write_LCD(0x4E);
                        Write_LCD(0x20);
                        Write_LCD(0x20);
                        Write_LCD(0x20);
                        Lcd_Set_Time(setTime);
                        setTime = T3_OFF;
                        Clear();
                        LCD_D = 0xC0;           // Line 2
                        Enab();
                        Write_LCD(0x20);
                        Write_LCD(0x43);
                        Write_LCD(0x61);
                        Write_LCD(0x73);
                        Write_LCD(0x6F);
                        Write_LCD(0x76);
                        Write_LCD(0x61);
                        Write_LCD(0x63);
                        Write_LCD(0x20);
                        Write_LCD(0x33);
                        Write_LCD(0x20);
                        Write_LCD(0x4F);
                        Write_LCD(0x46);
                        Write_LCD(0x46);
                        Write_LCD(0x20);
                        Write_LCD(0x20);
                        Lcd_Set_Time(setTime);
                        break;
                    case 4:
                        Test_IO();
                        break;
                }
                ebtn = EMPTY;
                break;
            case UP:
                ebtn = EMPTY;
                page--;
                break;
            case EMPTY:
                // Nothing TODO
                break;
            default:
                ebtn = EMPTY;
                break;
        }
        if (page > 4) page = 0;
        if (page < 0) page = 4;
    }
    
}

void Lcd_Front()
{
    LCD_D = 0xC0;           // Line 2
    Enab();
    
    Write_LCD(0x20);
    Write_LCD(0x4F);        // O
    Write_LCD(0x31);        // 1
    Write_LCD(0x2D);        // - 
    if (OUT_1 == 1){
        Write_LCD(0x48);    // H
    }
    else Write_LCD(0x4C); // L
    Write_LCD(0x20);
    Write_LCD(0x4F);        // O
    Write_LCD(0x32);        // 2
    Write_LCD(0x2D);        // - 
    if (OUT_2 == 1){
        Write_LCD(0x48);    // H
    }
    else Write_LCD(0x4C); // L
    Write_LCD(0x20);
    Write_LCD(0x4F);        // O
    Write_LCD(0x33);        // 3
    Write_LCD(0x2D);        // - 
    if (OUT_3 == 1){
        Write_LCD(0x48);    // H
    }
    else Write_LCD(0x4C); // L
    Write_LCD(0x20);
}

void Lcd_MenuIN(int iMenu, eSIG_TIME *choise)
{
    // TODO write setting menu in matters on input iMenu
    LCD_D = 0xC0;           // Line 2
    Enab();
    switch (iMenu)
    {
        case 0:
            // System time setting
            *choise = T0;
            
            LCD_D = 0xC0;           // Line 2
            Enab();
            Write_LCD(0x20);
            Write_LCD(0x4E);
            Write_LCD(0x61);
            Write_LCD(0x73);
            Write_LCD(0x74);
            Write_LCD(0x61);
            Write_LCD(0x76);
            Write_LCD(0x20);
            Write_LCD(0x68);
            Write_LCD(0x6F);
            Write_LCD(0x64);
            Write_LCD(0x69);
            Write_LCD(0x6E);
            Write_LCD(0x79);
            Write_LCD(0x20);
            Write_LCD(0x20);
            break;
        case 1:
            // Set timer 1
            *choise = T1_ON;
            
            LCD_D = 0xC0;           // Line 2
            Enab();
            Write_LCD(0x20);
            Write_LCD(0x43);
            Write_LCD(0x61);
            Write_LCD(0x73);
            Write_LCD(0x6F);
            Write_LCD(0x76);
            Write_LCD(0x61);
            Write_LCD(0x63);
            Write_LCD(0x20);
            Write_LCD(0x31);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            break;
        case 2:
            // Set timer 2
            *choise = T2_ON;
            
            LCD_D = 0xC0;           // Line 2
            Enab();
            Write_LCD(0x20);
            Write_LCD(0x43);
            Write_LCD(0x61);
            Write_LCD(0x73);
            Write_LCD(0x6F);
            Write_LCD(0x76);
            Write_LCD(0x61);
            Write_LCD(0x63);
            Write_LCD(0x20);
            Write_LCD(0x32);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            break;
        case 3:
            // Set timer 3
            *choise = T3_ON;
            
            LCD_D = 0xC0;           // Line 2
            Enab();
            Write_LCD(0x20);
            Write_LCD(0x43);
            Write_LCD(0x61);
            Write_LCD(0x73);
            Write_LCD(0x6F);
            Write_LCD(0x76);
            Write_LCD(0x61);
            Write_LCD(0x63);
            Write_LCD(0x20);
            Write_LCD(0x33);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            break;
        case 4:
            // Manual output control 
            LCD_D = 0xC0;           // Line 2
            Enab();
            Write_LCD(0x20);
            Write_LCD(0x54);
            Write_LCD(0x65);
            Write_LCD(0x73);
            Write_LCD(0x74);
            Write_LCD(0x20);
            Write_LCD(0x76);
            Write_LCD(0x79);
            Write_LCD(0x73);
            Write_LCD(0x74);
            Write_LCD(0x75);
            Write_LCD(0x70);
            Write_LCD(0x75);
            Write_LCD(0x20);
            Write_LCD(0x20);
            Write_LCD(0x20);
            break;  
    }

}

void Lcd_Set_Time(eSIG_TIME choisetime)
{
    // Temporary var to set time
    sTime *tmp;
    
    tmp = SignToTimer(choisetime);
    
    // Use ShowTime() function to show time set
    
    eSIG_BUTTON cursor;
    // set Secund to zero
    tmp->sSH = 0;
    tmp->sSL = 0;
    
    ShowTime(choisetime);
    uint8_t position;
    position = addr_Hours + 1;
    
    for (;;)
    {
        
        LCD_D = position;    
        Enab();
    
        __delay_ms(100);        
        cursor = Input_B();
        switch(cursor)
        {
            case LEFT:
                cursor = EMPTY;
                return;
                                
            case DOWN:
                // Free button
                cursor = EMPTY;
                break;
            case RIGHT:
                cursor = EMPTY;
                if (position == (addr_Minuts + 1))
                {
                    position = addr_Hours + 1;
                }
                else if (position == (addr_Hours + 1))
                {
                    position = addr_Minuts + 1;
                }
                LCD_D = position;    
                Enab();
                break;
            case UP:
                cursor = EMPTY;
                /* Change time value begin from hours
                 * 
                 */
                if(position == (addr_Hours + 1))
                {
                    tmp->sHL++;
                    
                    if (tmp->sHL > 4)
                    {
                        if (tmp->sHH == 2)
                            {
                                tmp->sHH = 0;
                                tmp->sHL = 0;
                            }
                        if (tmp->sHL > 9)
                        {
                            tmp->sHH++;
                            tmp->sHL = 0;                                                      
                        }                        
                    }
                    
                    ShowTime(choisetime);
                }
                if ((position == addr_Minuts) || (position == addr_Minuts + 1))
                {
                    tmp->sML++;
                    
                    if (tmp->sML > 9)
                    {
                        if (tmp->sMH == 5)
                        {
                            tmp->sMH = 0;
                            tmp->sML = 0;
                        }
                        else {
                            tmp->sML = 0;
                            tmp->sMH++;
                        }
                    }                    
                    // Show update time
                    ShowTime(choisetime);
                }
                break;
            case EMPTY:
                // Nothing TODO
                break;
        }
        
    }// end for
}

void ON()
{
    // Function write text on second line
    LCD_D = 0xC0;           // Line 2
    Enab();
    Write_LCD(0x20);
    Write_LCD(0x20);
    Write_LCD(0x20);
    Write_LCD(0x5A);
    Write_LCD(0x61);
    Write_LCD(0x70);
    Write_LCD(0x6E);
    Write_LCD(0x75);
    Write_LCD(0x74);
    Write_LCD(0x6F);
    Write_LCD(0x20);
    Write_LCD(0x20);
    Write_LCD(0x20);
    Write_LCD(0x20);
    Write_LCD(0x20);
    Write_LCD(0x20);
    
}

void OFF()
{
    // Function write text on second line
    LCD_D = 0xC0;           // Line 2
    Enab();
    Write_LCD(0x20);
    Write_LCD(0x20);
    Write_LCD(0x20);
    Write_LCD(0x56);
    Write_LCD(0x79);
    Write_LCD(0x70);
    Write_LCD(0x6E);
    Write_LCD(0x75);
    Write_LCD(0x74);
    Write_LCD(0x6F);
    Write_LCD(0x20);
    Write_LCD(0x20);
    Write_LCD(0x20);
    Write_LCD(0x20);
    Write_LCD(0x20);
    Write_LCD(0x20);
    
}