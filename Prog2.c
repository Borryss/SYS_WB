// PIC24FJ128GA010 Configuration Bit Settings
// 'C' source line config statements
 
#pragma config POSCMOD = XT             // Primary Oscillator Select (XT Oscillator mode selected)
 
#pragma config OSCIOFNC = ON            // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as port I/O (RC15))
 
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
 
#pragma config FNOSC = PRI              // Oscillator Select (Primary Oscillator (XT, HS, EC))
 
#pragma config IESO = ON                // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) enabled)
 
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32,768)
 
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
 
#pragma config WINDIS = ON              // Watchdog Timer Window (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
 
#pragma config FWDTEN = ON              // Watchdog Timer Enable (Watchdog Timer is enabled)
 
#pragma config ICS = PGx2               // Comm Channel Select (Emulator/debugger uses EMUC2/EMUD2)
 
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
 
#pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
 
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG port is disabled)

// #pragma config statements should precede project file includes.
 
// Use project enums instead of #define for ON and OFF.

 
#include "xc.h"
#include "libpic30.h"
#include "adc.h"
#include "buttons.h"
 
 
unsigned char read_speed_level(unsigned int adc_value) {
    if (adc_value < 200) return 0;
    else if (adc_value < 400) return 1;
    else if (adc_value < 600) return 2;
    else if (adc_value < 800) return 3;
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
 
    portValue = 0x07;
 
    while (1) {
        unsigned int adc_val = ADC_Read10bit(ADC_CHANNEL_POTENTIOMETER);
        unsigned char speed_level = read_speed_level(adc_val);
        unsigned long delay = get_delay_from_level(speed_level);
 
        switch (program) {
            case 7:
                if (portValue & 0x80) left = 0;
                if (portValue & 0x01) left = 1;
                if (left)
                    portValue = portValue << 1;
                else
                    portValue = portValue >> 1;
                break;
        
            case 8:
                portValue = rand() % 0x40;
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