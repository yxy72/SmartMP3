#ifndef _UART_H_
#define	 _UART_H_

extern void Uart_init();
extern void uart_rx();
extern void SendASC(unsigned char d);
extern void SendOrder(unsigned char *str);
extern void Uart2_init();
extern void Uart2_SendASC(unsigned char date);
extern void Uart2_SendOrder(unsigned char *p);
#endif
