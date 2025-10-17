/*
 * File:   25Q16VJ_Flash_Memory.c
 * Author: LENOVO
 *
 * Created on 10 de junio de 2025, 08:56 PM
 */

#include <25Q16VJ_Flash_Memory.h>


uint8_t Memory_Buffer[256];
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


void Write_Page_Program(AddressBytes AddressMemory, int size_data, uint8_t Buffer[256])
{

    
    
    CCS_Memory = 0;
    write_command(Write_enable);//0x06 command
     CCS_Memory = 1;
     
    __delay_us(1);
    
    CCS_Memory = 0;
    write_command(Page_Program);//0x02
    write_command(AddressMemory.high_byte);
    write_command(AddressMemory.mid_byte);
    write_command(AddressMemory.low_byte); 
    
    for(int writer=0; writer<PAGE_SIZE; writer++)
    {
         write_data(Buffer[writer]); 
    }
     CCS_Memory = 1;
     
      Memory_state();
     
        __delay_ms(20);
        
     
}
void Read_Page(AddressBytes AddressMemory, uint8_t Buffer[256])
{
    
    
  
    CCS_Memory = 0;
    write_command(Read_data);
     write_command(AddressMemory.high_byte);
        __delay_us(3);
    write_command(AddressMemory.mid_byte);
       __delay_us(3);
    write_command(AddressMemory.low_byte);
       __delay_us(3);
    for(int reader=0; reader<PAGE_SIZE; reader++)
    {
        
        write_dummy();
        Buffer[reader] = SSPBUF;
        
    }
    
    
    CCS_Memory = 1;
    __delay_ms(1);
    
    
}
    
    



void Read_Address(AddressBytes AddressMemory, int *value)
{
    

    
    CCS_Memory = 0;
    write_command(Read_data);
     write_command(AddressMemory.high_byte);
    write_command(AddressMemory.mid_byte);
    write_command(AddressMemory.low_byte);
    write_dummy();
    *value = SSPBUF;
    CCS_Memory = 1;
    
    
}



void Sector_erase_4kb(AddressBytes AddressMemory)
{
    CCS_Memory = 0;
    write_command(Write_enable);//0x06 command
    CCS_Memory = 1;
     
    __delay_us(1);
    
    
    

    CCS_Memory = 0;
    write_command(Sector_Erase_4Kb);
    write_command(AddressMemory.high_byte);
    write_command(AddressMemory.mid_byte);
    write_command(AddressMemory.low_byte);  
   
    CCS_Memory = 1;
    Memory_state();
    __delay_ms(900);
    
}

void Block_Erase_64KB(AddressBytes AddressMemory)
{
    CCS_Memory = 0;
    write_command(Write_enable);//0x06 command
    CCS_Memory = 1;
     
    __delay_us(1);
    
    
    

    CCS_Memory = 0;
    write_command(Block_Erase_64Kb);
    write_command(AddressMemory.high_byte);
    write_command(AddressMemory.mid_byte);
    write_command(AddressMemory.low_byte);  
   
    CCS_Memory = 1;
    Memory_state();
    __delay_ms(900);
    
}

void set_page(AddressBytes AddressMemory)

{
    
    
    CCS_Memory = 0;
    write_command(Write_enable);//0x06 command
     CCS_Memory = 1;
     
    __delay_us(1);
    
    CCS_Memory = 0;
    write_command(Page_Program);//0x02
    write_command(AddressMemory.high_byte);
    write_command(AddressMemory.mid_byte);
    write_command(AddressMemory.low_byte);
    
    
}

void write_memory_data(uint8_t data)

{
    
    SSPBUF =  data;
    while(SSPSTATbits.BF == 0);
    while(PIR1bits.SSPIF == 0);
    PIR1bits.SSPIF = 0;
    
}
    
