﻿/*
 * kumeskapisi.h
 *
 * Created: 13.07.2019 11:36:01
 *  Author: Orhan
 */ 


#ifndef KUMESKAPISI_H_
#define KUMESKAPISI_H_

typedef int8_t sayac_t;
typedef uint8_t konum_t;
typedef uint16_t seviye_t;
typedef bool durum;


#include <avr/io.h>
#include <stdbool.h>


#define UART_BAUD_RATE				38400
#define GECE_ISIK_SEVIYESI			0
#define GUNDUZ_ISIK_SEVIYESI		50
#define DEGISIM_BEKLEME_SURESI		60
#define KAPANMA_ADIM_SAYISI			50
#define BASLANGIC_ADIMI				0
#define ZAMANLI_ISLEMLER_PERIYOT	F_CPU/2048
#define EMNIYET_BEKLEME_SURESI		5
#define LED_NORMAL_ACIK				120
#define LED_NORMAL_KAPALI			64
#define LED_ARIZA					8
#define SIKISMADAN_KURTULMA_DENEME	4


seviye_t isikSeviyesi;
seviye_t kapanmaGecikmesi;
konum_t anahtarKonumu;
sayac_t sayacGunduz;
seviye_t sayacGece;
sayac_t sayac_motorAdim;
sayac_t onceki_sayac_motorAdim;
sayac_t sayactimer0;
sayac_t sayacEmniyet;
sayac_t sayac_motor1_sikisma;
uint8_t ledPeriyot;

durum durum0;
durum durumLed;
durum birSaniye;
durum gunduzDurumu;
durum motor1_yon;
durum motor1_sikisma;
durum motor1_sikisma_yon;
char calismaModu;



void uart_yazdir();

void gece_gunduz_algilama();

void kapiyi_otomatik_acma_kapatma();

void kapiyi_kapat();

void kapiyi_ac();

void zamanli_islemler();

void led_komuta();

void emniyetTedbirleri();

void switchDurumunaGoreSayacAyarlama();

void anahtarKonumunaGoreSistemin_isletilmesi();

void calismaModlarininUygulanmasi();

void motor1_sikisiklik_kontrolu();

void WDT_init();

#endif /* KUMESKAPISI_H_ */