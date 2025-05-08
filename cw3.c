
 
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
 
 
unsigned char is_alarm_goes_off(unsigned int adc_value) {
    if (adc_value < 500) return 0;
    else return 4;
}
 
unsigned long get_delay_from_level(unsigned char level) {
    const unsigned long delays[] = {250000, 500000, 750000, 1000000, 1250000};
    return delays[level];
}
 
void init(void) {
    TRISA = 0x0000;
    TRISB |= (1 << 3) | (1 << 4); 
    AD1PCFG = 0xFFFB; 
    ADC_SetConfiguration(ADC_CONFIGURATION_DEFAULT);
    ADC_ChannelEnable(ADC_CHANNEL_POTENTIOMETER);
}
 
int main(void) {
    uint8_t portValue = 0x00;
    uint8_t counter = 0x01;
    uint8_t queue = 0x80;
    int left = 1;
    char program = 7;
 
    char current6 = 0, prev6 = 0;
    char current13 = 0, prev13 = 0;

    srand(1110011);
 
    init();
 
    portValue = 0x00;
 
    while (1) {
        unsigned int adc_val = ADC_Read10bit(ADC_CHANNEL_POTENTIOMETER);
        unsigned char speed_level = is_alarm_goes_off(adc_val);
        unsigned long delay = get_delay_from_level(speed_level);
 
        switch (program) {
            case 7:
                if (speed_level == 0) {
                    

                    portValue = 0x00;
                    __delay32(3000000);
                    portValue = 0x01;
                     __delay32(3000000);
                    portValue = 0xFF;
                    
                    break;
                }
                else {
                    portValue = 0x00;
                    break;
                }
                break;
            case 8:
                portValue = 0x00;
                break;
        }
 
        LATA = portValue;
 
        prev6 = PORTDbits.RD6;
        prev13 = PORTDbits.RD13;
        __delay32(delay);
        current6 = PORTDbits.RD6;
        current13 = PORTDbits.RD13;
        if (prev6 == 1 && current6 == 0) {
            ++program;
            if (program > 8) program = 7;
            if (program == 7)
                portValue = 0x07;
            else if (program == 8) {
                portValue = 0x01;
                counter = 0x01;
            }
        }
        if (prev13 == 1 && current13 == 0) {
            --program;
            if (program < 7) program = 8;
            if (program == 7)
                portValue = 0x07;
            else if (program == 8) {
                portValue = 0x01;
                counter = 0x01;
            }
        }
    }
 
    return 0;
}