/*
 * File:   newmainXC16.c
 * Author: local
 *
 * Created on April 10, 2025, 11:58 AM
 */


// PIC24FJ128GA010 Configuration Bit Settings

// 'C' source line config statements

// CONFIG2
//#pragma config POSCMOD = XT             // Primary Oscillator Select (XT Oscillator mode selected)
//#pragma config OSCIOFNC = ON            // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as port I/O (RC15))
//#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
//#pragma config FNOSC = PRI              // Oscillator Select (Primary Oscillator (XT, HS, EC))
//#pragma config IESO = ON                // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) enabled)
//
//// CONFIG1
//#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32,768)
//#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
//#pragma config WINDIS = ON              // Watchdog Timer Window (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
//#pragma config FWDTEN = ON              // Watchdog Timer Enable (Watchdog Timer is enabled)
//#pragma config ICS = PGx2               // Comm Channel Select (Emulator/debugger uses EMUC2/EMUD2)
//#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
//#pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
//#pragma config JTAGEN = OFF            // JTAG Port Enable (JTAG port is disabled)
//
//// #pragma config statements should precede project file includes.
//// Use project enums instead of #define for ON and OFF.
//
//
//#include "xc.h"
//#include "libpic30.h"
//
//int main(void) {
//    
//    unsigned char portValue;
//    
//    AD1PCFG = 0xFFFF;
//    TRISA = 0x0000;
//    LATA = portValue;
//    
//    while(1){
//        portValue = 0x01;
//        LATA = portValue;
//        __delay32(2000000);
//        portValue = 0x02;
//        LATA = portValue;
//        __delay32(2000000);
//        
//    }
//    
//    
//    
//    return -1;
//    
//}


#include <xc.h>
#include <stdint.h>
#include <libpic30.h>

// Konfiguracje
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

#define _XTAL_FREQ 8000000UL  // XTAL frequency

#define NEXT_BUTTON PORTDbits.RD6
#define PREV_BUTTON PORTDbits.RD13

uint8_t currentProgram = 1;
uint8_t counter = 0;

// Funkcja do debouncingu przycisków
void debounce() {
    __delay32(1000000);  // proste opó?nienie (200ms)
}

void switchProgram() {
    if (!NEXT_BUTTON) {
        debounce();
        currentProgram++;
        if (currentProgram > 9) currentProgram = 1;
    }
    if (!PREV_BUTTON) {
        debounce();
        if (currentProgram == 1) currentProgram = 9;
        else currentProgram--;
    }
}

void binaryCounterUp() {
    LATB = counter++;
    __delay32(1000000);
}

void binaryCounterDown() {
    LATB = counter--;
    __delay32(1000000);
}

uint8_t grayEncode(uint8_t num) {
    return num ^ (num >> 1);
}

void grayCounterUp() {
    LATB = grayEncode(counter++);
    __delay32(1000000);
}

void grayCounterDown() {
    LATB = grayEncode(counter--);
    __delay32(1000000);
}

void bcdCounterUp() {
    static uint8_t tens = 0, ones = 0;
    ones++;
    if (ones > 9) {
        ones = 0;
        tens++;
    }
    if (tens > 9) {
        tens = 0;
    }
    LATB = (tens << 4) | ones;
    __delay32(1000000);
}

void bcdCounterDown() {
    static uint8_t tens = 9, ones = 9;
    if (ones == 0) {
        if (tens > 0) {
            ones = 9;
            tens--;
        }
    } else {
        ones--;
    }
    LATB = (tens << 4) | ones;
    __delay32(1000000);
}

void snake() {
    static uint8_t pos = 0b00000111;
    static int direction = 1;
    LATB = pos;
    __delay32(1000000);
    if (direction) {
        pos <<= 1;
        if (pos & 0b11100000) direction = 0;
    } else {
        pos >>= 1;
        if (pos & 0b00000111) direction = 1;
    }
}

void queueEffect() {
    static uint8_t pattern = 0b00000001;
    LATB = pattern;
    __delay32(1000000);
    pattern <<= 1;
    if (pattern == 0) pattern = 0b00000001;
}

void lfsrRandom() {
    static uint8_t lfsr = 0b1110011;
    LATB = lfsr;
    __delay32(1000000);
    uint8_t bit = ((lfsr >> 6) ^ (lfsr >> 5)) & 1; // XOR bitów 6 i 5
    lfsr = (lfsr << 1) | bit;
}

int main(void) {
    TRISD |= (1 << 6) | (1 << 13); // RD6, RD13 jako wej?cia
    TRISB = 0x00; // ca?y port B jako wyj?cie
    LATB = 0x00;

    while (1) {
        switchProgram();

        switch (currentProgram) {
            case 1: binaryCounterUp(); break;
            case 2: binaryCounterDown(); break;
            case 3: grayCounterUp(); break;
            case 4: grayCounterDown(); break;
            case 5: bcdCounterUp(); break;
            case 6: bcdCounterDown(); break;
            case 7: snake(); break;
            case 8: queueEffect(); break;
            case 9: lfsrRandom(); break;
        }
    }
}
