
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
 

 
#include <xc.h>
#include "buttons.h"
#include "lcd.h"
#include "string.h"

 
void system_init(void){
    LCD_Initialize();
}
 
void display_start_screen(void) {
    const char *message = "   SUPER PROMOCJA!  \xB1\xB2\xB3 LCD HD44780 \xB3\xB2\xB1 TYLKO DZIS!  >> www.wmii.uwm.edu.pl << \xB4\xB5\xB6\xB7\xB8 ZOBACZ TERAZ!   ";
    int len = strlen(message);
    char buffer[17]; 

    for (int i = 0; i <= len - 1; i++) {
        memset(buffer, 0, sizeof(buffer));  
        strncpy(buffer, &message[i], 16);   
        LCD_ClearScreen();                  
        LCD_PutString(buffer, strlen(buffer)); 
        __delay32(1500000); 
    }
}
 
void flashLEDs(){
    AD1PCFG=0xFFFF;
    TRISA=0x0000;
    LATA=0xFFFF;
}
 

void mainMenu(void){
    display_start_screen();
}
 
int main(void) {
    system_init();
    mainMenu();
    return 0;
}
