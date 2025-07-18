/*
 * File:   ST7735.c
 * Author: LENOVO
 *
 * Created on 13 de junio de 2025, 05:35 AM
 */



#include <ST7735.h>

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


