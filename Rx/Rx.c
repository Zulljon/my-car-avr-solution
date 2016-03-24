/*
 * Rx.c
 *
 * Created: 24.02.2016 17:56:44
 *  Author: Dan
 */ 

//E:\Micro_Cirquit\projects\avr
//#include "E:\Micro_Cirquit\projects\avr\MY CAR (bt+avr+pc)\MY CAR (avr solution)\defines.h"
//#include "E:\Micro_Cirquit\projects\avr\MY CAR (bt+avr+pc)\MY CAR (avr solution)\uart_functions.c"

#include "Rx.h"

struct {
	struct {
		//���� �������� 60 �������� � ���
		uint8_t on_off:1;
		//������� ���
		uint8_t brightness:5;
		} headlights;// ����� ��� �������� ���������� ��� ���

	struct {
		//���/����
		uint8_t on_green:1;
		uint8_t on_blue:1;
		//�������
		uint8_t brightness_green:4;
		uint8_t brightness_blue:4;
		} neon_buffer;// ����� ��� �������� ���������� ���������

	struct {
		//������ ����
		uint8_t on_off:1;
		}parking_lights;

} LED;// ����� ��� �������� ���������� ��� ��������� � ������������

struct {
	uint8_t servoo	:1;
	uint8_t motorr	:1;
	uint8_t top_value:3;
	uint8_t prescaller:2;
	uint8_t leds	:1;
	uint8_t set_servo__left:1;
	uint8_t set_servo__rigft:1;
} init_variables_state;// ��������� ������ ��� ������ ������� ���� ����


volatile union {
	//�������� ����������
	uint8_t word;
	
	//------�e���������------//
	struct {
		uint8_t angle:5;
		//uint8_t turn_side:1;
		//uint8_t needs_turn:1;
		uint8_t assignation:3;
	} servo;
	
	//------���������------//
	struct {
		uint8_t speed			:4;
		uint8_t spin_rotation	:1;
		uint8_t assignation	:3;
	} motor;
	
	//------����������------//
	//����
	struct {
		uint8_t p_w_m:5;
		//uint8_t on_off:1;
		uint8_t assignation:3;
	} headlight;
	
	//-���������--
	struct {
		uint8_t pwm			:4; // ��� ����� 0b0000 ��������� ����� 1 ��� 0
		uint8_t color			:1; //����� ����� ��� ��������� ���, 1-��� 0-���.
		uint8_t assignation	:3;
	} neon;
	
	// ������ ����
	struct {
		uint8_t :4;
		uint8_t on_off:1;
		uint8_t assignation:3;
	} parking_lights;
	
	//��������� ������� ���� ���������
	struct {
		uint8_t top_value:3;
		uint8_t prescaller:2;
		uint8_t assignation:3;
		} motor_freq;
	
	// ��������� �������� ������/������� ��������� �����
	struct {
		uint8_t values:5;
		uint8_t assignation:3;
		} set_servo__left;
	
	struct {
		uint8_t values:5;
		uint8_t assignation:3;
		} set_servo__right;
		
} inbound_processing ;


uint8_t pwm_speed, timer0_top_value;// ���������� �� ���������� ��������� (��� ����)
int16_t servo_turn;
int32_t leftmost,rightmost;
uint16_t a;
/*
#define N_OF_TIKS 7
int8_t n=0;
int8_t randoms[N_OF_TIKS];
*/
// ������ - 16-bit Timer/Counter1 with PWM
// �������� ������� 8
// Fast PWM Mode

uint16_t	timer1_top_value,
				servo_min_angle,
				servo_max_angle;
int32_t			servo_temp;			

//-------------------------------------------------------//

void init_variables_main(void){
	init_variables_state.servoo = 1;
	init_variables_state.motorr = 1;
	init_variables_state.prescaller = 3;
	init_variables_state.leds = 0x0;
	init_variables_state.set_servo__left = 0x0;
	init_variables_state.set_servo__rigft = 0x0;
	leftmost = 0.001;
	rightmost = 0.002;
	//randoms[0] = 51;
	
	//OCR1AH = (uint8_t)(3000>>8);
	//OCR1AL = (uint8_t)3000;	
}

int32_t set_servo_math(int8_t a){
	int32_t b;
	b = (int32_t)((a/32)*0.0005);
	return b;
}

