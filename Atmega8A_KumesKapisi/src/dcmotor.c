/*
 * DcMotor.c
 *
 * Created: 19.07.2019 11:47:47
 *  Author: Orhan
 */ 
#include <avr/io.h>
#include "dcmotor.h"

void motor1_init()
{
	MOTOR1_DDR |= (1<<MOTOR1_A)|(1<<MOTOR1_B);
	MOTOR_EN_DDR |= (1<<MOTOR1_EN);

}

void motor2_init()
{
	MOTOR2_DDRA |= (1<<MOTOR1_A);
	MOTOR2_DDRB |= (1<<MOTOR1_B);
	MOTOR_EN_DDR |= (1<<MOTOR2_EN);
}


void motor1_geri()
{
	MOTOR1_PORT	|= (1<<MOTOR1_A);
	MOTOR1_PORT &=~ (1<<MOTOR1_B);
	MOTOR_EN_PORT |= (1<<MOTOR1_EN);
// 	set_PWM();
}

void motor1_ileri()
{
	MOTOR1_PORT	|= (1<<MOTOR1_B);
	MOTOR1_PORT &=~ (1<<MOTOR1_A);
	MOTOR_EN_PORT |= (1<<MOTOR1_EN);
// 	set_PWM();
}

void motor1_dur()
{
	MOTOR1_PORT &=~ (1<<MOTOR1_A);
	MOTOR1_PORT &=~ (1<<MOTOR1_B);
	MOTOR_EN_PORT &=~ (1<<MOTOR1_EN);
}

void motor1_acil_dur()
{
	MOTOR1_PORT &=~ (1<<MOTOR1_A);
	MOTOR1_PORT &=~ (1<<MOTOR1_B);
	MOTOR_EN_PORT &=~ (1<<MOTOR1_EN);

}

void motor2_ileri()
{
	MOTOR2_PORTA	|= (1<<MOTOR2_A);
	MOTOR2_PORTB &=~ (1<<MOTOR2_B);
	MOTOR_EN_PORT |= (1<<MOTOR2_EN);
}

void motor2_geri()
{
	MOTOR1_PORT	|= (1<<MOTOR2_B);
	MOTOR1_PORT &=~ (1<<MOTOR2_A);
	MOTOR_EN_PORT |= (1<<MOTOR2_EN);
}

void motor2_dur()
{
	MOTOR_EN_PORT &=~ (1<<MOTOR2_EN);
}

void motor2_acil_dur()
{
	MOTOR1_PORT &=~ (1<<MOTOR2_A);
	MOTOR1_PORT &=~ (1<<MOTOR2_B);
	MOTOR_EN_PORT &=~ (1<<MOTOR2_EN);
}

void set_PWM()
{
	PWM_MOTOR1=PWM_valueMotor1;
}