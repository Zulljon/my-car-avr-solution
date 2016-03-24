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
#include "stdint.h"

//-----options-------
#define ADC_used_channels	2			// количество использованых каналов АЦП  1...8


//состояния КА для АЦП
typedef enum {
	ADC_START,		//состояние смены канала и старта преобразования
	ADC_WAIT,		// состояние ожидания конца оброботки
	ADC_END,		// состояние окончания оцифровки
	ADC_DEADTIME	//состояние простоя
} ADC_state;

// -------------- функции------------
void Init_FSM_ADC(void);
void FSM_ADC(void);



#endif /* FSM_ADC_H_ */