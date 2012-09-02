/*
 * (C) Copyright 2003
 * David M�ller ELSOFT AG Switzerland. d.mueller@elsoft.ch
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/************************************************
 * NAME     : s3c24x0.h
 * Version  : 31.3.2003
 *
 * common stuff for SAMSUNG S3C24X0 SoC
 ************************************************/

#ifndef __S3C24X0_H__
#define __S3C24X0_H__

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;

typedef volatile u8 S3C24X0_REG8;
typedef volatile u16    S3C24X0_REG16;
typedef volatile u32    S3C24X0_REG32;

/* Memory controller (see manual chapter 5) */
typedef struct {
    S3C24X0_REG32   BWSCON;
    S3C24X0_REG32   BANKCON[8];
    S3C24X0_REG32   REFRESH;
    S3C24X0_REG32   BANKSIZE;
    S3C24X0_REG32   MRSRB6;
    S3C24X0_REG32   MRSRB7;
} /*__attribute__((__packed__))*/ S3C24X0_MEMCTL;


/* USB HOST (see manual chapter 12) */
typedef struct {
    S3C24X0_REG32   HcRevision;
    S3C24X0_REG32   HcControl;
    S3C24X0_REG32   HcCommonStatus;
    S3C24X0_REG32   HcInterruptStatus;
    S3C24X0_REG32   HcInterruptEnable;
    S3C24X0_REG32   HcInterruptDisable;
    S3C24X0_REG32   HcHCCA;
    S3C24X0_REG32   HcPeriodCuttendED;
    S3C24X0_REG32   HcControlHeadED;
    S3C24X0_REG32   HcControlCurrentED;
    S3C24X0_REG32   HcBulkHeadED;
    S3C24X0_REG32   HcBuldCurrentED;
    S3C24X0_REG32   HcDoneHead;
    S3C24X0_REG32   HcRmInterval;
    S3C24X0_REG32   HcFmRemaining;
    S3C24X0_REG32   HcFmNumber;
    S3C24X0_REG32   HcPeriodicStart;
    S3C24X0_REG32   HcLSThreshold;
    S3C24X0_REG32   HcRhDescriptorA;
    S3C24X0_REG32   HcRhDescriptorB;
    S3C24X0_REG32   HcRhStatus;
    S3C24X0_REG32   HcRhPortStatus1;
    S3C24X0_REG32   HcRhPortStatus2;
} /*__attribute__((__packed__))*/ S3C24X0_USB_HOST;


/* INTERRUPT (see manual chapter 14) */
typedef struct {
    S3C24X0_REG32   SRCPND;
    S3C24X0_REG32   INTMOD;
    S3C24X0_REG32   INTMSK;
    S3C24X0_REG32   PRIORITY;
    S3C24X0_REG32   INTPND;
    S3C24X0_REG32   INTOFFSET;
    S3C24X0_REG32   SUBSRCPND;
    S3C24X0_REG32   INTSUBMSK;
} /*__attribute__((__packed__))*/ S3C24X0_INTERRUPT;


/* DMAS (see manual chapter 8) */
typedef struct {
    S3C24X0_REG32   DISRC;
    S3C24X0_REG32   DISRCC;
    S3C24X0_REG32   DIDST;
    S3C24X0_REG32   DIDSTC;
    S3C24X0_REG32   DCON;
    S3C24X0_REG32   DSTAT;
    S3C24X0_REG32   DCSRC;
    S3C24X0_REG32   DCDST;
    S3C24X0_REG32   DMASKTRIG;
    S3C24X0_REG32   res[7];
} /*__attribute__((__packed__))*/ S3C24X0_DMA;

typedef struct {
    S3C24X0_DMA dma[4];
} /*__attribute__((__packed__))*/ S3C24X0_DMAS;


/* CLOCK & POWER MANAGEMENT (see S3C2400 manual chapter 6) */
/*                          (see S3C2410 manual chapter 7) */
typedef struct {
    S3C24X0_REG32   LOCKTIME;
    S3C24X0_REG32   MPLLCON;
    S3C24X0_REG32   UPLLCON;
    S3C24X0_REG32   CLKCON;
    S3C24X0_REG32   CLKSLOW;
    S3C24X0_REG32   CLKDIVN;
    S3C24X0_REG32   CAMDIVN;    /* for s3c2440 */
} /*__attribute__((__packed__))*/ S3C24X0_CLOCK_POWER;