void init_variables(void){
	
	if (init_variables_state.servoo){
		timer1_top_value = (uint16_t)( F_CPU / (8 * 50 ) ) ; //8 �������� ������� F_CPU � �������/����� 16 ������, 50 �������� ������� ����
		ICR1H = (uint8_t)(timer1_top_value>>8);
		ICR1L = (uint8_t)timer1_top_value;
		servo_min_angle = (uint16_t)( (timer1_top_value * leftmost) / 0.02) ; //leftmost >= 0.001
		servo_max_angle = (uint16_t)( (timer1_top_value * rightmost) / 0.02) ; //rightmost <= 0.002
		servo_temp  = (servo_max_angle - servo_min_angle) / (32);
		// ��������� ���������� ��� ����� ������� 
		// � ������� ��������� � EEPROM ����� ����������� servo_temp
		init_variables_state.servoo = 0x0;
		
		//USART_Transmit(	(uint8_t)(timer1_top_value>>8)	);
		//USART_Transmit(	(uint8_t)timer1_top_value	);
		//USART_Transmit(	ICR1H	);
		//USART_Transmit(	ICR1L	);
	}
	if (init_variables_state.motorr){
		timer0_top_value = (uint8_t)((0xFF)*(init_variables_state.top_value/8));
		OCR0B = timer0_top_value ;
		// �������� � �������� ������� �������� ���� ��� ��������� � OCR0A
		switch(init_variables_state.prescaller){
			case 0 :	//8
				TCCR0B = (0<<CS02)|(1<<CS01)|(0<<CS00);
				break;
			case 1 :	//64
				TCCR0B = (0<<CS02)|(1<<CS01)|(1<<CS00);
				break;
			case 2 :	//256
				TCCR0B = (1<<CS02)|(0<<CS01)|(0<<CS00);
				break;
			case 3 :	//1024
				TCCR0B = (1<<CS02)|(0<<CS01)|(1<<CS00);
				break;
		}
		init_variables_state.motorr = 0x0 ;
	}

	if (init_variables_state.set_servo__left){
		leftmost = (int32_t)(0.0015 - set_servo_math(inbound_processing.set_servo__left.values));
		init_variables_state.set_servo__left = 0x0;
	}
	if (init_variables_state.set_servo__rigft){
		rightmost = (int32_t)(0.0015 + set_servo_math(inbound_processing.set_servo__right.values));
		init_variables_state.set_servo__rigft = 0x0;
	}

}

uint8_t PWM_speed_math(uint8_t pwm_speeeds){
	uint8_t pwm_a = (uint8_t)((timer0_top_value)*(pwm_speeeds/16));
	//USART_Transmit(pwm_a);
	return pwm_a;
}

uint16_t servo_angle(uint8_t r){
	int16_t a = (uint16_t)(servo_min_angle + r * servo_temp);
	return a;
}

// ������� ��������� ������� ���������
uint8_t processing( uint8_t resive_word ){
	inbound_processing.word = resive_word;
	//PORTB=(1<<PORTB5);
	switch (inbound_processing.motor.assignation){
		case MOTORchik:
		if (inbound_processing.motor.speed == 0){
			TCCR0A |= (1<<COM0B1)|(1<<COM0B0);	// �������� ���� OC0B
			//PORTD |= 1<<PORTD2;// ����� ���������� ����� �� ������� ��������� ������� ����� ������ �����!!!
			} 
		else {
			pwm_speed = PWM_speed_math(inbound_processing.motor.speed);			//	�������� � ��� ���� �� ... ���������!!!
			OCR0B = pwm_speed;
			if (inbound_processing.motor.spin_rotation){PORTB |= (1<<P_MOTOR_SIDE);} else {PORTB &= ~(1<<P_MOTOR_SIDE);} // �������� ���� � �������!!!
			TCCR0A |= (1<<COM0B1)|(1<<COM0B0);	// ������� ���� OC0B
			}
		//USART_Transmit(timer0_top_value);
		
		break;
		
		case SERVO:
			//if (inbound_processing.servo.needs_turn){// �������� �������� � ������������ ����������, ����������� ����� � if � else �������
			servo_turn = servo_angle(inbound_processing.servo.angle); 
			OCR1AH = (uint8_t)(servo_turn>>8);//8>>servo_turn //servo_turn>>8
			OCR1AL = (uint8_t)servo_turn;		// ���������� � 16 ������ ��� servo_turn  (������ �������� � ������)
				
			//USART_Transmit(servo_turn);		
			//}

		break;
		
		case LED_HEADLIGHTS:
			if (inbound_processing.headlight.p_w_m == 0b00000){
				LED.headlights.on_off = 0b0;
				}else{
				LED.headlights.on_off	=	0b1; // �������� ����
				LED.headlights.brightness = inbound_processing.headlight.p_w_m; 
			}
			// ��������� ������� ���
			// ��������� ������1 OC1B
			//� ����c������ ���� inbound_processing.front_leds.p_w_m
			init_variables_state.leds = 0x1;
		break;
			
		case NEON:
			if (inbound_processing.neon.pwm == 0b0000){
				if (inbound_processing.neon.color){
					LED.neon_buffer.on_green = 0b0;
				}else{
					LED.neon_buffer.on_blue = 0b0;}
			} else {
				if (inbound_processing.neon.color){
					LED.neon_buffer.brightness_green = inbound_processing.neon.pwm;
					}else{
				LED.neon_buffer.brightness_blue = inbound_processing.neon.pwm;}
			}
			
			init_variables_state.leds = 0x1;
		break;
		
		case LEDS_PS:
			LED.parking_lights.on_off	=	inbound_processing.parking_lights.on_off;
			init_variables_state.leds = 0x1;
		break;
		
		case SET_MOTOR_FREQ:
			init_variables_state.prescaller = inbound_processing.motor_freq.prescaller ;
			init_variables_state.top_value = inbound_processing.motor_freq.top_value ;
			init_variables_state.motorr = 0x1;
		break;
		
		case SET_SERVO_RIGHT:
			init_variables_state.set_servo__rigft = 0x1;		
		break;
		case SET_SERVO_LEFT:
			init_variables_state.set_servo__left = 0x1;		
		break;	
	}
	return 0;
}

