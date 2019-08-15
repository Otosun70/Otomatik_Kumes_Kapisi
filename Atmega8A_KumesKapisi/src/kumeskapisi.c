/*
 * kumeskapisi.c
 *
 * Created: 13.07.2019 12:04:52
 *  Author: Orhan
 */ 
#include "include.h"

char calismaModlari[3]={'E','O','T'};//Acik,Emniyet,Kapali,Otomatik,Test


void gece_gunduz_algilama()
{
	if (isikSeviyesi <= GECE_ISIK_SEVIYESI)
	{
		sayacGece++;
		sayacGunduz=0;
		
		if (sayacGece>DEGISIM_BEKLEME_SURESI)
		{
			gunduzDurumu=false;
			sayacGece=DEGISIM_BEKLEME_SURESI+1;
		}
	}
	else if (isikSeviyesi >= GUNDUZ_ISIK_SEVIYESI)
	{
		sayacGunduz++;
		sayacGece=0;

		if (sayacGunduz>DEGISIM_BEKLEME_SURESI)
		{
			gunduzDurumu=true;
			sayacGunduz=DEGISIM_BEKLEME_SURESI+1;
		}
	}
}

void kapiyi_kapat()
{
	if (sayac_motorAdim < ACMA_KAPAMA_ADIM_SAYISI)
	{
		optik_kapi_emniyeti_enable();	
		optik_Encoder_enable();
		motor1_ileri();
		motor1_yon=true;

	}
	else
	{
		motor1_dur();
		optik_kapi_emniyeti_disable();
		optik_Encoder_disable();
	}
}

void kapiyi_ac()
{
	if (sayac_motorAdim > 0)
	{
		optik_Encoder_enable();
		motor1_geri();
		motor1_yon=false;

	}
	else
	{
		motor1_dur();
		optik_Encoder_disable();
	}

}

void kapiyi_otomatik_acma_kapatma()
{
	if(gunduzDurumu)
	{
		kapiyi_ac();
	}
	else
	{
		kapiyi_kapat();
	}
}

void switchDurumunaGoreSayacAyarlama()
{
	if (durum_switch_acik())
	{
		sayac_motorAdim=0;
		ledPeriyot=LED_NORMAL;
		motor1_sikisma=false;
	}
	else if (durum_switch_kapali())
	{
		sayac_motorAdim=50;
		ledPeriyot=LED_NORMAL;
		motor1_sikisma=false;
	}

	if (sayac_motorAdim<0)
	{
		sayac_motorAdim=0;
	} 
	else if (sayac_motorAdim> ACMA_KAPAMA_ADIM_SAYISI)
	{
		sayac_motorAdim=ACMA_KAPAMA_ADIM_SAYISI;
	}

}

void anahtarKonumunaGoreSistemin_isletilmesi()
{
	switch (anahtarKonumu)
	{
		case 0:
		kapiyi_ac();
		break;
		
		case 1:
		calismaModlarininUygulanmasi();
		break;
		
		case 2:
		kapiyi_kapat();
		break;
	}
}

void emniyetTedbirleri()
{

	if (!durum_optik_kapi_emniyeti())
	{
		calismaModu='E';
		ledAc();
		sayacEmniyet=0;
	}
	else if(motor1_sikisma)
	{
		calismaModu='T';
	}
	else
	{
		if (sayacEmniyet>EMNIYET_BEKLEME_SURESI)
		{
			sayacEmniyet=EMNIYET_BEKLEME_SURESI+1;
			calismaModu='O';
		}
		ledKapat();
	}
}

void calismaModlarininUygulanmasi()
{
	emniyetTedbirleri();
			
	switch(calismaModu)
	{
				
		case 'E':
			if (!durum_switch_kapali())	//Kapý kapalý iken tekrar açýlmamasý için switch durumuna baðlý olarak kapý açtýrýldý
			{
				kapiyi_ac();
			}
			else
			{
				sayacEmniyet=EMNIYET_BEKLEME_SURESI+1;	//Emniyet sayacýndan dolayý beklemeyi önlemek için sayaç güvenli deðere ayarlandý
			}
				
		break;
				
				
		case 'O':
				
			kapiyi_otomatik_acma_kapatma();
				
		break;
				
		case 'T':
			if (motor1_yon)
			{
				kapiyi_ac();
			}
			else
			{
				kapiyi_kapat();
			}
	
				
		break;
	}
}

void zamanli_islemler()
{
	if (durum0)
	{
		if (birSaniye)
		{
			birSaniye=false;
			sayacEmniyet++;
			isikSeviyesi=(ADC_get_conversion(6));
			anahtarKonumu=(ADC_get_conversion(7)/340);//üç konumlu anahtar kullanacaðýmýz için 340'a böldüm
			gece_gunduz_algilama();
			motor1_sikisiklik_kontrolu();
			uart_yazdir();
		}
	}
	else
	{
		birSaniye=true;
	}	
}

void motor1_sikisiklik_kontrolu()
{
	if (motor1_enable())
	{
		if (sayac_motorAdim==onceki_sayac_motorAdim)
		{
			motor1_sikisma=true;
			ledPeriyot=LED_ARIZA;
		}
		else
		{
			motor1_sikisma=false;
		}
	} 
	onceki_sayac_motorAdim=sayac_motorAdim;
}

void led_komuta()
{
	if (durumLed)
	{
		ledAc();
	}
	else
	{
		ledKapat();
	}
}

void uart_yazdir()
{
	char buffer[7];
	
	itoa( isikSeviyesi, buffer, 10);   // convert interger into string (decimal format)
	uart_puts("\t");
	uart_puts(buffer);        
	uart_puts("\t");
/*
	itoa( sayacGece, buffer, 10);
	uart_puts(buffer);
	uart_puts("\t");
	*/
	itoa( anahtarKonumu, buffer, 10);
	uart_puts(buffer);
	uart_puts("\t");
	
	itoa( sayac_motorAdim, buffer, 10);
	uart_puts(buffer);
	uart_puts("\t");

	uart_putc(calismaModu);
	uart_puts("\n");

}
