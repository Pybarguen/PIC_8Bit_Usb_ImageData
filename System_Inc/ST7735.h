/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ST7735_H
#define	ST7735_H
#include <xc.h> // include processor files - each processor file is guarded.  
#include "Fonts.h"
//#include "St7735_Widgets.h"
//COMMANDS
#define SWRESET 0x01//Software reset
#define SLPIN   0x10//Sleep in and booster off
#define SLPOUT  0x11//Sleep out and booster on
#define PTLON   0x12//Partial mode on
#define NORON   0x13//Partial mode off normal mode on
#define INVOFF  0x20//display inversion off
#define INVON   0x21//display inversion on
#define GAMSET  0x26//Gamma curve select
#define DISPOFF 0x28//Display off
#define DISPON  0x29//Display on
#define CASET   0x2A//set column address
#define RASET   0x2B//set row address
#define RAMWR   0x2C//memory write
#define RAMRD   0x2E//memory read
#define PTLAR   0x30//Partial start/end address
#define TE0FF   0x34//tearing efect line off
#define TEON    0x35//tearing efect line on
#define IDMOFF  0x38//Idle mode off
#define IDMON   0x39//Idle mode on
#define COLMOD  0x3A//interface pixel format
#define MADCTL  0x36//memoty acces control




//FUNCTIONS
#define FRMCTR1 0xB1
#define FRMCTR2 0xB2
#define FRMCTR3 0xB3
#define INVCTR  0xB4//Display inversion control
#define DISSET5 0xB6
#define GMCTRP1 0xE0
#define GMCTRN1 0xE1
#define PWCTR1  0xC0//Power control for gamma settings
#define PWCTR2  0xC1
#define PWCTR3  0xC2//Power control in normal mode
#define PWCTR4  0xC3//Power control in idle mode 8 color
#define PWCTR5  0xC4//Power control in partial mode full colors
#define VMCTR1  0xC5
#define PWCTR6  0xFC



#include <stdint.h>

char image_high;
char image_low;
int color_img;
int background;
unsigned long k;
uint8_t i;
uint8_t j;
uint8_t Temporal_data;
uint8_t line_char;
unsigned long r = 1023;


//Varibles for temporal function control.
uint8_t Set_size =0;
uint8_t Temporal_data_y;
uint8_t Temporal_data_x;
uint8_t iterator;
char temporal_C;


//Union for cursor Location
typedef union {
   unsigned long Mouse;
   struct{
       unsigned char x_start;
       unsigned char y_start;
       unsigned char x_end;
       unsigned char y_end;
       
       
       
   }Position;
    
    
    
}Cursor;


Cursor Mouse_data;
Cursor *PMouse_data = &Mouse_data;

//ENUM for choose ST7735 MODEL
enum DISPLAY_MODEL{
    
    ST7735S_80_x_160,
    ST7735_128_x_160
    
    
};

enum DISPLAY_MODEL TFT_MODEL;


void write_color(uint8_t data)
{
   
   
    SSPBUF =  data;
    while(SSPSTATbits.BF == 0);
    while(PIR1bits.SSPIF == 0);
    PIR1bits.SSPIF = 0;
     
     
    
    
}

