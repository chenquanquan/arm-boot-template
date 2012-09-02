/*
 * boot_init.c
 * changed from GTStudio, board/GTStudio/boot_init.c
 */

#include <s3c2440.h>
#include <s3c24x0.h>

#define BUSY				1

#define NAND_SECTOR_SIZE	512
#define NAND_BLOCK_MASK		(NAND_SECTOR_SIZE - 1)

#define NAND_SECTOR_SIZE_LP	2048
#define NAND_BLOCK_MASK_LP	(NAND_SECTOR_SIZE_LP - 1)

/* pubilc functions */
void nand_init_ll(void);
void nand_read_ll(unsigned char *buf, unsigned long start_addr, int size);
char NF_ReadID(void);

/* private functions */
static void nand_reset(void);
static void wait_idle(void);
static void nand_select_chip(void);
static void nand_deselect_chip(void);
static void write_cmd(int cmd);
static void write_addr(unsigned int addr);
static unsigned char read_data(void);

/* rest NAND Flash */
static void nand_reset(void)
{
	nand_select_chip();
	write_cmd(0xff);	//rest command
	wait_idle();
	nand_deselect_chip();
}

/* wait NAND Flash ready */
static void wait_idle(void)
{
	int i;
	S3C2440_NAND * s3c2440nand = (S3C2440_NAND *)0x4e000000;
	volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFSTAT;

	while (!(*p & BUSY))
		for (i = 0; i < 10; i++);
}

/* select NAND Flash */
static void nand_select_chip(void)
{
	int i;
	S3C2440_NAND * s3c2440nand = (S3C2440_NAND *)0x4e000000;

	s3c2440nand->NFCONT &= ~(1 << 1);
	for (i = 0; i < 10; i++);
}

/* deselect NAND Flash */
static void nand_deselect_chip(void)
{
	S3C2440_NAND * s3c2440nand = (S3C2440_NAND *)0x4e000000;

	s3c2440nand->NFCONT |= (1 << 1);
}

/* write command to chip */
static void write_cmd(int cmd)
{
	S3C2440_NAND * s3c2440nand = (S3C2440_NAND *)0x4e000000;

	volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFCMD;
	*p = cmd;
}

/* write address to chip */
static void write_addr(unsigned int addr)
{
	int i;
	S3C2440_NAND * s3c2440nand = (S3C2440_NAND *)0x4e000000;
	volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFADDR;

	*p = addr & 0xff;
	for (i = 0; i < 10; i++);

	*p = (addr >> 9) & 0xff;
	for (i = 0; i < 10; i++);

	*p = (addr >> 17) & 0xff;
	for (i = 0; i < 10; i++);

	*p = (addr >> 25) & 0xff;
	for (i = 0; i < 10; i++);
}

/* send address to NAND Flash */
static void write_addr_lp(unsigned int addr)
{
	int i;
	S3C2440_NAND * s3c2440nand = (S3C2440_NAND *)0x4e000000;
	volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFADDR;
	int col, page;

	col = addr & NAND_BLOCK_MASK_LP;
	page = addr / NAND_SECTOR_SIZE_LP;

	*p = col & 0xff;	/* Column Address A0~A7 */
	for (i = 0; i < 10; i++);

	*p = (col >> 8) & 0x0f;	/* Column Address A8~A11 */
	for (i = 0; i < 10; i++);

	*p = page & 0xff;	/* Row Address A12~A19 */
	for (i = 0; i < 10; i++);

	*p = (page >> 8) & 0xff;	/* Row Address A20~A27 */
	for (i = 0; i < 10; i++);

	*p = (page >> 16) & 0x01;	/* Row Address A28 */
	for (i = 0; i < 10; i++);
}

/* read data */
static unsigned char read_data(void)
{
	S3C2440_NAND * s3c2440nand = (S3C2440_NAND *)0x4e000000;
	volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFDATA;

	return *p;
}

char NF_ReadID(void)
{
	char	pMID;
	char	pDID;
	char	nBuff;
	char	n4thcycle;

	S3C2440_NAND * s3c2440nand = (S3C2440_NAND *)0x4e000000;

	nand_select_chip();
	s3c2440nand->NFSTAT = (1 << 2);
	write_cmd(0x90);
	write_addr(0x00);
	wait_idle();

	pMID	= read_data();
	pDID	= read_data();

	nBuff	= read_data();
	n4thcycle	= read_data();
	nand_deselect_chip();

	nBuff = pMID = pDID = n4thcycle;
	pMID = nBuff;

	return (pDID);
}

/* init NAND Flash */
void nand_init_ll(void)
{
	S3C2440_NAND * s3c2440nand = (S3C2440_NAND *)0x4e000000;
	
#define TACLS	0
#define TWRPH0	3
#define TWRPH1	0

	/* set NAND Flash clock */
	s3c2440nand->NFCONF = (TACLS << 12) | (TWRPH0 << 8) | (TWRPH1 << 4);
	/* enable NAND Flash */
	s3c2440nand->NFCONT = (1 << 4) | (1 << 1) | (1 << 0);
	nand_reset();
}

