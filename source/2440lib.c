#include <2440lib.h>
#include "2440addr.h"

 
void inline ClearPending(int bit)
{
	register int i;

	rSRCPND = bit;
	rINTPND = bit;
	i = rINTPND;
}

void inline ClearSubPending(int bit)
{
	register int i;
	
	rSUBSRCPND = bit;	
	i = rINTPND;
}                       

//Wait until rINTPND is changed for the case that the ISR is very short.



void irq_enable_botton(void)
{
	serial_puts("enable botton interrupt\n");

	/* configure botton I/O
	 * External interrupt will be falling edge triggered.
	 * */
	rEXTINT0 = 0x22222222;    // EINT[7:0]
	rEXTINT1 = 0x22222222;    // EINT[15:8]
	rEXTINT2 = 0x22222222;    // EINT[23:16]


	rGPGCON = rGPGCON & (~((3<<22)|(3<<6))) | ((2<<22)|(2<<6));	//GPG11,3 set EINT

	rGPFCON = rGPFCON & (~((3<<4)|(3<<0))) | ((2<<4)|(2<<0));	//GPF2,0 set EINT



	rEXTINT0 &= ~(7|(7<<8));	
	rEXTINT0 |= (0|(0<<8));	//set eint0,2 falling edge int
	rEXTINT1 &= ~(7<<12);
	rEXTINT1 |= (0<<12);	//set eint11 falling edge int
	rEXTINT2 &= ~(0xf<<12);
	rEXTINT2 |= (0<<12);	//set eint19 falling edge int

	rEINTPEND |= (1<<11)|(1<<19);		//clear eint 11,19
	rEINTMASK &= ~((1<<11)|(1<<19));	//enable eint11,19
	ClearPending(BIT_EINT0|BIT_EINT2|BIT_EINT8_23);
	/* pISR_EINT0 = pISR_EINT2 = pISR_EINT8_23 = (U32)Key_ISR; */
	EnableIrq(BIT_EINT0|BIT_EINT2|BIT_EINT8_23);	



}
