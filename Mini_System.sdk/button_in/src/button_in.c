/*
 * button_in.c
 *
 *  Created on: 2021��5��18��
 *      Author: win10
 */
#include"stdio.h"
#include"xil_io.h"
#include"xgpio_l.h"
int main()
{
	char button;
	Xil_Out8(XPAR_AXI_GPIO_2_BASEADDR+XGPIO_TRI_OFFSET,0x1f);						//����ͨ����5λ����
	while(1)
		while((Xil_In8(XPAR_AXI_GPIO_2_BASEADDR+XGPIO_DATA_OFFSET)&0x1f)!=0)		//�ж��Ƿ��а�������
		{
			button = Xil_In8(XPAR_AXI_GPIO_2_BASEADDR+XGPIO_DATA_OFFSET)&0x1f;		//��ȡ����ֵ
			while ((Xil_In8(XPAR_AXI_GPIO_2_BASEADDR+XGPIO_DATA_OFFSET)&0x1f)!=0);	//�ȴ������ͷ�
			xil_printf("The pushed button's code is 0x%x\n",button);
		}
}
