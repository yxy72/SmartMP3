#ifndef	__INFRARED_H
#define	__INFRARED_H
#define uchar unsigned char
#define uint unsigned int	//����ת��

//************* ����ң�� ***************
extern bit irpro_ok,irok;
extern uchar IRcord[];
extern uchar irdata[];
extern uchar irtime;					//������ȫ�ֱ���

void Ir_work(void);
void Ircordpro(void);
void delay(uint z);		//��ʱ
void IRInit();		//����+��ʱ����ʼ��


				
#endif