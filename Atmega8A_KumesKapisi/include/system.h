/*
 * system.h
 *
 * Created: 19.07.2019 15:29:11
 *  Author: Orhan
 */ 


#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "include.h"

#ifndef F_CPU
#error "F_CPU undefined, please define CPU frequency in Hz in Makefile"
#endif


void sistem_init();

void devre_init();

void timer0_init();

void timer1_init();

void timer2_init();

void powerSaveControl();



#endif /* SYSTEM_H_ */