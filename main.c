/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

To request to license the code under the MLA license (www.microchip.com/mla_license), 
please contact mla_licensing@microchip.com
*******************************************************************************/

/** INCLUDES *******************************************************/


#define _STDIO_H    // 
#define _STDLIB_H   // 

#include "system.h"
#include "Spi_Interface.h" 


#include <stdlib.h>

#include <string.h>
#include "app_device_cdc_basic.h"
#include "app_led_usb_status.h"

#include "usb.h"
#include "usb_device.h"
#include "usb_device_cdc.h"

#include "Fonts.h"

#include "ST7735.h"
#include "25Q16VJ_Flash_Memory.h"
AddressBytes AddressMemory;

static  unsigned char readBuffer[CDC_DATA_OUT_EP_SIZE];



static uint8_t writeBuffer[CDC_DATA_IN_EP_SIZE];
char memory_buffer[256];

uint8_t i;
uint8_t numBytesRead;
uint8_t control_page =0;
uint8_t numImgs = 0;
int testi=0;
int date =0;
char dataprint[10];
typedef struct
{
    int width;
    uint8_t height;
    int size;
    
    
    
}Image_data;


Image_data Control_Image;

enum Reception_data_state{
     
     WAITING_IMGS_NUMBERS,            
     WAITING_IMGS_DATA,  
     READY_FOR_IMG_PIXELS,
     SUSPENDED,
     MD
    
             
     
     
     
 }; 
enum Reception_data_state transfer_state;