void ST7735_128_x_160_init() {
    
     DCs = 0; 
     CCS_ST7735 = 0;
    write_command(SWRESET);//software reset
    CCS_ST7735 = 1;
     __delay_ms(150);
     CCS_ST7735 = 0;
    write_command(SLPOUT);//sleep mode out
    CCS_ST7735 = 1;
     __delay_ms(255);  
     
     
     DCs = 0; 
     CCS_ST7735 = 0;
    write_command(FRMCTR1);//Frame rate control in normal mode
    DCs = 1; 
    write_data(0x01);
    write_data(0x2C);
    write_data(0x2D);
    CCS_ST7735 = 1;
    
    
    DCs = 0; 
    CCS_ST7735 = 0;
    write_command(FRMCTR2);//Frame rate control in idle mode
    DCs = 1; 
    write_data(0x01);
    write_data(0x2C);
    write_data(0x2D); 
    CCS_ST7735 = 1;
    
    
    DCs = 0; 
    CCS_ST7735 = 0;
    write_command(FRMCTR3);//Frame rate control in Partial mode
    DCs = 1; 
    write_data(0x01);
    write_data(0x2C);
    write_data(0x2D);
    write_data(0x01);
    write_data(0x2C);
    write_data(0x2D);
    CCS_ST7735 = 1;
    
    
    DCs = 0; 
    CCS_ST7735 = 0;
    write_command(INVCTR);//Display inversion control
    DCs = 1; 
    write_data(0x07);//Frame version in all modes
    CCS_ST7735 = 1;
    
    
    DCs = 0; 
    CCS_ST7735 = 0;
    write_command(PWCTR1);//Power control 1
    DCs = 1; 
    write_data(0x02);//4.7V
    write_data(0x02);//1.5uA
    CCS_ST7735 = 1;
    
    
    DCs = 0; 
    CCS_ST7735 = 0;
    write_command(PWCTR2);
    DCs = 1; 
    write_data(0xC5);//VGH VGL
    CCS_ST7735 = 1;
    
    
    DCs = 0; 
    CCS_ST7735 = 0;
    write_command(PWCTR3);
    DCs = 1; 
    write_data(0x0A);//
    write_data(0x00);//
    CCS_ST7735 = 1;
    
    DCs = 0; 
    CCS_ST7735 = 0;
    write_command(PWCTR4);
    DCs = 1; 
    write_data(0x8A);//
    write_data(0x2A);//
    CCS_ST7735 = 1;
    
    
    DCs = 0; 
    CCS_ST7735 = 0;
    write_command(PWCTR5);
    DCs = 1;
    write_data(0x8A);//
    write_data(0xEE);//
    CCS_ST7735 = 1;
    
      
    DCs = 0;  
    CCS_ST7735 = 0;
    write_command(INVOFF);//  
    write_command(COLMOD);//RGB pixel format
    DCs = 1;
    write_data(0x05);//16bit pixel
    CCS_ST7735 = 1;
    
    DCs = 0;  
    CCS_ST7735 = 0;
    write_command(MADCTL);//Memory access control
    DCs = 1;
    //write_data(0b01001000);//RGB mode   
     write_data(0b11110100);//RGB mode
    //write_data(0b11011000); //for image
    CCS_ST7735 = 1;
      __delay_ms(10);
      
      
      DCs = 0; 
      CCS_ST7735 = 0;
      write_command(GMCTRP1);//RGB pixel format 
      DCs = 1;
       write_data(0x02);write_data(0x1C);write_data(0x07);write_data(0x12);
       write_data(0x37);write_data(0x32);write_data(0x29);write_data(0x2D);
       write_data(0x29);write_data(0x25);write_data(0x2B);write_data(0x39);
       write_data(0x00);write_data(0x01);write_data(0x03);write_data(0x10);
       CCS_ST7735 = 1;
       
       
       DCs = 0;
       CCS_ST7735 = 0;
       write_command(GMCTRN1);//RGB pixel format 
       DCs = 1;
       write_data(0x03);write_data(0x1D);write_data(0x07);write_data(0x06);
       write_data(0x2E);write_data(0x2C);write_data(0x29);write_data(0x2D);
       write_data(0x2E);write_data(0x2E);write_data(0x37);write_data(0x3F);
       write_data(0x00);write_data(0x00);write_data(0x02);write_data(0x10);
       CCS_ST7735 = 1;
       
       
       
        DCs = 0;
        CCS_ST7735 = 0;
       write_command(NORON);//
        __delay_ms(10);
       write_command(DISPON);//
        __delay_ms(150);
        
        DCs = 0;   
        write_command(VMCTR1);
        DCs = 1;
        write_data(0x0E);//
       CCS_ST7735 = 1;
      
    
     
    

}