/*
uint8_t buffer_receive;

uint8_t buffer_receive[BUFFER_MAX];
uint8_t last_word_in_buffer = 0;

uint8_t buffer_RX( uint8_t a){
	if ( last_word_in_buffer < (BUFFER_MAX-1) ){
		++last_word_in_buffer;
	} else {	last_word_in_buffer = 0;	}
	buffer_receive[last_word_in_buffer] = a ;
	return buffer_receive[last_word_in_buffer];
}
*/

void LEDs_manipulations(void){
		
	if (init_variables_state.leds){
		
		if (!LED.neon_buffer.on_green){
			//��������� OC2A �� �������;	
			}else {
			//�������� OC2A
			//�������� OC2A = LED.neon_buffer.brightness_green
			}
			
		if (!LED.neon_buffer.on_blue){
			//��������� OC2B �� �������;
			}else {
			//�������� OC2B
			//�������� OC2B = LED.neon_buffer.brightness_blue
		}
			
		if (LED.parking_lights.on_off)	{	P_PARKING_LIGHT_1 ;	}	else { P_PARKING_LIGHT_0; }
			
		if (LED.headlights.on_off)	{
			// ������ ���� 
			//a = (uint16_t) ((LED.headlights.brightness/32)*65536);
			a = (uint16_t) (LED.headlights.brightness*2048);
			// ���������� ���������� � � ������1 	
			OCR1BH = (uint8_t)(a>>8);
			OCR1BL = (uint8_t)a;
		}else{
			OCR1BH = (uint8_t)(3>>8);
			OCR1BL = (uint8_t)3;
		}
		
				
		init_variables_state.leds = 0x0;
	}
	
}
/*
uint16_t user_counter_1; 

struct {
	uint8_t compare_match_1:1;
	uint8_t compare_match_2:1;
	uint8_t compare_match_3:1;
} user_counter_flags ;


uint16_t counter_on_TCNT1(){
	++user_counter_1;//����������� ����������
	if (user_counter_1 = 255){	user_counter_1 = 0x0;	}//�������� ���������� ��� ���������� ���������
	return 0;
}

void contact_bounce( uint8_t PORTx, uint8_t port ){
	if ( user_counter_1 == randoms[n] ){
		PORTx ^=1<<port; //�������� ��������� "�����"
	}
	++n;
	
}

uint16_t made_randoms_N(){
	int8_t i;
	for (i=0;i<N_OF_TIKS;++i){
		randoms[i+1] = (uint8_t)fmod(((randoms[i]*27)+3),128);
	}
	return 0;
}
*/

