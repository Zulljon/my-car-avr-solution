/*
 * FSM_ADC.c
 *
 * Created: 10.03.2016 13:49:15
 *  Author: Dan
 */ 

#include "FSM_ADC.h"
//uint8_t fsm_adc_state;							// ��������� ��
uint8_t adc_buffer_result[ADC_used_channels];		// �������� ������ ����������� ���
static struct  {
	uint8_t ON:1;
	uint8_t state:5;		// ��������� ��
	uint8_t current_channel:3;
}_adc;
//static ADC_state state =
//uint8_t adc_channel_proccesing;

void FSM_ADC(void){
	
	switch (_adc.state){
		case ADC_DEADTIME ://��������� �������
			if (!_adc.ON){		break;		} 
			else{
				_adc.state = ADC_START;
				}
		break;
		case ADC_START :
			ADSC;
		//��������� ��������� ������
		break;
		case ADC_WAIT :
		//���� ��������� ��������� � ���� � ADC_END
		break;
		case ADC_END :
		//����� � ����� ���������, ������������ � ADC_START
		break;
		case 4 :
		break;
		case 5 :
		break;
	}
	
}