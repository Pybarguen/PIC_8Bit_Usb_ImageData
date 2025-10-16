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
    
    TRISCbits.TRISC7 = 0;//Pin SDO    
    TRISBbits.TRISB5 = 1;//Pin SDI
    TRISBbits.TRISB4 = 0;//Pin SCL
    
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
        
      SSPM01 = 0;
      SSPM11 = 0;
      SSPM21 = 0;
      SSPM31 = 0;
      
    }
    
      if(data == SPI_MASTER_CLOCK_DIV_16)
    {
        SSPM01 = 1;
      SSPM11 = 0;
      SSPM21 = 0;
      SSPM31 = 0;
    
      
      
    }
    
       if(data == SPI_MASTER_CLOCK_DIV_64)
    {
        
      SSPM01 = 0;
      SSPM11 = 1;
      SSPM21 = 0;
      SSPM31 = 0;
      
      
      
      
    }
    
        if(data == SPI_MASTER_CLOCK_DI_TMR2_2)
    {
        
      SSPM01 = 1;
      SSPM11 = 1;
      SSPM21 = 0;
      SSPM31 = 0;
     
      
      
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

void write_dummy()
{
   
    
   
//    SSPBUF =  0X00;
//    while(SSPSTATbits.BF == 0);
//    while(PIR1bits.SSPIF == 0);
//    PIR1bits.SSPIF = 0;
//    
    
    PIR1bits.SSPIF = 0;       // Limpia flag de interrupci�n
    SSPBUF = 0xFF;            // Env�a 0xFF (valor est�ndar para lectura)
    while(!PIR1bits.SSPIF);   // Espera a que se complete la transferencia
    PIR1bits.SSPIF = 0;       // Limpia flag nuevamente
     
    
    
}