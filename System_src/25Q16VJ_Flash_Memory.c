/*
 * File:   25Q16VJ_Flash_Memory.c
 * Author: LENOVO
 *
 * Created on 10 de junio de 2025, 08:56 PM
 */

//#include <25Q16VJ_Flash_Memory.h>
#include <xc.h>
#include <25Q16VJ_Flash_Memory.h>
#define _XTAL_FREQ 48000000
AddressBytes AddressMemory;
/**
 * Funcion para leer el JEDEC ID de la memoria WINBOND
 * 
 * 
 * @param id Puntero de la estructura donde se guardara los datos
 */

void Read_Device_ID(MemoryID *id)

{   

  
    CCS_Memory = 0;
    write_command(0X9F);
    write_dummy();
    id->manufacturer = SSPBUF;

    write_dummy();

    id->memory_type = SSPBUF;
    write_dummy();
    id->capacity = SSPBUF;
     CCS_Memory = 1;

    

     
    
}


void Memory_state()
{
   

   
    CCS_Memory = 0;
    do{
     
        write_command(Read_Status_Register1);
       write_dummy();
    Busy_state_memory = (SSPBUF & 0x01); 
        
    }while(Busy_state_memory==1);
   CCS_Memory = 1;

}


void Write_Page_Program(uint32_t Page_write, int size_data)
{
    AddressMemory.address = Page_write;
    
    
    CCS_Memory = 0;
    write_command(Write_enable);//0x06 command
     CCS_Memory = 1;
     
    __delay_us(1);
    
    CCS_Memory = 0;
    write_command(Page_Program);//0x02
    write_command(AddressMemory.high_byte);
    write_command(AddressMemory.mid_byte);
    write_command(AddressMemory.low_byte); 
    for(int writer=0; writer<=size_data; writer++)
    {
     write_data(0xE0);    
    }
     CCS_Memory = 1;
     
      Memory_state();
     
        __delay_ms(10);
        
     
}
    
    
    
    /**
 * Funcion para leer el Direccion y unico Bytede la memoria WINBOND
 * 
 * 
 * @param id recibe la direccion de la memoria de 24bits
 */



void Read_Address(int *value)
{
    

    AddressMemory.address = 0x000000;
    CCS_Memory = 0;
    write_command(Read_data);
     write_command(AddressMemory.high_byte);
    write_command(AddressMemory.mid_byte);
    write_command(AddressMemory.low_byte);
    write_dummy();
    *value = SSPBUF;
    CCS_Memory = 1;
    
    
}



void Sector_erase()
{
    CCS_Memory = 0;
    write_command(Write_enable);//0x06 command
    CCS_Memory = 1;
     
    __delay_us(1);
    
    
    
    AddressMemory.address = 0x000000;
    CCS_Memory = 0;
    write_command(Sector_Erase_4Kb);
    write_command(AddressMemory.high_byte);
    write_command(AddressMemory.mid_byte);
    write_command(AddressMemory.low_byte);  
   
    CCS_Memory = 1;
    Memory_state();
    __delay_ms(900);
    
}

    
    