/* LCD CONTROLLER (see manual chapter 15) */
typedef struct {
    S3C24X0_REG32   LCDCON1;
    S3C24X0_REG32   LCDCON2;
    S3C24X0_REG32   LCDCON3;
    S3C24X0_REG32   LCDCON4;
    S3C24X0_REG32   LCDCON5;
    S3C24X0_REG32   LCDSADDR1;
    S3C24X0_REG32   LCDSADDR2;
    S3C24X0_REG32   LCDSADDR3;
    S3C24X0_REG32   REDLUT;
    S3C24X0_REG32   GREENLUT;
    S3C24X0_REG32   BLUELUT;
    S3C24X0_REG32   res[8];
    S3C24X0_REG32   DITHMODE;
    S3C24X0_REG32   TPAL;
    S3C24X0_REG32   LCDINTPND;
    S3C24X0_REG32   LCDSRCPND;
    S3C24X0_REG32   LCDINTMSK;
    S3C24X0_REG32   LPCSEL;
} /*__attribute__((__packed__))*/ S3C24X0_LCD;

/* NAND FLASH (see S3C2440 manual chapter 6) */
typedef struct {
    S3C24X0_REG32   NFCONF;
    S3C24X0_REG32   NFCONT;
    S3C24X0_REG32   NFCMD;
    S3C24X0_REG32   NFADDR;
    S3C24X0_REG32   NFDATA;
    S3C24X0_REG32   NFMECCD0;
    S3C24X0_REG32   NFMECCD1;
    S3C24X0_REG32   NFSECCD;
    S3C24X0_REG32   NFSTAT;
    S3C24X0_REG32   NFESTAT0;
    S3C24X0_REG32   NFESTAT1;
    S3C24X0_REG32   NFMECC0;
    S3C24X0_REG32   NFMECC1;
    S3C24X0_REG32   NFSECC;
    S3C24X0_REG32   NFSBLK;
    S3C24X0_REG32   NFEBLK;
} /*__attribute__((__packed__))*/ S3C2440_NAND;

/* UART (see manual chapter 11) */
typedef struct {
    S3C24X0_REG32   ULCON;
    S3C24X0_REG32   UCON;
    S3C24X0_REG32   UFCON;
    S3C24X0_REG32   UMCON;
    S3C24X0_REG32   UTRSTAT;
    S3C24X0_REG32   UERSTAT;
    S3C24X0_REG32   UFSTAT;
    S3C24X0_REG32   UMSTAT;
    S3C24X0_REG8    UTXH;
    S3C24X0_REG8    res1[3];
    S3C24X0_REG8    URXH;
    S3C24X0_REG8    res2[3];
    S3C24X0_REG32   UBRDIV;
} /*__attribute__((__packed__))*/ S3C24X0_UART;


/* PWM TIMER (see manual chapter 10) */
typedef struct {
    S3C24X0_REG32   TCNTB;
    S3C24X0_REG32   TCMPB;
    S3C24X0_REG32   TCNTO;
} /*__attribute__((__packed__))*/ S3C24X0_TIMER;

typedef struct {
    S3C24X0_REG32   TCFG0;
    S3C24X0_REG32   TCFG1;
    S3C24X0_REG32   TCON;
    S3C24X0_TIMER   ch[4];
    S3C24X0_REG32   TCNTB4;
    S3C24X0_REG32   TCNTO4;
} /*__attribute__((__packed__))*/ S3C24X0_TIMERS;


/* USB DEVICE (see manual chapter 13) */
typedef struct {
    S3C24X0_REG8    EP_FIFO_REG;
    S3C24X0_REG8    res[3];
} /*__attribute__((__packed__))*/ S3C24X0_USB_DEV_FIFOS;

typedef struct {
    S3C24X0_REG8    EP_DMA_CON;
    S3C24X0_REG8    res1[3];
    S3C24X0_REG8    EP_DMA_UNIT;
    S3C24X0_REG8    res2[3];
    S3C24X0_REG8    EP_DMA_FIFO;
    S3C24X0_REG8    res3[3];
    S3C24X0_REG8    EP_DMA_TTC_L;
    S3C24X0_REG8    res4[3];
    S3C24X0_REG8    EP_DMA_TTC_M;
    S3C24X0_REG8    res5[3];
    S3C24X0_REG8    EP_DMA_TTC_H;
    S3C24X0_REG8    res6[3];
} /*__attribute__((__packed__))*/ S3C24X0_USB_DEV_DMAS;

