#ifndef __SERIAL_H__
#define __SERIAL_H__


void serial_setbrg (void);
int serial_init (void);
int serial_getc (void);
void serial_putc (const char c);
int serial_tstc (void);
void serial_puts (const char *s);

#endif /* __SERIAL_H__ */
