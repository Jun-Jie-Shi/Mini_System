/*
 * SPI_DA_IO.c
 *
 *  Created on: 2021��5��26��
 *      Author: win10
 */
#include"xil_io.h"
#include"xintc_l.h"
#include"xspi_l.h"
void My_ISR()__attribute__((interrupt_handler));
u16 volt,lastvolt;
int main()
{
	//�趨SPIΪ���豸��CPOL=1��CPHA=0���Զ���ʽ����λ���ȴ���
	Xil_Out32(XPAR_AXI_QUAD_SPI_0_BASEADDR+XSP_CR_OFFSET,XSP_CR_ENABLE_MASK|XSP_CR_MASTER_MODE_MASK|XSP_CR_CLK_POLARITY_MASK);
	//�趨SSR�Ĵ���
	Xil_Out32(XPAR_AXI_QUAD_SPI_0_BASEADDR+XSP_SSR_OFFSET,0xfffffffe);
	//����SPI���ͼĴ����ж�
	Xil_Out32(XPAR_AXI_QUAD_SPI_0_BASEADDR+XSP_IIER_OFFSET,XSP_INTR_TX_EMPTY_MASK);
	Xil_Out32(XPAR_AXI_QUAD_SPI_0_BASEADDR+XSP_DGIER_OFFSET,XSP_GINTR_ENABLE_MASK);
	//�жϿ�����intr0�ж�Դʹ��
	Xil_Out32(XPAR_AXI_INTC_0_BASEADDR+XIN_IER_OFFSET,XPAR_AXI_QUAD_SPI_0_IP2INTC_IRPT_MASK);
	Xil_Out32(XPAR_AXI_INTC_0_BASEADDR+XIN_MER_OFFSET,XIN_INT_MASTER_ENABLE_MASK|XIN_INT_HARDWARE_ENABLE_MASK);
	//�������ж�ʹ��
	microblaze_enable_interrupts();
	//�������䣬��������0
	Xil_Out16(XPAR_AXI_QUAD_SPI_0_BASEADDR+XSP_DTR_OFFSET,0);//����SPI���䣬����ʱ�Ӻ�Ƭѡ�ź�
	while(1);
}

void My_ISR(){
	//���SPI�ж�״̬�Ĵ���
	Xil_Out32(XPAR_AXI_QUAD_SPI_0_BASEADDR+XSP_IISR_OFFSET,Xil_In32(XPAR_AXI_QUAD_SPI_0_BASEADDR+XSP_IISR_OFFSET));
	//дINTC�ж���Ӧ�Ĵ���
	Xil_Out32(XPAR_AXI_INTC_0_BASEADDR+XIN_IAR_OFFSET,Xil_In32(XPAR_AXI_INTC_0_BASEADDR+XIN_ISR_OFFSET));
	volt++;
	Xil_Out16(XPAR_AXI_QUAD_SPI_0_BASEADDR+XSP_DTR_OFFSET,volt&0xfff);//����SPI���䣬����ʱ�Ӻ�Ƭѡ�ź�
}
