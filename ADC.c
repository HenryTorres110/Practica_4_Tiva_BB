#include "lib/include.h"

extern void ADC_CONFIGURATION(void){
    SYSCTL -> RCGCADC = (1 << 0); // Enable Module 0
    SYSCTL -> RCGCADC = (1 << 1); // Enable Module 1

    SYSCTL -> RCGCGPIO = (1 << 1) | (1 << 3) |(1 << 4) | (1 << 5); 
                //        Port B    Port D    Port E      Port F
    // Configuracion de Pines EN DIRECTION REGISTER DIR para que sean outputs (1) o inputs (0)
    GPIOE -> DIR &= ~(1 << 2); // AIN1 PE2
    GPIOE -> DIR &= ~(1 << 5); // AIN8 PE5

    GPIOE -> AFSEL = (1 << 2) | (1 << 5);//0x3F; // E0-E5 AIN0-AIN3, AIN8-AIN9
    GPIOE -> DEN = ~(1 << 2) | ~(1 << 5); //~0x3F;
    GPIOE -> AMSEL = (1 << 2) | (1 << 5); //0x3F; 

    GPIOD -> DIR &= ~(1 << 2); // AIN5 PD2
    GPIOD -> DIR &= ~(1 << 1); // AIN6 PD1
    GPIOD -> DIR &= ~(1 << 0); // AIN7 PD0

    GPIOD -> AFSEL = (1 << 0) | (1 << 1)| (1 << 2);
    GPIOD -> DEN = ~(1 << 0) | ~(1 << 1) | ~(1 << 2); 
    GPIOD -> AMSEL = (1 << 0) | (1 << 1) | (1 << 2);  

    GPIOB -> DIR &= ~(1 << 5); // AIN11 PB5
    GPIOB -> AFSEL =  (1 << 5);
    GPIOB -> DEN =  ~(1 << 5); 
    GPIOB -> AMSEL = (1 << 5); 
    // LED
    GPIOF -> DEN = 0xff; 
    GPIOF -> AFSEL = 0x00; 
    GPIOF -> DIR = 0xff; // Output
    GPIOF -> DATA = (1 << 1); 
} 

extern void SEQ_CONFIGURATION_0(void){
    ADC1 -> SSPRI = (0x0 << 0);
    ADC1 -> ACTSS &= ~(0x0F); 
    ADC1 -> EMUX |= 0x0000;
    ADC1 -> SSMUX0 |= 0x000B8765; 
    ADC1 -> SSCTL0 |= (1 << 17)| (1 << 18); //0x00064444; //0x66666; 
    ADC1 -> PC = 0x7; 
    ADC1 -> IM |= (0xf << 16) | (0xf << 0); 
    ADC1 -> ACTSS |= (1 << 0) | (0 << 1) | (0 << 2) | (0 << 3); 
    ADC1 -> ISC = 1;
    //ADC0 -> ACTSS = ~(1 << 3); 
    //ADC0 -> EMUX &= 0x0000F000; 
    //ADC0 -> SSMUX3 = 1; 
    //ADC0 -> SSCTL3 = 0x6; 
    //ADC0 -> PC = 0x7; 
    //ADC0 -> IM = (1 << 3); 
    //ADC0 -> ACTSS |= (1 << 3); 
    //ADC0 -> ISC = 8; 
}