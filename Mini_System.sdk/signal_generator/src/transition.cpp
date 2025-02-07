/*
 * transition.cpp
 *
 *  Created on: 2021年6月7日
 *      Author: uniqueMR
 */
#include "include.hpp"

const int segcode_change[10] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
const int segcode_p[4] = {0xa0,0x83,0xc6,0xa1};
void transition(unsigned short control,int &volt_set,int &freq_change,int *segcode)
{
	//生成幅度调节信号和频率控制信号
	int volt_set_control = (control >> 2)&0x3f;
	int freq_change_control = (control >> 8)&0x3f;
	volt_set /= (volt_set_control+1);

	int freq_change_regulation = 0;//控制频率改变的方向，即增加频率还是减小频率
	if(((freq_change_control >> 5)&0x1) == 1)
		freq_change_regulation = 1;
	else freq_change_regulation = 0;

	int freq_change_value = freq_change_control&0x1f;//控制频率改变的幅度
	if(freq_change_regulation == 0)
		freq_change *= (freq_change_value + 1);
	else
		freq_change /= (freq_change_value + 1);

	//生成波形选择信号·
	int alter = control&0x3;

	//生成需要现实的段码
	int volt_0 = volt_set % 10;
	int volt_1 = (volt_set / 10) % 10;
	int volt_2 = volt_set / 100;

	int freq_0 = freq_change % 10;
	int freq_1 = (freq_change / 10) % 10;
	int freq_2 = (freq_change / 100) % 10;
	int freq_3 = freq_change / 1000;

	segcode[7] = segcode_change[freq_0];
	segcode[6] = segcode_change[freq_1];
	segcode[5] = segcode_change[freq_2];
	segcode[4] = segcode_change[freq_3];
	segcode[3] = segcode_change[volt_0];
	segcode[2] = segcode_change[volt_1];
	segcode[1] = segcode_change[volt_2]&0x7f;
	segcode[0] = segcode_p[alter];

	return;
}
