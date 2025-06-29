/*
 * File:   25Q16VJ_Flash_Memory.c
 * Author: LENOVO
 *
 * Created on 10 de junio de 2025, 08:56 PM
 */

//#include <25Q16VJ_Flash_Memory.h>
#include <xc.h>
#include <25Q16VJ_Flash_Memory.h>

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

void Write_Page_Program()
{
    CCS_Memory = 0;
    write_command(Write_enable);
    write_command(Page_Program);
    
    
    
    
    
    
}