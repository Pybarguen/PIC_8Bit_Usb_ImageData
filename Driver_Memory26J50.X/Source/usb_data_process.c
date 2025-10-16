/*
 * File:   usb_data_process.c
 * Author: LENOVO
 *
 * Created on 9 de octubre de 2025, 05:27 PM
 */


#include <usb_data_process.h>

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
              
          
             
           
             
             transfer_state = SET_DATA_POINT;
         
           
            
  
             
    
}

                    
void Processing_Data(unsigned char Data[], uint8_t byte_control)
{
    uint8_t idx=0;
     char String_Buffer[];//Buffer to print char in the display
     
     if(transfer_state == SET_DATA_POINT)
     {
         
              
                      Set_Display_Cursor(0, 0, (Control_Image.width-1), (Control_Image.height-1)); 
                        transfer_state = READY_FOR_IMG_PIXELS;
           
           
          
      
             
              
          
         
     }
     if(transfer_state == READY_FOR_IMG_PIXELS && byte_control==64)
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

               
            
             
        
                   
                 
           