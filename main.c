/// By Henry
#include "lib/include.h"
#include <stdio.h>
uint32_t adc_valor[5];
uint32_t adc_seq_3[5];

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


extern void integer_to_char(uint32_t number)
{
    char number_in_string[5];
    int i = 3;
    int j = 0; 
    int n_digit;  
    while (i >= 0){
        n_digit = (int)number / (int)(pow(10, i));
        number_in_string[j] = n_digit + '0';
        number = number - (n_digit * pow(10, i)); 
        i = i - 1; 
        j++;
    }
    number_in_string[4] = '\n';
    printString(number_in_string);
}


int main(void)
{
    uint32_t lectura_canal_1;
    uint32_t lectura_canal_2;
    uint32_t lectura_canal_3;
    int prueba_2 = 10;
    char data_str[128];
    //char ARREGLO[128]; 
    Configurar_PLL(_40MHZ);  //Configuracion de velocidad de reloj
    //Configurar_GPIO();
    UART_2_CONFIG(); // Funciona en el Puerto D
    //Configurar_UART0();
    //PWM_CONFIGURATION(0, 0, 10000, 50000000, 50); 
    ADC_CONFIGURATION();
    //SEQ_CONFIGURATION_3();
    SEQ_CONFIGURATION_0();
    while (1){
        //ADC_ISR_SEQ_3(adc_seq_3);
        ADC_ISR_SEQ_0(adc_valor);
        lectura_canal_1 = (uint32_t)(adc_valor[0]);
        lectura_canal_2 = (uint32_t)(adc_valor[1]);
        lectura_canal_3 = (uint32_t)(adc_valor[2]);
        integer_to_char(lectura_canal_1);
        integer_to_char(lectura_canal_2);
        integer_to_char(lectura_canal_3);
    }
}
