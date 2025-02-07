/*
 * seg_timer.c
 *
 *  Created on: 2021年5月30日
 *      Author: Unique MR
 */
/*
 * seg_timer.c
 *
 *  Created on: 2021年5月29日
 *      Author: Unique MR
 */
#include "xil_io.h"
#include "stdio.h"
#include "xgpio_l.h"
#include "xtmrctr_l.h"
#include "xintc_l.h"
#define RESET_VALUE 10000
void Seg_TimerCounterHandler();
void My_ISR() __attribute__ ((interrupt_handler));
char segcode[8] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x83,0xf8};
short pos = 0xff7f;
int i = 0;
int main()
{
    Xil_Out32(XPAR_AXI_GPIO_1_BASEADDR+XGPIO_TRI_OFFSET,0X0);//设定为输出方式
    Xil_Out32(XPAR_AXI_GPIO_1_BASEADDR+XGPIO_TRI2_OFFSET,0X0);//设定为输出方式
    Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR+XTC_TCSR_OFFSET,Xil_In32(XPAR_AXI_TIMER_0_BASEADDR+XTC_TCSR_OFFSET)&~XTC_CSR_ENABLE_TMR_MASK);//写TCSR，停止计数器
    Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR+XTC_TLR_OFFSET,RESET_VALUE);//写TLR预置计数值
    Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR+XTC_TCSR_OFFSET,
        Xil_In32(XPAR_AXI_TIMER_0_BASEADDR+XTC_TCSR_OFFSET)|XTC_CSR_LOAD_MASK);//装载计数初值
    Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR+XTC_TCSR_OFFSET,
        (Xil_In32(XPAR_AXI_TIMER_0_BASEADDR+XTC_TCSR_OFFSET)&~XTC_CSR_LOAD_MASK)|XTC_CSR_ENABLE_TMR_MASK|XTC_CSR_AUTO_RELOAD_MASK|XTC_CSR_ENABLE_INT_MASK|XTC_CSR_DOWN_COUNT_MASK);
    //开始计时运行，自动装载，允许中断，减计数
    Xil_Out32(XPAR_AXI_INTC_0_BASEADDR+XIN_IER_OFFSET,XPAR_AXI_TIMER_0_INTERRUPT_MASK);
    //对中断控制器进行中断使能
    Xil_Out32(XPAR_AXI_INTC_0_BASEADDR+XIN_MER_OFFSET,XIN_INT_MASTER_ENABLE_MASK|XIN_INT_HARDWARE_ENABLE_MASK);
    microblaze_enable_interrupts();
    //允许微处理器接受中断
    while(1);
    return 0;
}
void My_ISR()
{
    int status;
    status = Xil_In32(XPAR_AXI_INTC_0_BASEADDR+XIN_ISR_OFFSET);//读取ISR
    if(status&XPAR_AXI_TIMER_0_INTERRUPT_MASK) //== XPAR_AXI_TIMER_0_INTERRUPT_MASK)
        Seg_TimerCounterHandler();
    Xil_Out32(XPAR_AXI_INTC_0_BASEADDR+XIN_IAR_OFFSET,status);
}
void Seg_TimerCounterHandler()
{
    Xil_Out8(XPAR_AXI_GPIO_1_BASEADDR+XGPIO_DATA2_OFFSET,segcode[i]);
    Xil_Out8(XPAR_AXI_GPIO_1_BASEADDR+XGPIO_DATA_OFFSET,pos);
    pos=pos>>1;
    i++;
    if(i == 8)
    {
        i = 0;
        pos = 0xff7f;
    }
    Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR+XTC_TCSR_OFFSET,Xil_In32(XPAR_AXI_TIMER_0_BASEADDR+XTC_TCSR_OFFSET));//清除中断
}
