/// By Henry
#include "lib/include.h"

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
    
    //Configurar_PLL(_50MHZ);  //Configuracion de velocidad de reloj
    //Configurar_GPIO();
    //UART_2_CONFIG();
    //PWM_CONFIGURATION(0, 0, 10000, 50000000, 50); 
    ADC_CONFIGURATION();
    SEQ_CONFIGURATION();
    unsigned int adc_read;   
    // extern void PWM_CONFIGURATION(int module, int divisor,  int freq, int f_clk, int duty_cycle)
    while (1){
        ADC0 -> PSSI |= (1 << 3); //| (1 << 0);
        while ((ADC0 -> RIS & 8) == 0);
        adc_read = ADC0 -> SSFIFO3;
        ADC0 -> ISC = 8; // Clearing 0b1000
        if (adc_read >= 2048){
            GPIOF -> DATA |= (1 << 1); 
        }
        else if (adc_read < 2048){
            GPIOF -> DATA &= ~(1 << 1); 
        }
    } 
}
