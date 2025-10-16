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
#ifndef _USB_DATA_PROCESS_H
#define	_USB_DATA_PROCESS_H
#include <system.h>
#include <ST7735.h>
#include "usb_device_cdc.h"
#include <Fonts.h>
#include <xc.h>
#include "usb_config.h"
enum Reception_data_state{
     
     WAITING_IMGS_NUMBERS,            
     WAITING_IMGS_DATA,  
     READY_FOR_IMG_PIXELS,
     SET_DATA_POINT,
     SUSPENDED,
     MD
    
             
     
     
     
 }; 
enum Reception_data_state transfer_state;

typedef struct
{
    int width;
    uint8_t height;
    int size;
    
    
    
}Image_data;

Image_data Control_Image;


extern unsigned char readBuffer[CDC_DATA_OUT_EP_SIZE];
extern uint8_t writeBuffer[CDC_DATA_IN_EP_SIZE];
extern char dataprint[10];

void Process_Command(unsigned char *buffer);
void Processing_Data(unsigned char Data[], uint8_t byte_control);


#endif	/* XC_HEADER_TEMPLATE_H */