void Process_Command(unsigned char *buffer)
{
    
    
    
    
    char grupo1[4], grupo2[4], grupo3[4];
    
   
    for(uint8_t p =0; p<=2; p++)
    {
        grupo1[p]= buffer[p];
        grupo2[p]= buffer[4+p];
        grupo3[p]= buffer[8+p];
    }
    
    grupo1[3] = '\0';
    grupo2[3] = '\0';
    grupo3[3] = '\0';
 
    
    Control_Image.width = atoi(grupo1);
    Control_Image.height = atoi(grupo2);
    Control_Image.size = atoi(grupo3);
    
    
           sprintf(dataprint, "%d", Control_Image.width);  
          ST7735S_Print_String(Blue_Color, dataprint, 0, 0, 2);
          
           sprintf(dataprint, "%d", Control_Image.height);  
          ST7735S_Print_String(Blue_Color, dataprint, 0, 40, 2);
          
           sprintf(dataprint, "%d", Control_Image.size);  
          ST7735S_Print_String(Blue_Color, dataprint, 0, 60, 2);
          
          
          
              ST7735S_Fill_display(Yellow_Color); 
               //Send Command Ok
             writeBuffer[0] = 82;//R
                writeBuffer[1] = 101;//e
                    writeBuffer[2] = 97;//a
                        writeBuffer[3] = 100;//d
                            writeBuffer[4] = 121;//y
                                writeBuffer[5] = 10;//New Line
                                    writeBuffer[6] = 13;//CR
                                 
                      putUSBUSART(writeBuffer,6);
                        CDCTxService();
              
          
             
           
             
             transfer_state = READY_FOR_IMG_PIXELS;
         
           
            
  
             
    
}

                    
void Processing_Data(unsigned char Data[], uint8_t byte_control)
{
    uint8_t idx=0;
     char String_Buffer[];//Buffer to print char in the display
     
     if(transfer_state == READY_FOR_IMG_PIXELS)
     {
         
              
                      Set_Display_Cursor(0, 0, 63, 91); 
                        transfer_state = SUSPENDED;
           
           
          
      
             
              
          
         
     }
     if(transfer_state == SUSPENDED && byte_control==64)
      {
        
         
          
          //Do while cr command is not in the buffer 
                    
    
    
                
            for(int rx=0; rx<byte_control; rx++)
            {  
             
                 __delay_us(1);
             write_color(readBuffer[rx]);             
             
            }
                 
                
                 
            }
    
          
          
          
      
     
      if(transfer_state == WAITING_IMGS_DATA && byte_control==11)
          
      {
          Process_Command(readBuffer);
      }
   
         
         //Clear Display Command, String = clc
        if(Data[0]==99 && Data[1]==108 && Data[2]==99)
        {
              //Send Command Ok
             writeBuffer[0] = 79;
                writeBuffer[1] = 107;
                    writeBuffer[2] = 10;
                        writeBuffer[3] = 13;
                    putUSBUSART(writeBuffer,3);
           CDCTxService();
    
   
                   
            
                    
               
            
             
        }
     
     //Test Command
        if(Data[0]==84 && Data[1]==101 && Data[2]==115 && Data[3]==116 )
            
        {
            
            //Send Command Okt Request Test byte
             writeBuffer[0] = 79;
                writeBuffer[1] = 107;
                    writeBuffer[2] = 116;
                    writeBuffer[3] = 10;
                        writeBuffer[4] = 13;
                    putUSBUSART(writeBuffer,4);
           CDCTxService();
            
            
        }
        
        
        
        //pimg Command Put image data command
        if(Data[0]==112 && Data[1]==105 && Data[2]==109 && Data[3]==103)
            
        {
            
            
             
            //Send Command Ok
             writeBuffer[0] = 79;
                writeBuffer[1] = 107;
                    writeBuffer[2] = 10;
                        writeBuffer[3] = 13;
                    putUSBUSART(writeBuffer,3);
           CDCTxService();
            
            //Fill White the display
            ST7735S_Fill_display(Green_Color);             
            transfer_state = WAITING_IMGS_DATA;
            //Set Display Cursor
            
                
            
             Control_Image.width = 0;//Restart Image width data
                    Control_Image.height = 0;//Restart Image height data
                            Control_Image.size = 0;//Restart Image size data
                  
        }
     
     
      
            
                
                
      
 
    
   

        
           
//            if(control_page<4)   
//            {
//                
//            for(i=0; i<byte_control; i++)
//            {  
//             
//                 __delay_us(1);
//             write_color(readBuffer[i]);             
//             
//             memory_buffer[(control_page * 64) + i] = readBuffer[i];
//             
//            }
//            control_page = control_page+1;
//            }
//            if(control_page==4)
//            {
//               // CCS_ST7735 = 1;
//              //   __delay_ms(1);
//              //  Write_Page_Program(AddressMemory, PAGE_SIZE, memory_buffer);
//             
//              //  CCS_Memory = 1;
//                 AddressMemory.address += 0x000100;
//                 control_page=0;
//                 
//                
//                 
//            }
            
            
         //  }
             
            
          }

               
            
             
        
                   
                 
           
        
                    
                    
                    
            
            
              
    
    
   
    



void Get_USB_Data()
{
    /* If the USB device isn't configured yet, we can't really do anything
     * else since we don't have a host to talk to.  So jump back to the
     * top of the while loop. */
    if( USBGetDeviceState() < CONFIGURED_STATE )
    {
        return;
    }

    /* If we are currently suspended, then we need to see if we need to
     * issue a remote wakeup.  In either case, we shouldn't process any
     * keyboard commands since we aren't currently communicating to the host
     * thus just continue back to the start of the while loop. */
    if( USBIsDeviceSuspended()== true )
    {
        return;
    }
        
    
    if( USBUSARTIsTxTrfReady() == true)
    {
       
        

        numBytesRead = getsUSBUSART(readBuffer, sizeof(readBuffer));
       if(numBytesRead > 0)
       {
        /* For every byte that was read... */
//        for(i=0; i<numBytesRead; i++)
//        {
//            switch(readBuffer[i])
//            {
//                /* If we receive new line or line feed commands, just echo
//                 * them direct.
//                 */
//                case 0x0A:
//                case 0x0D:    
//                        
//                    
//                    
//                    
//                    
//                    
//                    
//                    break;
//
//                /* If we receive something else, then echo it plus one
//                 * so that if we receive 'a', we echo 'b' so that the
//                 * user knows that it isn't the echo enabled on their
//                 * terminal program.
//                 */
//                default:
//                   //writeBuffer[i] = readBuffer[i];
//                    break;
//            }
//        }
        
        Processing_Data(readBuffer, numBytesRead );
       }
        
//        if(numBytesRead > 0)
//        {
//            /* After processing all of the received data, we need to send out
//             * the "echo" data now.
//             */
//            ;;
//           // putUSBUSART(writeBuffer,numBytesRead);
//        }
    
    }
      
    CDCTxService();
    
}