/* read NAND Flash functions */
void nand_read_ll(unsigned char *buf, unsigned long start_addr, int size)
{
	int i, j;

	if ((start_addr & NAND_BLOCK_MASK) || (size & NAND_BLOCK_MASK)) {
		return;
	}

	nand_select_chip();

	for (i = start_addr; i < (start_addr + size);) {
		/* read0 command */
		write_cmd(0);
		/*write address */
		write_addr(i);
		wait_idle();

		for (j = 0; j < NAND_SECTOR_SIZE; j++, i++) {
			*buf = read_data();
			buf++;
		}
	}

	nand_deselect_chip();
}

/* read NAND Flash a Large Page */
void nand_read_ll_lp(unsigned char *buf, unsigned long start_addr, int size)
{
	int i, j;

	if ((start_addr & NAND_BLOCK_MASK_LP) || (size & NAND_BLOCK_MASK_LP))
		return;

	nand_select_chip();

	for (i = start_addr; i < (start_addr + size);) {
		/* write read0 command */
		write_cmd(0);
		/*write Address */
		write_addr_lp(i);
		write_cmd(0x30);
		wait_idle();

		for (j = 0; j < NAND_SECTOR_SIZE_LP; i++, j++) {
			*buf = read_data();
			buf++;
		}
	}

	nand_deselect_chip();
}

/* check boot from */
int boot_from_flash(void)
{
	volatile unsigned int *pdw = (volatile unsigned int *)0;
	unsigned int tmp;

	tmp = *pdw;
	*pdw = 0x12345678;

	if (*pdw != 0x12345678) {
		return 1;
	} else {
		*pdw = tmp;
		return 0;
	}
}

int copy_code_to_ram(unsigned long start_addr, unsigned char *buf, int size)
{
	unsigned int *pdwDest;
	unsigned int *pdwSrc;
	int i;

	if (boot_from_flash()) {
		/* boot from NOR Flash */
		pdwDest	= (unsigned int *)buf;
		pdwSrc	= (unsigned int *)start_addr;

		for (i = 0; i < size / 4; i++)
			pdwDest[i] = pdwSrc[i];

		return 0;
	} else {
		/* boot from NAND Flash */
		nand_init_ll();
		nand_read_ll_lp(buf, start_addr, (size + NAND_BLOCK_MASK_LP) & ~(NAND_BLOCK_MASK_LP));

		return 0;
	}
}

static inline void delay(unsigned long loops)
{
	__asm__ volatile ("1:\n"
			"subs %0, %1, #1\n"
			"bne 1b":"=r"(loops):"0"(loops));
}

#define S3C2440_MPLL_400MHZ	((0X5C << 12) | (0X01 << 4) | (0X01))
#define S3C2440_UPLL_48MHZ	((0X38 << 12) | (0X02 << 4) | (0X02))
#define S3C2440_CLKDIV		0X05	/* FCLK:HCLK:PCLK = 1:4:8, UCLK=UPLL */
void clock_init(void)
{
	S3C24X0_CLOCK_POWER *clk_power = (S3C24X0_CLOCK_POWER *)0x4c000000;

	/* FCLK:HCLK:PCLK = 1:4:8 */
	clk_power->CLKDIVN = S3C2440_CLKDIV;

	/* change the bus mode */
	__asm__(	"mrc	p15, 0, r1, c1, c0, 0\n"	/* read ctrl register */
				"orr	r1, r1, #0xc0000000\n"	/* Asynchronous */
				"mcr	p15, 0, r1, c1, c0, 0\n"	/* write ctrl register */
				:::"r1"
		   );

	/* to reduce PLL lock time, adjust the LOCKTIME register */
	clk_power->LOCKTIME = 0xffffff;

	/* configure MPLL */
	//clk_power->MPLLCON = S3C2440_MPLL_400MHZ;
	clk_power->UPLLCON = S3C2440_UPLL_48MHZ;

	/* delay between MPLL and UPLL */
	delay(4000);

	/* configure UPLL */
	//clk_power->UPLLCON = S3C2440_UPLL_48MHZ;
	clk_power->MPLLCON = S3C2440_MPLL_400MHZ;

	/*delay between MPLL and UPLL */
	delay(8000);
}

int board_init(void)
{
	S3C24X0_GPIO * const gpio = S3C24X0_GetBase_GPIO();

	/* set up the I/O ports */
	gpio->GPACON = 0x007FFFFF;
	/* gpio->GPBCON = 0x00055555; */
	/* gpio->GPBUP = 0x000007FF; */
	gpio->GPCCON = 0xAAAAAAAA;
	gpio->GPCUP = 0x0000FFFF;
	gpio->GPDCON = 0xAAAAAAAA;
	gpio->GPDUP = 0x0000FFFF;
	gpio->GPECON = 0xAAAAAAAA;
	gpio->GPEUP = 0x0000FFFF;
	gpio->GPFCON = 0x000055AA;
	gpio->GPFUP = 0x000000FF;
	gpio->GPGCON = 0xFF94FFBA;
	gpio->GPGUP = 0x0000FFEF;
	gpio->GPGDAT = (gpio->GPGDAT & ((~(1<<4)) | (1<<4))) ;
	gpio->GPHCON = 0x002AFAAA;
	gpio->GPHUP = 0x000007FF;
	gpio->GPJCON = 0x02aaaaaa;
	gpio->GPJUP = 0x00001fff;

	return 0;
}
