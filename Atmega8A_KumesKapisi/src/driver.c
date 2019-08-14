/*
 * driver.c
 *
 * Created: 19.07.2019 11:58:42
 *  Author: Orhan
 */ 

#include "include.h"


void led_init()
{
	LED_DDR |= (1<<LED);
}

void switch_Acik_Kapali_init()
{
	SWITCH_KAPALI_DDR &=~ (1<<SWITCH_KAPALI);
	SWITCH_ACIK_DDR &=~ (1<<SWITCH_ACIK);
	
	SWITCH_KAPALI_PORT |= (1<<SWITCH_KAPALI);
	SWITCH_ACIK_PORT   |= (1<<SWITCH_ACIK);
}

void optik_Encoder_init()
{
	GICR|= (1<<INT0);
	MCUCR|= (1<<ISC01)|(1<<ISC00);
	OPTIK_ENCODER_PIN |= (1<<OPTIK_ENCODER);
	OPTIK_ENCODER_PORT |= (1<<OPTIK_ENCODER);
	OPTIK_ENCODER_LED_DDR |= (1<<OPTIK_ENCODER_LED);
}

void optik_kapi_emniyeti_init()
{
	OPTIK_KAPI_EMNIYETI_PIN |= (1<<OPTIK_KAPI_EMNIYETI);
	OPTIK_KAPI_EMNIYETI_DDR |= (1<<OPTIK_KAPI_EMNIYETI_LED);
}

void optik_Encoder_enable()
{
	OPTIK_ENCODER_LED_PORT |=(1<<OPTIK_ENCODER_LED);
}

void optik_Encoder_disable()
{
	OPTIK_ENCODER_LED_PORT &=~ (1<<OPTIK_ENCODER_LED);
}

void optik_kapi_emniyeti_enable()
{
	OPTIK_KAPI_EMNIYETI_PORT &=~ (1<<OPTIK_KAPI_EMNIYETI_LED);

}

void optik_kapi_emniyeti_disable()
{
	OPTIK_KAPI_EMNIYETI_PORT |= (1<<OPTIK_KAPI_EMNIYETI_LED);
}

bool durum_optik_kapi_emniyeti()
{
	if (!(OPTIK_KAPI_EMNIYETI_PIN & (1<<OPTIK_KAPI_EMNIYETI_LED)))
	{
		return(OPTIK_KAPI_EMNIYETI_PIN &(1<<OPTIK_KAPI_EMNIYETI));
	} 
	else
	{
		return true;
	}
}

void ledAc()
{
	LED_PORT |=(1<<LED);
}

void ledKapat()
{
	LED_PORT &=~ (1<<LED);
}

bool durum_switch_acik()
{
	return!(SWITCH_ACIK_PIN &(1<<SWITCH_ACIK));
}

bool durum_switch_kapali()
{
	return!(SWITCH_KAPALI_PIN &(1<<SWITCH_KAPALI));
}

ISR(INT0_vect){

	if (motor1_yon)
	{
		sayac_motorAdim++;
	}
	else
	{
		sayac_motorAdim--;
	}
}