MAIN_RETURN main(void)
{
    
    
    
    Control_Image.width =0;
Control_Image.height =0;
Control_Image.size =0;
    
     AddressMemory.address = 0x000000;
      MemoryID test;
      test.manufacturer = 0;
      test.memory_type = 0;
      test.capacity = 0;
      
      
 
    SYSTEM_Initialize(SYSTEM_STATE_USB_START);

    USBDeviceInit();
    USBDeviceAttach();
    
    
    
  
                   
    
    
    //SPI
   Spi_init();//start spi interface
   Spi_mode(CPOL_1_CPHA_0);//SPI mode 0 0 
   Spi_clock_mode(SPI_MASTER_CLOCK_DIV_4);//SPI clock = FOSC/4 
   TRISBbits.RB2 = 0;//SLAVE control PIN ST7735
   TRISDbits.RD4 = 0;//SLAVE control PIN MEMORY
   TRISBbits.RB3 = 0;//output DC comman/data ST7735 control
   TRISBbits.RB4 = 0;//output DC comman/data ST7735 control
   
   __delay_ms(10);
    RES = 1;
    CCS_ST7735 = 1;
    CCS_Memory = 1;
    DCs = 0;
   
   ST7735S_Init(ST7735_128_x_160);
    ST7735S_Fill_display(Black_Color); 
    CCS_ST7735 = 1;
   __delay_ms(10);
   
   
   transfer_state = SUSPENDED;
  
   
//    Read_Device_ID(&test);
 //  AddressMemory.address = 0x000000;
 // Sector_erase_4kb(AddressMemory);
 //     Block_Erase_64KB(AddressMemory);
 //    __delay_ms(900);
//    Write_Page_Program(AddressMemory, 256);
//    Read_Address(AddressMemory, &date);
 //   Read_Page(AddressMemory, memory_buffer);
//       
//
//         
//          sprintf(String_Buffer, "0x%02X", test.manufacturer);    
//     ST7735S_Print_String(Blue_Color, String_Buffer, 0, 0, 2);
//     
//      sprintf(String_Buffer, "%d", date);  
//      ST7735S_Print_String(Blue_Color, String_Buffer, 0, 40, 2);
//      
//       sprintf(String_Buffer, "hola");  
//      ST7735S_Print_String(Blue_Color, String_Buffer, 0, 60, 2);
      
//      
//           __delay_ms(1000);   
//                  __delay_ms(1000);  
     
     /*
     ST7735S_Fill_display(White_Color); 
     //Set_Display_Cursor(0, 0, 63, 91);  
     Set_Display_Cursor(0, 0, 63, 91); 
      
     for(int mr=0; mr<46; mr++)
     {
          CCS_ST7735 = 1;
           __delay_ms(1);
         Read_Page(AddressMemory, memory_buffer);
          CCS_ST7735 = 0;
           __delay_ms(1);
          
     for(int mt=0; mt<256; mt++)
            {
           __delay_ms(10);
             write_color(memory_buffer[mt]);  
             
             
            }
           
           
      AddressMemory.address += 0x000100;
     
    }
   */
      CCS_ST7735 = 1;
    CCS_Memory = 1;
     

    while(1)
    {
        SYSTEM_Tasks();

        #if defined(USB_POLLING)
            
        #endif

        //Application specific tasks
        Get_USB_Data();
       
        
   
  

         
        
    }//end while
}//end main

/*******************************************************************************
 End of File
*/
