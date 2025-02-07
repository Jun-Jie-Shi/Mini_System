/*
 * triangle_wave.cpp
 *
 *  Created on: 2021年5月31日
 *      Author: Unique MR
 */
#include "include.hpp"

const int counter2_initial = 4095;

void triangle_wave(int &volt, int &edge,int &counter,int &freq_change,int &volt_set)
{
	const int counter_max = counter2_initial * 1000 / freq_change;
	if(counter >= counter_max)
		edge = 1;
	if(counter <= 0)
		edge = 0;
	if(edge == 0)
		counter++;
	if(edge == 1)
		counter--;
	volt = 4095 * volt_set * counter / (counter_max*333);
	Xil_Out16(XPAR_AXI_QUAD_SPI_0_BASEADDR+XSP_DTR_OFFSET,volt&0xfff);//启动SPI传输，产生时钟和片选信号
}
