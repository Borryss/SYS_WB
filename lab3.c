

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




int main(void) {
    
    unsigned portValue = 0x01;
    char aktualny6 = 0, poprzedni6 = 0, aktualny7 = 0, poprzedni7 = 0;
    
    
    TRISA = 0x00;
    TRISD = 0xFF;
    
    int value  = 1;
    
    while(1){
        switch(value){
            case 1:
                LATA = portValue;
                break;
            case 2:
                LATA = portValue +1;
                break;
            case 3:
                LATA = portValue +11;
                break;
            default :
                LATA = portValue;
                
                
        }
        
        poprzedni6 = PORTDbits.RD6;
        poprzedni7 = PORTDbits.RD7;
        __delay32(150000);
        aktualny6 = PORTDbits.RD6;
        aktualny7 = PORTDbits.RD7;
        
        if (aktualny6 - poprzedni6 == 1){
            value --;
            portValue = 1;
            if (value<=0){
                value = 3;
            }
        }
        if(aktualny7-poprzedni7 == 1){
            value ++;
            portValue = 1;
            if (value>=4){
                value = 1;
            }
        }
    }
    
    
    
    
    return 0;
}