void ST7735S_Init(enum DISPLAY_MODEL data)
{
    TFT_MODEL  = data;
    if(data == ST7735S_80_x_160)
    {
        //ST7735S_80_x_160_init();
       ;;
        
    }
    else if(data == ST7735_128_x_160)
    {
        
        ST7735_128_x_160_init();
        
    }
    
    
}
void Set_Display_Cursor(uint8_t X_s, uint8_t Y_s, uint8_t X_end, uint8_t Y_end)
{
      if(TFT_MODEL == ST7735S_80_x_160)
    {
          
          
     PMouse_data->Position.y_start = 26+Y_s;
     PMouse_data->Position.x_start = 1+X_s;
     PMouse_data->Position.y_end = PMouse_data->Position.y_start+Y_end;
     PMouse_data->Position.x_end = PMouse_data->Position.x_start+X_end;
  
   
    }
    else if(TFT_MODEL== ST7735_128_x_160)
    {
     PMouse_data->Position.x_start = 2+X_s;  
     PMouse_data->Position.y_start = 1+Y_s;
     PMouse_data->Position.x_end = PMouse_data->Position.x_start+X_end;
     PMouse_data->Position.y_end = PMouse_data->Position.y_start+Y_end;
       
    
    }
  DCs = 0;
  CCS_ST7735 = 0;
  write_command(CASET);
  DCs = 1;
  write_data(0);
  write_data(PMouse_data->Position.y_start);
  write_data(0);
  write_data(PMouse_data->Position.y_end);
  DCs = 0;
  write_command(RASET);
  DCs = 1;
  write_data(0);
  write_data(PMouse_data->Position.x_start);
  write_data(0);
  write_data(PMouse_data->Position.x_end);
  
   
  DCs = 0;
  write_command(RAMWR); // Write to RAM
  CCS_ST7735 = 0; 
  DCs = 1; 
     
}

void Set_Color(int Temp_Color)
{
    
    
     
    if(TFT_MODEL == ST7735_128_x_160)
    {
        
        color_img = ~Temp_Color;
        
    }
    
    
    
}
 
    






void ST7735S_Fill_display(int color)
{
   
    i=0;
    j=0;
   
    
    background = color;
   
    if(TFT_MODEL == ST7735_128_x_160)
    {
      
  
     Set_Display_Cursor(0, 0, 128,160);
      Set_Color(color);  
    }    
       
    for(i=0; i<=PMouse_data->Position.y_end; i++)
  {
      for(j=0; j<=PMouse_data->Position.x_end; j++)
      {
   write_color(color_img >> 8);  
  write_color(color_img & 0xFF);

  }
    
    
}     
   
        
}
    
void ST7735S_Print_Char(int color, char C_char, uint8_t X_pos, uint8_t Y_pos, uint8_t Size)
{
   
  
         //PMouse_data->Position.y_end = PMouse_data->Position.y_start+((8*Size)-1);
         Temporal_data_y = ((8*Size)-1);
         Temporal_data_x = ((5*Size)-1);
       
      
  
 
  Set_Display_Cursor(X_pos, Y_pos, Temporal_data_x, Temporal_data_y);
  
   i=0;
   j=0;

 
  
 
 for(i=0; i<=4; i++)
  {
      
    
    
       line_char = font[C_char][i];
       for(int h=0; h<Size; h++)
       {
      for(j=0; j<=7; j++)
      {
         
            if(line_char & 1)
            {    Set_Color(color);   
                 
             for(Set_size =0; Set_size<=(Size-1); Set_size++)
                
                {    
                 write_color(color_img >> 8);  
                write_color(color_img & 0xFF); 
                     __delay_ms(1);   
             }
            }
                      
            else
            {            
              Set_Color(background);   
              for(Set_size =0; Set_size<=(Size-1); Set_size++)
                
                {   
                 write_color(color_img >> 8);  
                write_color(color_img & 0xFF); 
                __delay_ms(1); 
              }
                }
                  
           
            
          
           
          
          
          
        line_char>>=1;
        
     
        }
      if(j>=7)
      {
        line_char = font[C_char][i];
      }
      }
        
  
      }
      
 }
          
    


