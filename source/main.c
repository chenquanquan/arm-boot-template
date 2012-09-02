/* main.c
 * interrupt template.
 */
#include "2440addr.h"
#include "2440lib.h"

extern void _start_kernel(void);
extern void enable_interrupts(void);

void inline delay(int a)  
{
	int i,j;

	for(i=0;i<a;i++)
		for(j=0;j<100;j++);

}

extern int serial_init(void);
extern int serial_putc(const char c);
extern void clock_init(void);
extern int board_init(void);

int main(void)
{
	int i;
	int light;

	/* set I/O control register */
	rGPBCON = (0x1<<10)|(0x1<<12)|(0x1<<14)|(0x1<<16);
	/* the pull up function is disable */
	rGPBUP  = 0x7ff;

	clock_init();
	board_init();
	serial_init();
	enable_interrupts();
	irq_enable_botton();

	while(1) {
		/* initialize the first LED */
		light = 0x10;
		light = light<<1;
		rGPBDAT = ~light;
		delay(5000);

		serial_putc('c');

		for (i=0;i<3;i++) {
			light = light<<1;
			rGPBDAT = ~light;
			delay(5000);
		}
		//_start_kernel();
	} 

	return 0;
}