typedef struct {
    S3C24X0_REG8    FUNC_ADDR_REG;
    S3C24X0_REG8    res1[3];
    S3C24X0_REG8    PWR_REG;
    S3C24X0_REG8    res2[3];
    S3C24X0_REG8    EP_INT_REG;
    S3C24X0_REG8    res3[15];
    S3C24X0_REG8    USB_INT_REG;
    S3C24X0_REG8    res4[3];
    S3C24X0_REG8    EP_INT_EN_REG;
    S3C24X0_REG8    res5[15];
    S3C24X0_REG8    USB_INT_EN_REG;
    S3C24X0_REG8    res6[3];
    S3C24X0_REG8    FRAME_NUM1_REG;
    S3C24X0_REG8    res7[3];
    S3C24X0_REG8    FRAME_NUM2_REG;
    S3C24X0_REG8    res8[3];
    S3C24X0_REG8    INDEX_REG;
    S3C24X0_REG8    res9[7];
    S3C24X0_REG8    MAXP_REG;
    S3C24X0_REG8    res10[3];
    S3C24X0_REG8    EP0_CSR_IN_CSR1_REG;
    S3C24X0_REG8    res11[3];
    S3C24X0_REG8    IN_CSR2_REG;
    S3C24X0_REG8    res12[7];
    S3C24X0_REG8    OUT_CSR1_REG;
    S3C24X0_REG8    res13[3];
    S3C24X0_REG8    OUT_CSR2_REG;
    S3C24X0_REG8    res14[3];
    S3C24X0_REG8    OUT_FIFO_CNT1_REG;
    S3C24X0_REG8    res15[3];
    S3C24X0_REG8    OUT_FIFO_CNT2_REG;
    S3C24X0_REG8    res16[3];
    S3C24X0_REG32   res17[8];
    S3C24X0_USB_DEV_FIFOS   fifo[5];
    S3C24X0_REG32   res18[11];
    S3C24X0_USB_DEV_DMAS    ep1;
    S3C24X0_USB_DEV_DMAS    ep2;
    S3C24X0_REG8    res19[16];
    S3C24X0_USB_DEV_DMAS    ep3;
    S3C24X0_USB_DEV_DMAS    ep4;
} /*__attribute__((__packed__))*/ S3C24X0_USB_DEVICE;


/* WATCH DOG TIMER (see manual chapter 18) */
typedef struct {
    S3C24X0_REG32   WTCON;
    S3C24X0_REG32   WTDAT;
    S3C24X0_REG32   WTCNT;
} /*__attribute__((__packed__))*/ S3C24X0_WATCHDOG;


/* IIC (see manual chapter 20) */
typedef struct {
    S3C24X0_REG32   IICCON;
    S3C24X0_REG32   IICSTAT;
    S3C24X0_REG32   IICADD;
    S3C24X0_REG32   IICDS;
} /*__attribute__((__packed__))*/ S3C24X0_I2C;


/* IIS (see manual chapter 21) */
typedef struct {
    S3C24X0_REG16   IISCON;
    S3C24X0_REG16   res1;
    S3C24X0_REG16   IISMOD;
    S3C24X0_REG16   res2;
    S3C24X0_REG16   IISPSR;
    S3C24X0_REG16   res3;
    S3C24X0_REG16   IISFCON;
    S3C24X0_REG16   res4;
    S3C24X0_REG16   IISFIFO;
    S3C24X0_REG16   res5;
} /*__attribute__((__packed__))*/ S3C24X0_I2S;


/* I/O PORT (see manual chapter 9) */
typedef struct {
    S3C24X0_REG32   GPACON;
    S3C24X0_REG32   GPADAT;
    S3C24X0_REG32   res1[2];
    S3C24X0_REG32   GPBCON;
    S3C24X0_REG32   GPBDAT;
    S3C24X0_REG32   GPBUP;
    S3C24X0_REG32   res2;
    S3C24X0_REG32   GPCCON;
    S3C24X0_REG32   GPCDAT;
    S3C24X0_REG32   GPCUP;
    S3C24X0_REG32   res3;
    S3C24X0_REG32   GPDCON;
    S3C24X0_REG32   GPDDAT;
    S3C24X0_REG32   GPDUP;
    S3C24X0_REG32   res4;
    S3C24X0_REG32   GPECON;
    S3C24X0_REG32   GPEDAT;
    S3C24X0_REG32   GPEUP;
    S3C24X0_REG32   res5;
    S3C24X0_REG32   GPFCON;
    S3C24X0_REG32   GPFDAT;
    S3C24X0_REG32   GPFUP;
    S3C24X0_REG32   res6;
    S3C24X0_REG32   GPGCON;
    S3C24X0_REG32   GPGDAT;
    S3C24X0_REG32   GPGUP;
    S3C24X0_REG32   res7;
    S3C24X0_REG32   GPHCON;
    S3C24X0_REG32   GPHDAT;
    S3C24X0_REG32   GPHUP;
    S3C24X0_REG32   res8;

    S3C24X0_REG32   MISCCR;
    S3C24X0_REG32   DCLKCON;
    S3C24X0_REG32   EXTINT0;
    S3C24X0_REG32   EXTINT1;
    S3C24X0_REG32   EXTINT2;
    S3C24X0_REG32   EINTFLT0;
    S3C24X0_REG32   EINTFLT1;
    S3C24X0_REG32   EINTFLT2;
    S3C24X0_REG32   EINTFLT3;
    S3C24X0_REG32   EINTMASK;
    S3C24X0_REG32   EINTPEND;
    S3C24X0_REG32   GSTATUS0;
    S3C24X0_REG32   GSTATUS1;
    S3C24X0_REG32   GSTATUS2;
    S3C24X0_REG32   GSTATUS3;
    S3C24X0_REG32   GSTATUS4;

    /* s3c2440 */
    S3C24X0_REG32   res9[4];
    S3C24X0_REG32   GPJCON;
    S3C24X0_REG32   GPJDAT;
    S3C24X0_REG32   GPJUP;
} /*__attribute__((__packed__))*/ S3C24X0_GPIO;


