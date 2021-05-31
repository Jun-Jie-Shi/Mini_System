/*
 * switch_in.c
 *
 *  Created on: 2021��5��18��
 *      Author: win10
 */
#include"stdio.h"
#include"xil_io.h"
#include"xgpio_l.h"
int main()
{
	unsigned short last_sw,current_sw;
	Xil_Out16(XPAR_AXI_GPIO_0_BASEADDR+XGPIO_TRI_OFFSET,0xffff);					//����ͨ����16λ����
	while(1)
	{
		last_sw=current_sw;							//����ǰһ����״̬
		current_sw=Xil_In16(XPAR_AXI_GPIO_0_BASEADDR+XGPIO_DATA_OFFSET)&0xffff;		//��ȡ��ǰ����ֵ
		if(last_sw!=current_sw)						//�ж�ǰ��״̬�Ƿ�һ��
			xil_printf("The switches'code is 0x%4x\n",current_sw);
	}
}
