/// By Henry
#include "lib/include.h"
#include <stdio.h>
uint32_t adc_valor[5];

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
        ADC_ISR_SEQ_0(adc_valor);
    } 
}
