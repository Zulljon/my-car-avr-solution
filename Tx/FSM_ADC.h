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
#define ADC_used_channels	2			// ���������� ������������� ������� ���  1...8


//��������� �� ��� ���
typedef enum {
	ADC_START,		//��������� ����� ������ � ������ ��������������
	ADC_WAIT,		// ��������� �������� ����� ���������
	ADC_END,		// ��������� ��������� ���������
	ADC_DEADTIME	//��������� �������
} ADC_state;

// -------------- �������------------
void Init_FSM_ADC(void);
void FSM_ADC(void);



#endif /* FSM_ADC_H_ */