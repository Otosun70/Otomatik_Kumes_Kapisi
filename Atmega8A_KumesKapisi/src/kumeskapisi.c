/*
 * kumeskapisi.c
 *
 * Created: 13.07.2019 12:04:52
 *  Author: Orhan
 *
 *	Bu proje tavuklarýn barýndýðý bir kümesin kapýsýný güneþ doðduðunda açmasý,
 *	güneþ battýðýnda kapatmasý için yapýlmýþtýr. 
 *
 *	Her gün sabah ve akþam hayvanlarla zamanýnda ilgilenme fýrsatýnýn bulunmadýðý 
 *	durumlarda hayvanlarýn zarar görmesini önlemek amaçlanmýþtýr.
 *	
 *	Proje farklý amaçlar için kullanýlabilir.
 *
 */ 
#include "include.h"

char calismaModlari[5]={'D','E','O','S','T'};//Dur,Emniyet,Otomatik,Sýkýþma,Test

/* 
	Belirlenen süre kadar istenen iþýk seviyesi devam ettiðinde 
	gündüz veya gece olduðuna karar veren fonksiyon 
*/  

void gece_gunduz_algilama()
{
	if (isikSeviyesi <= GECE_ISIK_SEVIYESI)
	{
		sayacGece++;
		sayacGunduz=0;
		
		if (sayacGece>(DEGISIM_BEKLEME_SURESI+kapanmaGecikmesi))
		{
			gunduzDurumu=false;
			sayacGece=(DEGISIM_BEKLEME_SURESI+kapanmaGecikmesi+1);
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
	if (sayac_motorAdim < KAPANMA_ADIM_SAYISI)
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
	if (sayac_motorAdim > BASLANGIC_ADIMI)
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

/*
	Kapý dýþarýdan müdahale ile açýlmaya veya kapatýlmaya çalýþýldýðýnda 
	bu durumu algýlayýp kapýyý olmasý gereken duruma getiren fonksiyon.
*/

void kapi_acik_kapali_kontrolu()
{
	if (sayac_motorAdim==BASLANGIC_ADIMI && !durum_switch_acik())
	{
		sayac_motorAdim=sayac_motorAdim+4;
	} 
	else if (sayac_motorAdim==KAPANMA_ADIM_SAYISI && !durum_switch_kapali())
	{
		sayac_motorAdim=KAPANMA_ADIM_SAYISI-4;
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
/*
	Kapý, donanýmda bulunan siwitch'lere ulaþtýðýnda sayaçlarý ve 
	motorun sýkýþmasýna karþý durumlarý ayarlayan fonksiyon 
*/
void switchDurumunaGoreSayacAyarlama()
{
	if (durum_switch_acik())
	{
		sayac_motorAdim=BASLANGIC_ADIMI;
		ledPeriyot=LED_NORMAL_ACIK;
		motor1_sikisma=false;
		sayac_motor1_sikisma=0;
	}
	else if (durum_switch_kapali())
	{
		sayac_motorAdim=KAPANMA_ADIM_SAYISI;
		ledPeriyot=LED_NORMAL_KAPALI;
		motor1_sikisma=false;
		sayac_motor1_sikisma=0;

	}

	if (sayac_motorAdim < BASLANGIC_ADIMI)
	{
		sayac_motorAdim = BASLANGIC_ADIMI;
	} 
	else if (sayac_motorAdim > KAPANMA_ADIM_SAYISI)
	{
		sayac_motorAdim = KAPANMA_ADIM_SAYISI;
	}

}
/*
	Bu fonksiyon; 3 konumlu bir anahtar ile kapýyý "Açýk","Kapalý" ve "Otomatik" 
	konumuna manuel olarak durumlandýrýlabilir.
*/
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
/*
	Bu fonksiyon; kapý kapanýrken araya sýkýþmayý önlemek için 
	kapýnýn ön tarafýnda bulunan IR ýþýk perdesini aktif hale getirir,
	bir nesne tespit ettiðinde istenen süre kadar kapýyý açar bekler 
	ve tekrar kapatýr.
*/
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
		if (sayac_motor1_sikisma < SIKISMADAN_KURTULMA_DENEME)
		{
			calismaModu='S';
		} 
		else
		{
			calismaModu='D';
// 			sayac_motorAdim=KAPANMA_ADIM_SAYISI;	//Motor durdurulduðunda kapý optik emniyetinin devre dýþý kalmasý için
		}
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
/*
	Bu fonksiyon; farklý durumlara göre belirlenen çalýþma modunu uygular.
*/
void calismaModlarininUygulanmasi()
{
	emniyetTedbirleri();
			
	switch(calismaModu)
	{
		case 'D':
			motor1_dur();
			optik_kapi_emniyeti_disable();
			optik_Encoder_disable();
			
		break;
				
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
			if (!birSaniye)
			{
				kapi_acik_kapali_kontrolu();
			}
				
		break;
				
		case 'S':
			if (motor1_sikisma_yon)
			{
				kapiyi_ac();
			}
			else
			{
				kapiyi_kapat();
			}
	
		break;
		
		case 'T':
		
		break;
	}
}

/*
	Bu fonksiyon 1 saniye periyod ile çalýþýr. Fonksiyon içinde ýþýk seviyesi ölçülür, 
	anahtar konumu kontrol edilir, motor sýkýþýklýðý kontrol edilir.
*/
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
			kapanmaGecikmesi=(ADC_get_conversion(4)*4);//1024*4/60=68 dakikalýk gecikme ayarlayabilmek için
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

/*
	Bu fonksiyonda motorun düzgün çalýþýp çalýþmadýðý optik enkoder ile 
	karþýlaþtýrýlarak tespit edilir ve deðiþkene atanýr.
*/

void motor1_sikisiklik_kontrolu()
{
	if (motor1_enable())
	{
		if (sayac_motorAdim==onceki_sayac_motorAdim)
		{
			motor1_sikisma=true;
			motor1_sikisma_yon=motor1_yon;
			ledPeriyot=LED_ARIZA;
			sayac_motor1_sikisma++;
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

	itoa( sayacGece, buffer, 10);
	uart_puts(buffer);
	uart_puts("\t");
	
	itoa( kapanmaGecikmesi, buffer, 10);
	uart_puts(buffer);
	uart_puts("\t");
	
	itoa( sayac_motorAdim, buffer, 10);
	uart_puts(buffer);
	uart_puts("\t");

	uart_putc(calismaModu);
	uart_puts("\n");

}
