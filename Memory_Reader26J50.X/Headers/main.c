/*
 * File:   main.c
 * Author: LENOVO
 *
 * Created on 16 de octubre de 2025, 08:05 PM
 */

#include <system.h>
#include <Spi_Interface.h>
#include "25Q16VJ_Flash_Memory.h"
#include <Fonts.h>
#include <ST7735.h>

    

char String_Buffer[12];
    

/********************************************************************
 * Function:        void main(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Main program entry point.
 *
 * Note:            None
 *******************************************************************/
MAIN_RETURN main(void)
{
    // Configurar el oscilador interno
OSCCONbits.IRCF = 0b111;    // 8 MHz internal oscillator
OSCCONbits.SCS = 0b10;      // Internal oscillator block
 OSCTUNEbits.PLLEN = 1;//ON Internal OScilator

     
    
      //SPI
   Spi_init();//start spi interface
   Spi_mode(CPOL_1_CPHA_0);//SPI mode 0 0 
   Spi_clock_mode(SPI_MASTER_CLOCK_DIV_4);//SPI clock = FOSC/4 
   TRISCbits.TRISC2 = 0;
   TRISCbits.TRISC1 = 0;
   TRISCbits.TRISC6 = 0;
   TRISBbits.TRISB4 = 0;
   
    AddressMemory.address = 0x000000;
    MemoryID test;

     
   ANCON0  = 0xFF;//All analog Pins are Digital NOW  

    CCS_ST7735 = 1;
    CCS_Memory = 1;
    
    DCs = 0;
       
   //TFT DISPLAY INIT
    ST7735S_Init(ST7735_128_x_160);
     ST7735S_Fill_display(Yellow_Color);
     
     CCS_ST7735 = 1;
   __delay_ms(10);
   
    Read_Device_ID(&test);
    
     sprintf(String_Buffer, "0x%02X", test.manufacturer);    
     ST7735S_Print_String(Blue_Color, String_Buffer, 0, 0, 2);
     
    
  
    
    while(1)
    {
        
       

    }
}