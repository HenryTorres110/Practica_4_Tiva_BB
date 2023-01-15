/// By Henry
#include "lib/include.h"
#include <stdio.h>

char *reading_string(char delimiter, int *ptr){
    char letter;
    static char array[50];
    int counter = 0;
    letter = readChar();  
    while (letter != delimiter){
        array[counter] = letter;
        letter = readChar();
        counter ++;
    }
    *ptr = strlen(array);
    return &array[0];
}

char *inverting_name(char *name, int length){
    static char inverted_name[50];
    int counter = 0;
    int idx = 0; 
    for (int i = length; i > 0; i--){
        inverted_name[counter] = *(name + (i -1));
        inverted_name[counter + 1] = idx + '0';
        idx ++; 
        counter = counter + 2;
    }
    inverted_name[counter - 1] = '\n'; 
    return &inverted_name[0];
}


int main(void)
{
    //char ARREGLO[128]; 
    Configurar_PLL(_20MHZ);  //Configuracion de velocidad de reloj
    //Configurar_GPIO();
    //UART_2_CONFIG();
    Configurar_UART0();
    //PWM_CONFIGURATION(0, 0, 10000, 50000000, 50); 
    ADC_CONFIGURATION();
    SEQ_CONFIGURATION_0();
    unsigned int array[10];
    // extern void PWM_CONFIGURATION(int module, int divisor,  int freq, int f_clk, int duty_cycle)
    while (1){
        ADC1 -> PSSI = 0x00000001; //| (1 << 0);
        while ((ADC1 -> RIS & 0x01) == 0){};
        array[0] = ADC1 -> SSFIFO0 & 0xFFF;
        array[1] = ADC1 -> SSFIFO0 & 0xFFF;
        array[2] = ADC1 -> SSFIFO0 & 0xFFF;
        array[3] = ADC1 -> SSFIFO0 & 0xFFF;
        array[4] = ADC1 -> SSFIFO0 & 0xFFF;
        ADC1 -> ISC = 0x0001; // Clearing 0b0001
        //sprintf(ARREGLO, "%u\n", array[1]);
        //printString(ARREGLO);
        if (array[0] < 2040){
            GPIOF -> DATA |= (1 << 1);
            GPIOF -> DATA &= ~(1 << 2); 
        }
        else if (array[0] > 2040){
            GPIOF -> DATA &= ~(1 << 1);
            GPIOF -> DATA |= (1 << 2);  
        }

    } 
}
