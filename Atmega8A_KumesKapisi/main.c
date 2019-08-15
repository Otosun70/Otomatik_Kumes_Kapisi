/*
 * Atmega8A_KumesKapisi.c
 *
 * Created: 13.07.2019 11:34:33
 * Author : Orhan
 */ 

#include "include.h"


	
int main(void)
{
	sistem_init();
    while (1) 
    {
		switchDurumunaGoreSayacAyarlama();
		
		anahtarKonumunaGoreSistemin_isletilmesi();

		zamanli_islemler();	
		
		led_komuta();	
    }
}

