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

#include "system.h"


/** CONFIGURATION Bits **********************************************/
/** CONFIGURATION Bits **********************************************/
#pragma config WDTEN = OFF          // WDT disabled (enabled by SWDTEN bit)
#pragma config PLLDIV = 2           // Divide by 2 (8 MHz internal oscillator / 2 = 4 MHz)
#pragma config STVREN = ON          // Stack overflow/underflow reset enabled
#pragma config XINST = OFF          // Extended instruction set disabled
#pragma config CPUDIV = OSC1        // No CPU system clock divide
#pragma config CP0 = OFF            // Program memory is not code-protected
#pragma config OSC = INTOSCPLL      // Internal oscillator with PLL enabled
#pragma config FCMEN = OFF          // Fail-Safe Clock Monitor disabled
#pragma config IESO = OFF           // Two-Speed Start-up disabled
#pragma config WDTPS = 32768        // 1:32768
#pragma config DSWDTOSC = INTOSCREF // DSWDT uses INTOSC/INTRC as clock
#pragma config RTCOSC = T1OSCREF    // RTCC uses T1OSC/T1CKI as clock
#pragma config DSBOREN = OFF        // Zero-Power BOR disabled in Deep Sleep
#pragma config DSWDTEN = OFF        // Disabled
#pragma config DSWDTPS = 8192       // 1:8,192 (8.5 seconds)
#pragma config IOL1WAY = OFF        // IOLOCK bit can be set and cleared
#pragma config MSSP7B_EN = MSK7     // 7 Bit address masking
#pragma config WPFP = PAGE_1        // Write Protect Program Flash Page 0
#pragma config WPEND = PAGE_0       // Start protection at page 0
#pragma config WPCFG = OFF          // Write/Erase last page protect Disabled
#pragma config WPDIS = OFF          // WPFP[5:0], WPEND, and WPCFG bits ignored
#pragma config T1DIG = ON           // Sec Osc clock source may be selected
#pragma config LPT1OSC = OFF        // High power Timer1 mode
 