void ST7735S_Print_String(int color, char text[], uint8_t X_posa, uint8_t Y_pos, uint8_t Size)
{
   
    iterator = 0;
   do
    {
       
      temporal_C  =  text[iterator];  
      
      ST7735S_Print_Char(color, temporal_C, X_posa, Y_pos, Size);
      X_posa += (7*Size)+2;
      iterator ++;
    }while(temporal_C!='\0');
    
}
    


void ST7735S_Fill_image(int Image_arr[])


{
    
  
Set_Display_Cursor(0, 0,67,99);
        
        
      
  
  for(int i =0; i<=6800; i++)
  {
      
          
      color_img =  Image_arr[i];
      write_color(color_img >> 8);  
      write_color(color_img & 0xFF);
  
  }
}
#ifdef St7735_Widgets


void ST7735_Progress_Bar(ProgressBar *ProgressBarObj)
{
    
     P_ProgressBar_animation->Get_Values.Current_Value = 0x00;
     P_ProgressBar_animation->Get_Values.Last_Value = 0x00;
    
            
    Set_Display_Cursor(ProgressBarObj->Coordinates.x_start, ProgressBarObj->Coordinates.y_start,
    ProgressBarObj->Coordinates.Widht, ProgressBarObj->Coordinates.Height);
    
  

    
     for(i=0; i<=ProgressBarObj->Coordinates.Widht; i++)
     {
         for(j=0; j<=ProgressBarObj->Coordinates.Height; j++)
         {
             if(j==0 | i ==0 | i ==  ProgressBarObj->Coordinates.Widht| j == ProgressBarObj->Coordinates.Height )
             {
                 
                 Set_Color(ProgressBarObj->Coordinates.Color_border);                  
                    write_color(color_img >> 8);  
                    write_color(color_img & 0xFF);
                    
             }
             else{
                    Set_Color(ProgressBarObj->Coordinates.Color_background);                    
                    write_color(color_img >> 8);  
                    write_color(color_img & 0xFF);
                  
             }
          
             
             }
             
         
         
         
         
     }
      
        }

