/*
 * ADC.h
 *
 *  Created on: 04/11/2019
 *      Author: Henry
 */

#ifndef ADC_ADC_H_
#define ADC_ADC_H_

extern void ADC_CONFIGURATION(void);
extern void SEQ_CONFIGURATION_0(void);
extern void ADC_ISR_SEQ_0(uint32_t data[5]);

#endif /* ADC_ADC_H_ */