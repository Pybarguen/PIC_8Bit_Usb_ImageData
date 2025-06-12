/*
 * File:   Spi_Interface.c
 * Author: LENOVO
 *
 * Created on 11 de junio de 2025, 08:30 PM
 */


#include <xc.h>
#include <Spi_Interface.h>

  

void Spi_init()
{
    
    TRISCbits.RC7 = 0;//Pin SDO
    TRISBbits.RB0 = 1;//Pin SDI
    TRISBbits.RB1 = 0;//Pin SCK
    
    SSPCON1bits.SSPEN = 1;//SPI Enable
}

void Spi_mode(enum SPI_MODES data)
{
    if(data == CPOL_0_CPHA_0)
    {
       
        SSPCON1bits.CKP = 0;
        SSPSTATbits.CKE = 0;
     
    }
    else if(data == CPOL_0_CPHA_1)
    {
        
          SSPCON1bits.CKP = 0;
          SSPSTATbits.CKE = 1;
    }
    else if(data == CPOL_1_CPHA_0)
    {
        
           SSPCON1bits.CKP = 1;
          SSPSTATbits.CKE = 0;
    }
    
    else if(data == CPOL_1_CPHA_1)
    {
        
       SSPCON1bits.CKP = 1;
           SSPSTATbits.CKE = 1;
    }
}

void Spi_clock_mode(enum Spi_master_clock_modes data)

{
    if(data == SPI_MASTER_CLOCK_DIV_4)
    {
        
      SSPM0 = 0;
      SSPM1 = 0;
      SSPM2 = 0;
      SSPM3 = 0;
      
      
    }
    
      if(data == SPI_MASTER_CLOCK_DIV_16)
    {
        
      SSPM0 = 1;
      SSPM1 = 0;
      SSPM2 = 0;
      SSPM3 = 0;
      
      
    }
    
       if(data == SPI_MASTER_CLOCK_DIV_64)
    {
        
      SSPM0 = 0;
      SSPM1 = 1;
      SSPM2 = 0;
      SSPM3 = 0;
      
      
    }
    
        if(data == SPI_MASTER_CLOCK_DI_TMR2_2)
    {
        
      SSPM0 = 1;
      SSPM1 = 1;
      SSPM2 = 0;
      SSPM3 = 0;
      
      
    }
    
    
}

void write_command(int command)
{
 

    SSPBUF =  command;
    while(SSPSTATbits.BF == 0);
    while(PIR1bits.SSPIF == 0);
    PIR1bits.SSPIF = 0;
   
  
     
    
    
}

void write_data(int data)
{
   
    
   
    SSPBUF =  data;
    while(SSPSTATbits.BF == 0);
    while(PIR1bits.SSPIF == 0);
    PIR1bits.SSPIF = 0;
    
     
    
    
}