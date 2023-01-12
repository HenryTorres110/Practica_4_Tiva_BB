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
    
    Configurar_PLL(_20MHZ);  //Configuracion de velocidad de reloj
    Configurar_GPIO();
    UART_2_CONFIG();
    //PWM_CONFIGURATION(0, 0, 10000, 50000000, 50); 
    ADC_CONFIGURATION();
    SEQ_CONFIGURATION_0();
    unsigned int array[10];
    // extern void PWM_CONFIGURATION(int module, int divisor,  int freq, int f_clk, int duty_cycle)
    while (1){
        ADC1 -> PSSI |= (1 << 0); //| (1 << 0);
        while ((ADC1 -> RIS & 0x0001) == 0);
        array[1] = ADC1 -> SSFIFO0;
        array[2] = ADC1 -> SSFIFO0;
        array[3] = ADC1 -> SSFIFO0;
        array[4] = ADC1 -> SSFIFO0;
        array[5] = ADC1 -> SSFIFO0;
        ADC1 -> ISC = 0x0001; // Clearing 0b0001
        if (array[1] < 2040){
            GPIOF -> DATA |= (1 << 1);
            GPIOF -> DATA &= ~(1 << 2); 
        }
        else if (array[1] > 2040){
            GPIOF -> DATA &= ~(1 << 1);
            GPIOF -> DATA |= (1 << 2);  
        }

    } 
}