/* RTC (see manual chapter 17) */
typedef struct {
    S3C24X0_REG8    res0[64];
    S3C24X0_REG8    RTCCON;
    S3C24X0_REG8    res1[3];
    S3C24X0_REG8    TICNT;
    S3C24X0_REG8    res2[11];
    S3C24X0_REG8    RTCALM;
    S3C24X0_REG8    res3[3];
    S3C24X0_REG8    ALMSEC;
    S3C24X0_REG8    res4[3];
    S3C24X0_REG8    ALMMIN;
    S3C24X0_REG8    res5[3];
    S3C24X0_REG8    ALMHOUR;
    S3C24X0_REG8    res6[3];
    S3C24X0_REG8    ALMDATE;
    S3C24X0_REG8    res7[3];
    S3C24X0_REG8    ALMMON;
    S3C24X0_REG8    res8[3];
    S3C24X0_REG8    ALMYEAR;
    S3C24X0_REG8    res9[3];
    S3C24X0_REG8    RTCRST;
    S3C24X0_REG8    res10[3];
    S3C24X0_REG8    BCDSEC;
    S3C24X0_REG8    res11[3];
    S3C24X0_REG8    BCDMIN;
    S3C24X0_REG8    res12[3];
    S3C24X0_REG8    BCDHOUR;
    S3C24X0_REG8    res13[3];
    S3C24X0_REG8    BCDDATE;
    S3C24X0_REG8    res14[3];
    S3C24X0_REG8    BCDDAY;
    S3C24X0_REG8    res15[3];
    S3C24X0_REG8    BCDMON;
    S3C24X0_REG8    res16[3];
    S3C24X0_REG8    BCDYEAR;
    S3C24X0_REG8    res17[3];
} /*__attribute__((__packed__))*/ S3C24X0_RTC;


/* ADC (see manual chapter 16) */
typedef struct {
    S3C24X0_REG32   ADCCON;
    S3C24X0_REG32   ADCTSC;
    S3C24X0_REG32   ADCDLY;
    S3C24X0_REG32   ADCDAT0;
    S3C24X0_REG32   ADCDAT1;
} /*__attribute__((__packed__))*/ S3C2440_ADC;


/* SPI (see manual chapter 22) */
typedef struct {
    S3C24X0_REG32   SPCON;
    S3C24X0_REG32   SPSTA;
    S3C24X0_REG32   SPPIN;
    S3C24X0_REG32   SPPRE;
    S3C24X0_REG32   SPTDAT;
    S3C24X0_REG32   SPRDAT;
    S3C24X0_REG32   res[2];
} __attribute__((__packed__)) S3C24X0_SPI_CHANNEL;

typedef struct {
    S3C24X0_SPI_CHANNEL ch[S3C24X0_SPI_CHANNELS];
} /*__attribute__((__packed__))*/ S3C24X0_SPI;


/* SD INTERFACE (see S3C2410 manual chapter 19) */
typedef struct {
    S3C24X0_REG32   SDICON;
    S3C24X0_REG32   SDIPRE;
    S3C24X0_REG32   SDICARG;
    S3C24X0_REG32   SDICCON;
    S3C24X0_REG32   SDICSTA;
    S3C24X0_REG32   SDIRSP0;
    S3C24X0_REG32   SDIRSP1;
    S3C24X0_REG32   SDIRSP2;
    S3C24X0_REG32   SDIRSP3;
    S3C24X0_REG32   SDIDTIMER;
    S3C24X0_REG32   SDIBSIZE;
    S3C24X0_REG32   SDIDCON;
    S3C24X0_REG32   SDIDCNT;
    S3C24X0_REG32   SDIDSTA;
    S3C24X0_REG32   SDIFSTA;
    S3C24X0_REG8    SDIDAT;
    S3C24X0_REG8    res[3];
    S3C24X0_REG32   SDIIMSK;
} /*__attribute__((__packed__))*/ S3C2440_SDI;

#define rGSTATUS1       (*(volatile unsigned *)0x560000B0)
#define isS3C2410 		((rGSTATUS1 & 0xffff0000) == 0x32410000)

#endif /*__S3C24X0_H__*/
