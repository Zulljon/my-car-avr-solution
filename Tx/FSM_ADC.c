/*
 * FSM_ADC.c
 *
 * Created: 10.03.2016 13:49:15
 *  Author: Dan
 */ 


//unsigned char fsm_adc_state;							// состояние КА
unsigned char adc_buffer_result[ADC_used_channels];		// выходной массив результатов ацп
static struct  {
	unsigned char ON:1;
	unsigned char state:5;		// состояние КА
	unsigned char current_channel:3;
}_adc;
//static ADC_state state =
//unsigned char adc_channel_proccesing;

void FSM_ADC(void){
	
	switch (_adc.state){
		case ADC_DEADTIME ://состояние простоя
			if (!_adc.ON){		break;		} 
			else{
				_adc.state = ADC_START;
				}
		break;
		case ADC_START :
			ADSC
		//запускаем оцифровку канала
		break;
		case ADC_WAIT :
		//ждем окончания оцифровки и идем в ADC_END
		break;
		case ADC_END :
		//пишем в выход результат, возвращаемся в ADC_START
		break;
		case 4 :
		break;
		case 5 :
		break;
	}
	
}