void init_pwm_2 (void){ //������ ��� ���������
	TCCR2A = (0<<COM2A1)|(0<<COM2A0)|(0<<COM2B1)|(0<<COM2B0)|(0<<WGM21)|(0<<WGM20);
	TCCR2B = (0<<FOC2A)|(0<<FOC2B)|(0<<WGM22)|(1<<CS22)|(1<<CS21)|(1<<CS20);
	TIMSK2 = (0<<OCIE2B)|(0<<OCIE2A)|(0<<TOIE2);
	TIFR2 =	(0<<OCF2B)|(1<<OCF2A)|(1<<TOV2);
	ASSR = (1<<EXCLK)|(1<<AS2)|(0<<TCN2UB)|(0<<OCR2AUB)|(0<<OCR2BUB)|(0<<TCR2AUB)|(0<<TCR2BUB);
	GTCCR = (0<<TSM)|(0<<PSRASY)|(0<<PSRSYNC);
	OCR2A = 128;
	OCR2B = 128;
}


void init_pwm_1 (void){
	TCCR1A = (1<<COM1A1)|(0<<COM1A0)|(0<<COM1B1)|(0<<COM1B0)|(1<<WGM11)|(0<<WGM10);
	TCCR1B = (0<<ICNC1)|(0<<ICES1)|(1<<WGM13)|(1<<WGM12)|(0<<CS12)|(1<<CS11)|(0<<CS10);
	TCCR1C = (0<<FOC1A)|(0<<FOC1B);
	TIMSK1 = (0<<ICIE1)|(0<<OCIE1B)|(0<<OCIE1A)|(0<<TOIE1);
	TIFR1 = (0<<ICF1)|(0<<OCF1B)|(0<<OCF1A)|(0<<TOV1);
	//TCNT1H and TCNT1L and OCR1AH and OCR1AL and OCR1BH and OCR1BL and ICR1H and ICR1L
	OCR1AH = (uint8_t)(3000>>8);	// ��������� ��������
	OCR1AL = (uint8_t)3000;		// ��� ���������
	OCR1BH = (uint8_t)(10>>8);	// ��������� ��������
	OCR1BL = (uint8_t)10;		// ��� ���������
	
}

void init_pwm_0 (void){
	TCCR0A = (1<<COM0A1)|(1<<COM0A0)|(1<<COM0B1)|(1<<COM0B0)|(1<<WGM01)|(1<<WGM00);
	TCCR0B = (0<<FOC0A)|(0<<FOC0B)|(1<<WGM02)|(0<<CS02)|(1<<CS01)|(0<<CS00);
	TIMSK0 = (0<<OCIE0B)|(0<<OCIE0A)|(0<<TOIE0);
	//TIFR0 = (0<<OCF0B)|(0<<OCF0A)|(0<<TOV0);
	//TCNT0 OCR0A OCR0B
}

ISR(USART_RX_vect){
	//buffer_RX(UDR0);
	//processing(buffer_RX(UDR0));
	//buffer_receive = UDR0;
	//PORTB = UDR0 ;
	processing(UDR0);
}

ISR(TIMER1_OVF_vect){ //TOIE1
	//counter_on_TCNT1();
	//contact_bounce(PORTB,PORTB5);
	//made_randoms_N();
}

void init_I_O (void){
	PORTB=(0<<PORTB0)|(0<<PORTB1)|(0<<PORTB2)|(0<<PORTB3)|(0<<PORTB4)|(0<<PORTB5);
	DDRB= (1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB3)|(1<<DDB4)|(1<<DDB5);
	/*
	PORTC=(0<<PORTC0)|(0<<PORTC0)|(0<<PORTC2)|(0<<PORTC3)|(0<<PORTC4)|(0<<PORTC5);
	DDRC= (0<<DDC0)|(0<<DDC0)|(0<<DDC2)|(0<<DDC3)|(0<<DDC4)|(0<<DDC5);
	*/
	PORTD=(0<<PORTD0)|(0<<PORTD0)|(0<<PORTD2)|(0<<PORTD3)|(0<<PORTD4)|(0<<PORTD5);
	DDRD= (0<<DDD0)|(0<<DDD0)|(0<<DDD2)|(0<<DDD3)|(1<<DDD4)|(0<<DDD5);
	
}

int main(void)
{
	
	init_I_O();
	//init_pwm_2();
	init_pwm_1();
	init_pwm_0();
	init_variables_main();
	USART_Init(MYUBRR);
	sei(); 
	
	
	while(1)
	{
		
		init_variables();
		LEDs_manipulations();
		//do_somethings();		
		
	}
}