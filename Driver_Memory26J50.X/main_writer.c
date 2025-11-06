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
#include <system.h>
#include <Spi_Interface.h>
#include <Fonts.h>
#include <ST7735.h>

#include "app_device_cdc_basic.h"
#include "app_led_usb_status.h"


#include "usb.h"
#include "usb_device.h"
#include "usb_device_cdc.h"

#include <usb_data_process.h>
#include "25Q16VJ_Flash_Memory.h"
unsigned char readBuffer[CDC_DATA_OUT_EP_SIZE];
uint8_t writeBuffer[CDC_DATA_IN_EP_SIZE];
char memory_buffer[256];
char String_Buffer[12];
uint8_t i;
uint8_t numBytesRead;
uint8_t control_page =0;
uint8_t numImgs = 0;
int testi=0;
int date =0;
char dataprint[10];





















        
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

    SYSTEM_Initialize(SYSTEM_STATE_USB_START);

    USBDeviceInit();
    USBDeviceAttach();
    
        Control_Image.width =0;
Control_Image.height =0;
Control_Image.size =0;
    
      //SPI
   Spi_init();//start spi interface
   Spi_mode(CPOL_1_CPHA_0);//SPI mode 0 0 
   Spi_clock_mode(SPI_MASTER_CLOCK_DIV_4);//SPI clock = FOSC/4 
  TRISCbits.TRISC2 = 0;
   TRISCbits.TRISC1 = 0;
   TRISCbits.TRISC6 = 0;
   TRISBbits.TRISB4 = 0;
     
   ANCON0  = 0xFF;//All analog Pins are Digital NOW  
   
     
   
   AddressMemory.address = 0x000000;
    MemoryID test;

    CCS_ST7735 = 1;
    CCS_Memory = 1;
    DCs = 0;
       
   //TFT DISPLAY INIT
    ST7735S_Init(ST7735_128_x_160);
     ST7735S_Fill_display(Purple_Color);
     
     CCS_ST7735 = 1;
   __delay_ms(10);

    
    
    
    
    
    
    
   Read_Device_ID(&test);
    
    sprintf(String_Buffer, "0x%02X", test.manufacturer);    
    ST7735S_Print_String(Blue_Color, String_Buffer, 0, 0, 2);
    Block_Erase_64KB(AddressMemory);
    __delay_ms(900);
    ST7735S_Fill_display(White_Color);
    

    
    while(1)
    {
        SYSTEM_Tasks();

        #if defined(USB_POLLING)
            // Interrupt or polling method.  If using polling, must call
            // this function periodically.  This function will take care
            // of processing and responding to SETUP transactions
            // (such as during the enumeration process when you first
            // plug in).  USB hosts require that USB devices should accept
            // and process SETUP packets in a timely fashion.  Therefore,
            // when using polling, this function should be called
            // regularly (such as once every 1.8ms or faster** [see
            // inline code comments in usb_device.c for explanation when
            // "or faster" applies])  In most cases, the USBDeviceTasks()
            // function does not take very long to execute (ex: <100
            // instruction cycles) before it returns.
            USBDeviceTasks();
        #endif

        //Application specific tasks
            Get_USB_Data();
       

    }//end while
}//end main

/*******************************************************************************
 End of File
*/
