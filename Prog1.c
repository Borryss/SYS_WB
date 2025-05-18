
#pragma config POSCMOD = XT             
 
#pragma config OSCIOFNC = ON           
 
#pragma config FCKSM = CSDCMD           
 
#pragma config FNOSC = PRI              
 
#pragma config IESO = ON                
 
#pragma config WDTPS = PS32768        
 
#pragma config FWPSA = PR128            
 
#pragma config WINDIS = ON              
 
#pragma config FWDTEN = ON              
 
#pragma config ICS = PGx2               
 
#pragma config GWRP = OFF               
 
#pragma config GCP = OFF                
 
#pragma config JTAGEN = OFF     

#include "xc.h"
#include "libpic30.h"
#include "adc.h"
#include "buttons.h"
#include <stdlib.h>

int main(void) {
    uint8_t portValue = 0x00, counter = 0x00, queue = 0x80;
    char current6 = 0, prev6 = 0;
    char current13 = 0, prev13 = 0;
    int program = 1;
    int left = 1;
    TRISA = 0x0000;
    TRISD = 0xFFFF;
    AD1PCFG = 0xFFFF;
    srand(1110011);

    while (1) {
        LATA = portValue;

        switch (program) {
            case 1:
                counter++;
                portValue = counter;
                break;
            case 2:
                counter--;
                portValue = counter;
                break;
            case 3:
                counter++;
                portValue = counter ^ (counter >> 1);  
                break;
            case 4:
                counter--;
                portValue = counter ^ (counter >> 1);  
                break;
            case 5:
                counter++;
                portValue = ((counter / 10) << 4) | (counter % 10);  
                break;
            case 6:
                counter--;
                portValue = ((counter / 10) << 4) | (counter % 10); 
                break;
            case 7:
                if (portValue & 0x80) left = 0;
                if (portValue & 0x01) left = 1;
                portValue = (left) ? (portValue << 1) : (portValue >> 1);
                break;
            case 8:
                if (queue & 0x01)
                    queue = 0x80;
                else if (counter & queue) {
                    counter = 0x01;
                    queue |= (queue >> 1);
                } else {
                    counter <<= 1;
                }
                portValue = (queue << 1) | counter;
                break;
            case 9:
                portValue = rand() % 0x40;
                break;
        }

        prev6 = PORTDbits.RD6;
        prev13 = PORTDbits.RD13;
        __delay32(1000000);
        current6 = PORTDbits.RD6;
        current13 = PORTDbits.RD13;

        if (prev6 == 1 && current6 == 0) {
            ++program;
            if (program > 9) program = 1;
            if (program == 7)
                portValue = 0x07;
            else if (program == 8) {
                portValue = 0x01;
                counter = 0x01;
            } else {
                portValue = 0x00;
                counter = 0x00;
            }
            queue = 0x80;
        }
        if (prev13 == 1 && current13 == 0) {
            --program;
            if (program < 1) program = 9;
            if (program == 7)
                portValue = 0x07;
            else if (program == 8) {
                portValue = 0x01;
                counter = 0x01;
            } else {
                portValue = 0x00;
                counter = 0x00;
            }
            queue = 0x80;
        }
    }

    return 0;
}
