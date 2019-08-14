/*
 * driver.h
 *
 * Created: 19.07.2019 11:59:00
 *  Author: Orhan
 */ 
#include <avr/io.h>
#include <stdbool.h>

#ifndef DRIVER_H_
#define DRIVER_H_

#define LED							PORTC0
#define LED_DDR						DDRC
#define LED_PORT					PORTC

#define SWITCH_ACIK					PIND4
#define SWITCH_KAPALI				PIND3
#define SWITCH_KAPALI_DDR			DDRD
#define SWITCH_ACIK_DDR				DDRD
#define SWITCH_KAPALI_PORT			PORTD
#define SWITCH_ACIK_PORT			PORTD
#define SWITCH_KAPALI_PIN			PIND
#define SWITCH_ACIK_PIN				PIND

#define OPTIK_ENCODER				PIND2
#define OPTIK_ENCODER_DDR			DDRD
#define OPTIK_ENCODER_PORT			PORTD
#define OPTIK_ENCODER_PIN			PIND
#define OPTIK_ENCODER_LED_DDR		DDRC
#define OPTIK_ENCODER_LED_PORT		PORTC
#define OPTIK_ENCODER_LED			PORTC3

#define OPTIK_KAPI_EMNIYETI			PINC1
#define OPTIK_KAPI_EMNIYETI_DDR		DDRC
#define OPTIK_KAPI_EMNIYETI_PORT	PORTC
#define OPTIK_KAPI_EMNIYETI_PIN		PINC
#define OPTIK_KAPI_EMNIYETI_LED		PORTC2


void led_init();

void switch_Acik_Kapali_init();

void optik_Encoder_init();

void optik_kapi_emniyeti_init();

void ledAc();

void ledKapat();

bool durum_switch_acik();

bool durum_switch_kapali();

void optik_Encoder_enable();

void optik_Encoder_disable();

bool durum_optik_kapi_emniyeti();

void optik_kapi_emniyeti_enable();

void optik_kapi_emniyeti_disable();

#endif /* DRIVER_H_ */