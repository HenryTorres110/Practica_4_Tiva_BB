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
    //Experimento 1
/*Usando el modulo 0 de PWM con una frecuencia de reloj del sistema de 50,000,000 Hz
 * junto con el generador 1  habilitar alguno de los pwm's asociados y obtener un PWM
 * cuya frecuencia sea de 10KHz
 */
//Experimento 2
/*Usando el modulo 0 de PWM con una frecuencia de reloj del sistema de 20,000,000 Hz
 * junto con el generador 0,1,2  habilitar alguno de los pwm's asociados y obtener un PWM
 * cuya frecuencia sea de 50Hz con tres potenciometros variar el ciclo de trabajo
 * para controlar la posicion de tres servos sg90 o otros.
 *
 */
//Experimento 3
/*Usando el modulo 0 de PWM con una frecuencia de reloj del sistema de 20,000,000 Hz
 * junto con el generador 0,1,2  habilitar alguno de los pwm's asociados y obtener un PWM
 * cuya frecuencia sea de 50Hz , utilizando el uart de la practica 3
 * se enviara dato desde interfaz de simulink para controlar la intensidad luminosa 
 * usando un led RGB externa 
 *
 */
    uint32_t data[5];
    int duty_cycle = 85;
    int f_clk = 20000000;
    int freq = 50;
    int divisor = 64;
    int module = 0;
    int servo = 1; // 1 for servo-mode and 0 for normal mode
    
    uint32_t CUENTAS_0;
    uint32_t CUENTAS_1;
    uint32_t CUENTAS_2; 
    Configurar_PLL(_20MHZ);  //Configuracion de velocidad de reloj
    //Configurar_GPIO();
    //UART_2_CONFIG(); // Puerto D
    //ADC_CONFIGURATION_PORT_D(); // PUERTO D PINES D0, D1, D2
    ADC_CONFIGURATION_PORT_E(); // PUERTO E PINES E1, E2, E5
    SEQ_CONFIGURATION_0();
    PWM_CONFIGURATION(module, divisor, freq, f_clk, duty_cycle); // Puerto B pines B4 y B7
    f_clk = f_clk / divisor;
    //PWM_CONFIGURATION(int module, int divisor, int freq, int f_clk, int duty_cycle)
    
    while (1){
        // Lectura de varios canales
        ADC_ISR_SEQ_0(data);
        if (servo == 0){
            CUENTAS_0 = (uint32_t)((1.0 - (data[0] / 4095.0)) *(f_clk / freq));
            CUENTAS_1 = (uint32_t)((1.0 - (data[1] / 4095.0)) *(f_clk / freq));
            //CUENTAS_2 = (uint32_t)((1.0 - (data[2] / 4095.0)) *(f_clk / freq));
        }
        else{
            CUENTAS_0 = (uint32_t)(((1.0 - (5.0 / 100.0)) *(f_clk / freq)) - (data[0] / 4095.0) * 312);
            CUENTAS_1 = (uint32_t)(((1.0 - (5.0 / 100.0)) *(f_clk / freq)) - (data[1] / 4095.0) * 312);
            //CUENTAS_2 = (uint32_t)(((1.0 - (5.0 / 100.0)) *(f_clk / freq)) - (data[2] / 4095.0) * 312);
        }
        PWM0->_0_CMPB = CUENTAS_0;
        PWM0->_1_CMPA = CUENTAS_1;
        //PWM0->_2_CMPA = CUENTAS_2;
    } 
}


