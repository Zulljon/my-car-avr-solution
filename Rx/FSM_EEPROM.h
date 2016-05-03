/*
 * FSM_EEPROM.h
 *
 * Created: 26.04.2016 14:49:56
 *  Author: Dan
 */ 


#ifndef FSM_EEPROM_H_
#define FSM_EEPROM_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

char FSM_EEPROM_init(void);
char FSM_EEPROM(void);
char FSM_EEPROM_r();
char FSM_EEPROM_w();

#endif /* FSM_EEPROM_H_ */