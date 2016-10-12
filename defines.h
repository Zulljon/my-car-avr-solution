#define F_CPU 16000000
#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR (FOSC/16/BAUD-1)



#define BUFFER_MAX 8



//---------------SWITCH--------------------------//
#define not_set_yet				0x0
#define SET_SERVO_RIGHT			0x1				// пока оставим для отладки в железе
#define MOTORchik				0x2
#define LEDS_B_PS				0x3
#define SERVO					0x4
#define LEDS_FRONT				0x5
#define SET_MOTOR_FREQ			0x6
#define SET_SERVO_LEFT			0x7				// пока оставим для отладки в железе
//---------------------------------------------//