void ST7735_Animating_ProgressBar( ProgressBar *ProgressBarObj, unsigned long value, char text[])
{    
    
     P_ProgressBar_animation->Get_Values.Current_Value = (int)(value);
     
     if(P_ProgressBar_animation->Get_Values.Current_Value >= P_ProgressBar_animation->Get_Values.Last_Value)
     {
         
     PMouse_data->Position.x_start = 2+ ProgressBarObj->Coordinates.x_start;   
     PMouse_data->Position.y_start = 27+ ProgressBarObj->Coordinates.y_start; 
     PMouse_data->Position.x_end = ( PMouse_data->Position.x_start + (ProgressBarObj->Coordinates.Widht-1));
     PMouse_data->Position.y_end = ( PMouse_data->Position.y_start + (ProgressBarObj->Coordinates.Height-2));
     k = ((value*ProgressBarObj->Coordinates.Widht)/r);
     color_img = 0xE0E0;
     
     DCs = 0;    
    write_command(MADCTL);//Memory access control
    DCs = 1;
    //  write_data(0b11110100);//RGB mode
      write_data(0b11110100);//RGB mode    
     }
     
     
     else
     {
     PMouse_data->Position.x_start = 132-ProgressBarObj->Coordinates.Widht-1;   
     PMouse_data->Position.y_start = 27+ ProgressBarObj->Coordinates.y_start; 
     PMouse_data->Position.x_end = 132;
     PMouse_data->Position.y_end = ( PMouse_data->Position.y_start + (ProgressBarObj->Coordinates.Height-2));
      k = 70-((value*ProgressBarObj->Coordinates.Widht)/r);
     DCs = 0;    
    write_command(MADCTL);//Memory access control
    DCs = 1;
    //  write_data(0b11110100);//RGB mode
      write_data(0b10110100);//RGB mod
     color_img = 0xF0F0;
     }
     P_ProgressBar_animation->Get_Values.Last_Value = (int)(value);
     /*
     PMouse_data->Position.x_start = 2+ ProgressBarObj->Coordinates.x_start;   
     PMouse_data->Position.y_start = 27+ ProgressBarObj->Coordinates.y_start; 
     PMouse_data->Position.x_end = ( PMouse_data->Position.x_start + (ProgressBarObj->Coordinates.Widht-1));
     PMouse_data->Position.y_end = ( PMouse_data->Position.y_start + (ProgressBarObj->Coordinates.Height-2));
 
       */
    
    
        DCs = 0;
        write_command(CASET);
        DCs = 1;
        write_data(0);
        write_data(PMouse_data->Position.y_start);//ST7735S column start in address 25
        write_data(0);
        write_data(PMouse_data->Position.y_end);
        DCs = 0;
        write_command(RASET);
        DCs = 1;
        write_data(0);
        write_data(PMouse_data->Position.x_start);
        write_data(0);
        write_data(PMouse_data->Position.x_end);


        DCs = 0;
        write_command(RAMWR); // Write to RAM
        CCS_ST7735 = 0; 
        DCs = 1; 
       
  
        
        
   
         for(i=0; i<k; i++)
         {
             
              for( j=0; j<=(ProgressBarObj->Coordinates.Height-2); j++)
              {
                  write_color(color_img >> 8);  
                    write_color(color_img & 0xFF);
                     __delay_ms(10);
                 

              }
    
         }
}
void print_7_segments(uint8_t X_pos, uint8_t Y_pos, char number, uint8_t Size, int color)
{
 
     
      Temporal_data_y = ((16*Size)-1);
      Temporal_data_x = ((8*Size)-1);
       
      
      Set_Display_Cursor(X_pos, Y_pos, Temporal_data_x, Temporal_data_y);
 
    
      
      for(i=0;i<=7;i++)
      {
          
      line_Display_pixel = Segments_Display_pixel[number-48][i];
          for(iterator=0; iterator<Size; iterator++)
       {
      
      for(j=0;j<=15;j++)
      {
          if( line_Display_pixel & 1)
          {      Set_Color(color);   
               for(Set_size =0; Set_size<=(Size-1); Set_size++)
                
                {    
                 write_color(color_img >> 8);  
                write_color(color_img & 0xFF); 
                     __delay_ms(1);   
             } 
                  
          }
          else
          {
              
            Set_Color(background); 
              for(Set_size =0; Set_size<=(Size-1); Set_size++)
                
                {   
                 write_color(color_img >> 8);  
                write_color(color_img & 0xFF); 
                __delay_ms(1); 
              }
          }
           line_Display_pixel>>=1;  
      }
      if(j>=15)
      {
      line_Display_pixel  = Segments_Display_pixel[number-48][i];
      }
    
}
    
}
  
 
    
    
 
}
void print_7_segments_string(uint8_t X_pos, uint8_t Y_pos, char display_number[], uint8_t Size, int color)
{
   
    uint8_t Wix;
    Wix = 0;
   do
    {
       
      temporal_C  = display_number[Wix];  
      if(temporal_C != '\0'){
      print_7_segments(X_pos, Y_pos, temporal_C, Size, Blue_Color); 
      X_pos += (7*Size)+4;
      
      }
     Wix++;
    }while(temporal_C!='\0');
    
}
    
#endif

     
     /*
     if(TFT_MODEL==1)
         
    {
     PMouse_data->Position.y_start = 26;
     PMouse_data->Position.x_start = 1;
     PMouse_data->Position.y_end = PMouse_data->Position.y_start+80;
     PMouse_data->Position.x_end = PMouse_data->Position.x_start+159;
    }
      * */
    
    
    
    






#endif	/* XC_HEADER_TEMPLATE_H */

