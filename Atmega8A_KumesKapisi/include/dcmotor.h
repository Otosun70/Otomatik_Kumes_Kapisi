/*
 * DcMotor.h
 *
 * Created: 19.07.2019 11:47:23
 *  Author: tosun_n
 */ 

#include <stdbool.h>

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#define MOTOR1_DDR			DDRD
#define MOTOR2_DDRB			DDRD
#define MOTOR1_PIN			PIND
#define MOTOR2_PIN			PIND
#define MOTOR2_DDRA			DDRB
#define MOTOR_EN_DDR		DDRB

#define MOTOR1_PORT			PORTD
#define MOTOR2_PORTA		PORTB
#define MOTOR_EN_PORT		PORTB
#define MOTOR_EN_PIN		PINB
#define MOTOR2_PORTB		PORTD
#define MOTOR1_A			PORTD5
#define MOTOR1_B			PORTD6
#define MOTOR1_EN			PORTB1
#define MOTOR2_A			PORTB0
#define MOTOR2_B			PORTD7
#define MOTOR2_EN			PORTB2



void motor1_init();

void motor2_init();

void motor1_ileri();

void motor1_geri();

void motor1_dur();

void motor1_acil_dur();

void motor2_ileri();

void motor2_geri();

void motor2_dur();

void motor2_acil_dur();

bool motor1_enable();

bool motor2_enable();


#endif /* DCMOTOR_H_ */