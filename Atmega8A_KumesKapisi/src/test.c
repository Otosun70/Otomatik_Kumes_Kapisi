/*
 * test.c
 *
 * Created: 25.07.2019 13:39:57
 *  Author: Orhan
 */ 
#include "include.h"

bool motor1_ileriTest()
{
	sayac_t testMotor1Adim;
	testMotor1Adim=sayac_motorAdim;
	motor1_ileri();
	if (sayac_motorAdim>testMotor1Adim+4)
	{
		motor1_dur();
		return true;
	}
	else
	{
		return false;
	}
}