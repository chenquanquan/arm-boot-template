/*
 * Nand flash interface of s3c2440
 * changed from kernel 2.6.13, driver/mtd/nand/s3c2440.c
 */
#include <s3c2440.h>

#define S3C2440_NFSTAT_READY		(1 << 0)
#define S3C2440_NFCONT_nFCE		(1 << 1)

/* select chip, for s3c2440 */
static void s3c2440_nand_select_chip(struct mtd_info *mtd, int chip)
{
	S3C2440_NAND * const s3c2440nand = S3C2440_GetBase_NAND();

	if (chip == -1)
		s3c2440nand->NFCONT |= S3C2440_NFCONT_nFCE;
	else
		s3c2440nand->NFCONT &= ~S3C2440_NFCONT_nFCE;
}

/* command and control functions */
static void s3c2440_nand_hwcontrol(struct mtd_info *mtd, int cmd)
{
	S3C2440_NAND * const s3c2440nand = S3C2440_GetBase_NAND();
	struct nand_chip *chip = mtd->priv;

	switch (cmd) {
		case NAND_CTL_SETNCE:
		case NAND_CTL_CLRNCE:
			printf("%s: called for NCE\n", __FUNCTION__);
			break;

		case NAND_CTL_SETCLE:
			chip->IO_ADDR_W = (void *)&s3c2440nand->NFCMD;
			break;

		case NAND_CTL_SETALE:
			chip->IO_ADDR_W = (void *)&s3c2440nand->NFADDR;
			break;

		/* NAND_CTL_CLRCLR: */
		/* NAND_CTL_CLRALE: */
		default:
			chip->IO_ADDR_W = (void *)&s3c2440nand->NFDATA;
			break;
	}
}

/* s3c2440_nand_devready()
 *
 * return 0 if the nand if busy, 1 if it is ready
 */
static int s3c2440_nand_devready(struct mtd_into *mtd)
{
	S3C2440_NAND * const s3c2440nand = S3C2440_GetBase_NAND();

	return (s3c2440nand->NFSTAT & S3C2440_NFSTAT_READY);
}

/*
 * Nand flash hardware initialization:
 * Set the timing, enable NAND flash controller
 */
static void s3c2440_nand_inithw(void)
{
	S3C2440_NAND * const s3c2440nand = S3C2440_GetBase_NAND();

#define TACLS	0
#define TWRPH0	4
#define TWRPH1	2

	/* Set flash memory timing */
	s3c2440nand->NFCONF = (TACLS << 12) | (TWRPH0 << 8) | (TWRPH1 << 4);
	/* Initialize ECC, enable chip select, NAND flash controller enable */
	s3c2440nand->NFCONT = (1 << 4) | (0 << 1) | (1 << 0);
}

/*
 * called by driver/nand/nand.c, initialize the interface of nand flash
 */
void board_nand_init(struct nand_chip *chip)
{
	S3C2440_NAND * const s3c2440nand = S3C2440_GetBase_NAND();

	s3c2440_nand_inithw();

	chip->IO_ADDR_R		= (void *)&s3c2440nand->NFDATA;
	chip->IO_ADDR_W		= (void *)&s3c2440nand->NFDATA;;
	chip->hwcontrol		= s3c2440_nand_hwcontrol;
	chip->dev_ready		= s3c2440_nand_devready;
	chip->select_chip	= s3c2440_nand_select_chip;
	chip->options		= 0;
	chip->eccmode		= NAND_ECC_SOFT;
}
