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
#ifndef FLASH_25Q16VJ_MEMORY_H  
#define FLASH_25Q16VJ_MEMORY_H

#include <Spi_Interface.h>



//Information : Winbond Flash Memory Commands
#define Write_enable 0x06
#define Volatile_SR_Write_E 0x50
#define Write_Disable 0x04
#define PowerDown_ID 0xAB
#define Device_ID 0x90
#define JEDEC_ID 0x9F
#define Read_data 0x03
#define Fast_read 0x0B
#define Page_Program 0x02
#define Sector_Erase_4Kb 0x20
#define Block_Erase_32Kb 0x52
#define Block_Erase_64Kb 0xD8
#define Chip_Erase 0xC7
#define Read_Status_Register1 0x05
#define Write_Status_Register1 0x01
#define Read_Status_Register2 0x35
#define Write_Status_Register2 0x31
#define Read_Status_Register3 0x15
#define Write_Status_Register3 0x11

//PIN OUTPUT for Memory COntrol SPI Interface
#define CCS_Memory LATDbits.LATD4

//COntrol Page Memory
#define PAGE_SIZE 256

//Variable for State Memory Control Read After o Before Write O Erase Flash Memory
uint8_t Busy_state_memory;


//Memory ID Variables
typedef struct {
    
    uint8_t manufacturer;
    uint8_t memory_type;
    uint8_t capacity;
}MemoryID;


//Struct for COntrol 24bit Flash Memory Address
typedef union {
   uint32_t address; 
   struct {
       uint8_t low_byte;
       uint8_t mid_byte;
       uint8_t high_byte;
   };
}AddressBytes;


/**
 * Funtion Read_Device_ID(MemoryID *id)
 * @brief Read Memory Flash ID
 * @param MemoryID STRUCT 
 * @return Nothing.
 */
void Read_Device_ID(MemoryID *id);


/**
 * Funtion Write_Page_Program(uint32_t Page_write, int size_data)
 * @brief Write Byte in the Flash Memory each page can be allow 256byte
 *        page 0 = 0x000000 to 0x0000FF 
 * @param Page_Write Address and Size of data to Write
 * @return Nothing.
 */
void Write_Page_Program(AddressBytes AddressMemory, int size_data);

/**
 * Funtion Read_Address(int *address)
 * @brief Read a single Byte to 25bit Flash memory Address
 * @param Struct AddressBytes 24bit flash memory address
 * @return Nothing.
 */

void Read_Address(AddressBytes AddressMemory, int *value);


/**
 * Funtion Read_Page(uint32_t Address_Page, uint8_t Buffer[256])
 * @brief Read a Complete Flash memory Page the data allow in memory_buffer[256] array
 * @param Struct AddressBytes Address_Page 24bit address pag, buffer to read de data Buffer[256] = memory_buffer[256] array
 * @return Nothing.
 */
void Read_Page(AddressBytes AddressMemory, uint8_t Buffer[256]);




/**
 * Funtion Sector_erase(AddressBytes AddressMemory);
 * @brief Erase 4Kb sector in the flash memory
 * @param Struct AddressBytes ---   24Bit Addres to Respective Sector 
 * @return Nothing.
 */
void Sector_erase_4kb(AddressBytes AddressMemory);



#endif	/* XC_HEADER_TEMPLATE_H */

