/*
 * led_out.c
 *
 *  Created on: 2021��5��18��
 *      Author: win10
 */
#include"stdio.h"
#include"xil_io.h"
#include"xgpio.h"
int main()
{
	unsigned short led;
	unsigned char byte;
	Xil_Out16(XPAR_AXI_GPIO_0_BASEADDR+XGPIO_TRI2_OFFSET,0x0);				//����ͨ����16λ���
	while(1)
	{
		xil_printf("input hexadecimal number to be displayed:\r\n");
		led = 0;											//��ʼ������ʮ��������
		while(1)
		{
			byte=inbyte();									//��ȡConsole�����ַ�
			if(byte == 0x0d)								//�ж��Ƿ��ǻس�
			{
				break;										//���Իس�
			}
			else{
				if(byte>='a')								//�ж�ʮ�������ַ��Ƿ�Ϊa~f
					byte = byte-0x57;						//�ַ�a~fת��Ϊʮ������ֵ
				else if(byte>='A')							//�ж�A~Fת��Ϊʮ������ֵ
					byte = byte-0x37;
				else
					byte = byte - 0x30;						//�ַ�0~9ת��Ϊʮ������ֵ
				led = (led<<4)+byte;						//�����ַ��ϲ�Ϊһ��ʮ��������
			}
		}
		Xil_Out16(XPAR_AXI_GPIO_0_BASEADDR+XGPIO_DATA2_OFFSET,led);			//���ʮ����������LED��
	}
}
