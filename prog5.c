
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

#define PLAYER1_BUTTON BUTTON_S3  // RB3
#define PLAYER2_BUTTON BUTTON_S5  // RB5

void init(void) {
    TRISA = 0x0000;
    TRISB |= (1 << 3) | (1 << 4); 
    AD1PCFG = 0xFFFB; 
    ADC_SetConfiguration(ADC_CONFIGURATION_DEFAULT);
    ADC_ChannelEnable(ADC_CHANNEL_POTENTIOMETER);
    LCD_Initialize();
    BUTTON_Enable(PLAYER1_BUTTON);
    BUTTON_Enable(PLAYER2_BUTTON);

}

unsigned int getInitialTimeMinutes() {
    int adc = ADC_Read10bit(ADC_CHANNEL_POTENTIOMETER);  
    if (adc < 341) return 1;
    else if (adc < 682) return 3;
    else return 5;
}

void displayTime(unsigned int t1, unsigned int t2) {
    char buf[17];
    LCD_ClearScreen();
    sprintf(buf, "P1: %02u:%02u", t1 / 60, t1 % 60);
    LCD_PutString(buf, strlen(buf));
    LCD_PutChar('\n');
    sprintf(buf, "P2: %02u:%02u", t2 / 60, t2 % 60);
    LCD_PutString(buf, strlen(buf));
}

void showLoseMessage(int player) {
    LCD_ClearScreen();
    if (player == 1)
        LCD_PutString("P1 PRZEGRAL!", 17);
    else
        LCD_PutString("P2 PRZEGRAL!", 17);
    while(1);  
}

void chessClock() {
    unsigned int time1 = getInitialTimeMinutes() * 60;
    unsigned int time2 = time1;
    int activePlayer = 1;

    displayTime(time1, time2);
    __delay32(1000000);  

    while (1) {
        if (activePlayer == 1) {
            __delay32(1000000);  
            if (BUTTON_IsPressed(PLAYER2_BUTTON)) {
                while (BUTTON_IsPressed(PLAYER2_BUTTON));  
                activePlayer = 2;
            } else {
                if (time1 > 0) time1--;
                else showLoseMessage(1);
            }
        } else {
            __delay32(1000000);
            if (BUTTON_IsPressed(PLAYER1_BUTTON)) {
                while (BUTTON_IsPressed(PLAYER1_BUTTON));
                activePlayer = 1;
            } else {
                if (time2 > 0) time2--;
                else showLoseMessage(2);
            }
        }
        displayTime(time1, time2);
    }
}

int main(void) {
    init();
    chessClock();
    return 0;
}
