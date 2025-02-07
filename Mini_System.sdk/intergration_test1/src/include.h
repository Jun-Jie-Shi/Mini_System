/*
 * include.h
 *
 *  Created on: 2021��5��30��
 *      Author: Unique MR
 */

#define SRC_INCLUDE_H_



#include "xil_io.h"
#include "stdio.h"
#include "xgpio_l.h"
#include "xtmrctr_l.h"
#include "xintc_l.h"
#include"xspi_l.h"

#define RESET_VALUE 10000

void SwitchHandler();
void Seg_TimerCounterHandler();
void DA_Transformer(int control);
void My_ISR() __attribute__ ((interrupt_handler));
