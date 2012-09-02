/*
 * (C) Copyright 2001-2004
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * (C) Copyright 2002
 * David Mueller, ELSOFT AG, d.mueller@elsoft.ch
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

/* This code should work for both the S3C2400 and the S3C2410
 * as they seem to have the same PLL and clock machinery inside.
 * The different address mapping is handled by the s3c24xx.h files below.
 */

#include <s3c2440.h>

#define MPLL 0
#define UPLL 1

/* ------------------------------------------------------------------------- */
/* NOTE: This describes the proper use of this file.
 *
 * CONFIG_SYS_CLK_FREQ should be defined as the input frequency of the PLL.
 *
 * get_FCLK(), get_HCLK(), get_PCLK() and get_UCLK() return the clock of
 * the specified bus in HZ.
 */
/* ------------------------------------------------------------------------- */

static unsigned long get_PLLCLK(int pllreg)
{
    S3C24X0_CLOCK_POWER * const clk_power = S3C24X0_GetBase_CLOCK_POWER();
    unsigned long r, m, p, s;

    if (pllreg == MPLL)
	r = clk_power->MPLLCON;
    else if (pllreg == UPLL)
	r = clk_power->UPLLCON;
    else
	/* hang(); */
	    ;

    m = ((r & 0xFF000) >> 12) + 8;
    p = ((r & 0x003F0) >> 4) + 2;
    s = r & 0x3;

#define CONFIG_SYS_CLK_FREQ	12000000

    //return ((CONFIG_SYS_CLK_FREQ * m * 2) / (p << s));
    r =  ((CONFIG_SYS_CLK_FREQ * m * 2) * (1.0f / (p << s)));

    return r;
}

/* return FCLK frequency */
unsigned long get_FCLK(void)
{
    return(get_PLLCLK(MPLL));
}

/* 
 * new macro for S3C2440
 */
#define S3C2440_CLKDIVN_PDIVN		(1 << 0)
#define S3C2440_CLKDIVN_HDIVN_MASK	(3 << 1)
#define S3C2440_CLKDIVN_HDIVN_1		(0 << 1)
#define S3C2440_CLKDIVN_HDIVN_2		(1 << 1)
#define S3C2440_CLKDIVN_HDIVN_4_8	(2 << 1)
#define S3C2440_CLKDIVN_HDIVN_3_6	(3 << 1)
#define S3C2440_CLKDIVN_UCLK		(1 << 3)

#define S3C2440_CAMDIVN_CAMCLK_MASK	(0XF << 0)
#define S3C2440_CAMDIVN_CAMCLK_SEL	(1 << 4)
#define S3C2440_CAMDIVN_HCLK3_HALF	(1 << 8)
#define S3C2440_CAMDIVN_HCLK4_HALF	(1 << 9)
#define S3C2440_CAMDIVN_DVSEN		(1 << 12)
/*
 * end of new marco
 */

/* return HCLK frequency */
unsigned long get_HCLK(void)
{
    S3C24X0_CLOCK_POWER * const clk_power = S3C24X0_GetBase_CLOCK_POWER();
	unsigned long clkdiv, camdiv;
	int hdiv = 1;

	clkdiv = clk_power->CLKDIVN;
	camdiv = clk_power->CAMDIVN;

	/* work out clock scalings */
	switch (clkdiv & S3C2440_CLKDIVN_HDIVN_MASK) {
		case S3C2440_CLKDIVN_HDIVN_1:
			hdiv = 1;
			break;

		case S3C2440_CLKDIVN_HDIVN_2:
			hdiv = 2;
			break;

		case S3C2440_CLKDIVN_HDIVN_4_8:
			hdiv = (camdiv & S3C2440_CAMDIVN_HCLK4_HALF) ? 8: 4;
			break;

		case S3C2440_CLKDIVN_HDIVN_3_6:
			hdiv = (camdiv & S3C2440_CAMDIVN_HCLK3_HALF) ? 6: 3;
			break;
	}


    //return((clk_power->CLKDIVN & 0x2) ? get_FCLK()/2 : get_FCLK());
	return get_FCLK() / hdiv;
}

/* return PCLK frequency */
unsigned long get_PCLK(void)
{
    S3C24X0_CLOCK_POWER * const clk_power = S3C24X0_GetBase_CLOCK_POWER();
	unsigned long clkdiv, camdiv;
	int hdiv = 1;

	clkdiv = clk_power->CLKDIVN;
	camdiv = clk_power->CAMDIVN;

	switch (clkdiv & S3C2440_CLKDIVN_HDIVN_MASK) {
		case S3C2440_CLKDIVN_HDIVN_1:
			hdiv = 1;
			break;

		case S3C2440_CLKDIVN_HDIVN_2:
			hdiv = 2;
			break;

		case S3C2440_CLKDIVN_HDIVN_4_8:
			hdiv = (camdiv & S3C2440_CAMDIVN_HCLK4_HALF) ? 8: 4;
			break;

		case S3C2440_CLKDIVN_HDIVN_3_6:
			hdiv = (camdiv & S3C2440_CAMDIVN_HCLK3_HALF) ? 6: 3;
			break;
	}

    //return((clk_power->CLKDIVN & 0x1) ? get_HCLK()/2 : get_HCLK());
	return get_FCLK() / hdiv / ((clkdiv & S3C2440_CLKDIVN_PDIVN) ? 2: 1);
}

/* return UCLK frequency */
unsigned long get_UCLK(void)
{
    return(get_PLLCLK(UPLL));
}
