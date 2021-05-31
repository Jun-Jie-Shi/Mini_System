/*
 * sawtooth_wave.c
 *
 *  Created on: 2021年5月31日
 *      Author: Unique MR
 */
#include "include.h"

void sawtooth_wave(int volt)
{
	volt++;
	Xil_Out16(XPAR_AXI_QUAD_SPI_0_BASEADDR+XSP_DTR_OFFSET,volt&0xfff);//启动SPI传输，产生时钟和片选信号
}
