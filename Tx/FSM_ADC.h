/*
 * FSM_ADC.h
 *
 * Created: 10.03.2016 13:49:55
 *  Author: Dan
 */ 


#ifndef FSM_ADC_H_
#define FSM_ADC_H_


#define F_CPU 16000000
#define FOSC 16000000 // Clock Speed

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


void FSM_ADC(void);



#endif /* FSM_ADC_H_ */