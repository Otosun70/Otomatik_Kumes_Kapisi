/*
 * system.c
 *
 * Created: 19.07.2019 15:29:36
 *  Author: tosun_n
 */ 
#include "include.h"

void sistem_init()
{
	devre_init();
	motor2_init();
	motor1_init();
	ADC_init();
	WDT_init();
	switch_Acik_Kapali_init();
	led_init();
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );
	timer1_init();
	timer0_init();
	optik_Encoder_init();
	optik_kapi_emniyeti_init();
	powerSaveControl();

	sei();
	
}

void powerSaveControl()
{
	ACSR |= (1<<7);//Anolog Comparator disable yapýldý.
	MCUCR |=(1<<2);//ADC noise reduction enable yapýldý.
	MCUCR |=(1<<5);//Sleep enable yapýldý.
}

void devre_init()
{
	isikSeviyesi=0;
	sayacGece=0;
	sayacGunduz=0;
	ledPeriyot=LED_NORMAL;
	sayac_motorAdim=0;
	sayac_motor1_sikisma=0;
	gunduzDurumu=true;
	calismaModu='O';
	optik_kapi_emniyeti_disable();
}
void WDT_init()
{
	#if (ENABLE_WATCHDOG == 1)
	wdt_enable(WDTO_1S);
	#endif
}

void timer0_init()
{
	TCCR0 |=(1<<CS02)|(1<<CS00);
	TIMSK  |= (1<<TOIE0);
}

void timer1_init()	
{
	TCCR1B |= (1<<WGM12)|(1<<CS12)|(1<<CS10);
	OCR1A = ZAMANLI_ISLEMLER_PERIYOT;
	TIMSK |= (1 << OCIE1A);
}

void timer2_init()
{
	TCCR2 |=(1<<CS22)|(1<<CS20);
	TIMSK  |= (1<<TOIE2);
}

ISR(TIMER0_OVF_vect)
{
	sayactimer0++;
	if (sayactimer0>ledPeriyot)
	{
		if (durumLed)
		{
			sayactimer0=0;
			durumLed=false;
		} 
		else
		{
			sayactimer0=(ledPeriyot-3);
			durumLed=true;
		}
	}
	if (sayacTest>0)
	{
		sayacTest--;
	}
 
}

ISR(TIMER1_COMPA_vect)
{
	if (durum0)
	{
		durum0=false;
	}
	else
	{
		durum0=true;
	}
}