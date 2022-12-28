#include "lib/include.h"

extern void ADC_CONFIGURATION(void){
    SYSCTL -> RCGCADC = (1 << 0); // Enable Module 1
    //SYSCTL -> RCGCADC = (1 << 0); // Enable Module 0

    SYSCTL -> RCGCGPIO = (1 << 4) | (1 << 5); 
                //       Port E      Port F
    GPIOE -> DIR &= ~(1 << 1);//(0 << 0) & (0 << 1) & (0 << 2) & (0 << 3) & (0 << 4) & (0 << 5);
                //      E0       E1        E2           E3          E4       E5 
    // LED
    GPIOF -> DEN = 0xff; 
    GPIOF -> AFSEL = 0x00; 
    GPIOF -> DIR = 0xff; // Output
    GPIOF -> DATA = (1 << 1); 

    GPIOE -> AFSEL = (1 << 1);//0x3F; // E0-E5 AIN0-AIN3, AIN8-AIN9
    GPIOE -> DEN = ~(1 << 1); //~0x3F;
    GPIOE -> AMSEL = (1 << 1); //0x3F; 
} 

extern void SEQ_CONFIGURATION(void){
    //ADC0 -> ACTSS &= ~0b1001; // Disable seq 0 and 3
    ADC0->ACTSS = (0 << 3); //~0x9;
    // Trigger for sampling
    //ADC0 -> EMUX = (0xF << 0) | (0xF << 12);
    ADC0->EMUX = (0xF << 12); //(0xF << 0) | (0xF << 12); // 0xF to sample continuously 
    
    ADC0->SSMUX3 = 2; // AN2 CHANNEL
    //ADC1 -> SSMUX0 = 0x98321;  // AN1-AN3, AN8-AN9 0b10011000001100100001

    ADC0->SSCTL3 = 0x6; //0b0110;
    ///ADC1 -> SSCTL0 = 0x66666;  // 0b01100110011001100110
    ADC0->PC = 0x7; // 1 Msps

    ADC0->IM = (1 << 3);  //| (1 << 0);

    // Enable Seq
    ADC0->ACTSS |= (1 << 3);//0x9;
    ADC0->ISC = 8; 
}



