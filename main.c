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
#define CCS_ST7735 LATBbits.LATB2
#define DCs  LATBbits.LATB3
#define RES LATBbits.LATB4
/** INCLUDES *******************************************************/
#include "system.h"
#include <stdio.h>
#include "app_device_cdc_basic.h"
#include "app_led_usb_status.h"

#include "usb.h"
#include "usb_device.h"
#include "usb_device_cdc.h"

#include "Fonts.h"
#include "Pic18f4550_spi.h"
#include "ST7735.h"

static  unsigned char readBuffer[CDC_DATA_OUT_EP_SIZE];
static uint8_t writeBuffer[CDC_DATA_IN_EP_SIZE];


uint8_t i;
uint8_t numBytesRead;

                    

                    
void Processing_Data(uint8_t Data[])
{
    
         
         //Clear Display Command, String = clc
        if(Data[0]==99 && Data[1]==108 && Data[2]==99)
        {
            
            ST7735S_Fill_display(Black_Color);            
            //putUSBUSART(writeBuffer,3);
            CDCTxService();
                    
               
            
             
        }
        
        
        
        if(Data[0]==112 && Data[1]==105 && Data[2]==103)
        {
            
            //ST7735S_Fill_display(White_Color);            
            //putUSBUSART(writeBuffer,3);
            Set_Display_Cursor(0, 0, 63, 91); 
            CDCTxService();
            
            
            while(readBuffer[0]!=99 || readBuffer[1]!=114)
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
       
        
        int byte_control;
        char value;
        byte_control = getsUSBUSART(readBuffer, sizeof(readBuffer));
       
       if(byte_control > 0)
       { 
            
           
             sprintf(value, "%d", readBuffer[0]);    
          
           
            for(i=0; i<byte_control; i++)
            {    
             write_color(readBuffer[i]);  
            
             
            }
             
              putUSBUSART(writeBuffer,3);
            CDCTxService();
             
            
            }
               
            
             
        }
                   
                    CDCTxService();
            }
        
                    
                    
                    
            
            } 
              
    
    
   
    
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
        
        Processing_Data(readBuffer);
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
    SYSTEM_Initialize(SYSTEM_STATE_USB_START);

    USBDeviceInit();
    USBDeviceAttach();
    
    writeBuffer[0] = 79;
                    writeBuffer[1] = 107;
                    writeBuffer[2] = 10;
                    writeBuffer[3] = 13;
                    
    
    
    //SPI
   Spi_init();//start spi interface
   Spi_mode(CPOL_1_CPHA_0);//SPI mode 0 0 
   Spi_clock_mode(SPI_MASTER_CLOCK_DIV_4);//SPI clock = FOSC/4 
   TRISBbits.RB2 = 0;//SLAVE control PIN
   TRISBbits.RB3 = 0;//output DC comman/data ST7735 control
   TRISBbits.RB4 = 0;//output DC comman/data ST7735 control
   
   __delay_ms(10);
    RES = 1;
    CCS_ST7735 = 1; 
    DCs = 0;
   
   ST7735S_Init(ST7735_128_x_160);
    ST7735S_Fill_display(Black_Color); 
   
                 
    
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
