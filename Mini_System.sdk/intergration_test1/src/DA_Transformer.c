/*
 * DA_Transformer.c
 *
 *  Created on: 2021��5��30��
 *      Author: Unique MR
 */
#include "include.h"
#include "waves.h"

u16 volt,lastvolt;
int edge = 0;

void DA_Transformer(int control)
{
	//���SPI�ж�״̬�Ĵ���
	Xil_Out32(XPAR_AXI_QUAD_SPI_0_BASEADDR+XSP_IISR_OFFSET,Xil_In32(XPAR_AXI_QUAD_SPI_0_BASEADDR+XSP_IISR_OFFSET));
	//дINTC�ж���Ӧ�Ĵ���
	Xil_Out32(XPAR_AXI_INTC_0_BASEADDR+XIN_IAR_OFFSET,Xil_In32(XPAR_AXI_INTC_0_BASEADDR+XIN_ISR_OFFSET));
    if(control == 8192)
    {
	    sawtooth_wave(&volt);
    }
    else
    {
        triangle_wave(&volt,&edge);
    }
}
