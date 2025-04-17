//
//#pragma config POSCMOD = XT            
//#pragma config OSCIOFNC = ON          
//#pragma config FCKSM = CSDCMD         
//#pragma config FNOSC = PRI             
//#pragma config IESO = ON                
//
//#pragma config WDTPS = PS32768        
//#pragma config FWPSA = PR128         
//#pragma config WINDIS = ON            
//#pragma config FWDTEN = ON          
//#pragma config ICS = PGx2           
//#pragma config GWRP = OFF              
//#pragma config GCP = OFF               
//#pragma config JTAGEN = OFF             
//
//
//
//
//
//#include "xc.h"
//#include "libpic30.h"
//#include "adc.h"
//#include "buttons.h"
//
//
//void init(void){
//    ADC_SetConfiguration(ADC_CONFIGURATION_DEFAULT);
//    ADC_ChannelEnable(ADC_CHANNEL_POTENTIOMETER);
//    TRISA = 0x00;
//    TRISD |= (1<<6);
//    
//}
//
//
//int main(void) {
//    init();
//    
//    unsigned long adc_value;
//    unsigned char tryb = 0;
//    unsigned char poprzedni_stan_przycisku = 1;
//    unsigned long opozninie;
//    
//    while(1){
//        adc_value = ADC_Read10bit(ADC_CHANNEL_POTENTIOMETER);
//        if (adc_value == 0xFF){continue;}
//        opozninie = 40000 + (adc_value*4000);
//        
//        unsigned char stan_przycisku = PORTDbits.RD6;
//        
//        if (poprzedni_stan_przycisku==1 && stan_przycisku==0 ){
//            tryb ^= 1;
//            __delay32(40000);
//            
//        }
//        poprzedni_stan_przycisku = stan_przycisku;
//        if (tryb==0) {
//            LATA=0x50;
//            __delay32(opozninie);
//            LATA=0x00;
//            __delay32(opozninie);
//            
//        }
//        else {
//            LATA=0x55;
//            __delay32(opozninie);
//            LATA=0x00;
//            __delay32(opozninie);
//        }
//        
//    }
//    
//    
//    return 0;
//}
//
