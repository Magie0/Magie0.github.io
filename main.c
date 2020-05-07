//
//  main.c
//  冯诺依曼式计算机CPU模拟器
//
//  Created by 陆泽意 on 2020/5/4.
//  Copyright © 2020 陆泽意. All rights reserved.
//

#include <stdio.h>
#include <string.h>

typedef struct inst
{
    unsigned char code; // 指令
    //unsigned char cond; // 执行该指令的条件
    short p1, p2 ,p3;// 参数1、2,3
    //short ax1,ax2,ax3,ax4,ax5,ax6,ax7,ax8;
} inst_t;
typedef signed short data_t; // 我们操作的就是16位数
//typedef unsigned short data_t;

typedef struct vm_state
{
    int ip; // 指令ptr
    int flag; // 记录最后判断的标志
    inst_t *code; // 代码段地址 从地址0开始
    data_t *data; // 数据段地址 从地址16384开始
    short ax[9];
} vm_state_t;

int Memory[32767];
#define IADD    1 // 加法
#define ISUB    2 // 减法
#define IMUL    3 // 乘法
#define IDIV    4 // 除法
#define ICMP    5 // 判断
#define IJMP    6 // 跳转
#define IMOV    7 // 赋值
#define IGIV    8 // 赋值
#define ISED    9 // 赋值
#define ILD     10 // 加载一个立即数
#define IPUT    11 // 输入
#define IOUT    12 // 输出
#define ILOG    13 // 逻辑指令
#define ILOV    14 // 逻辑指令
#define ILON    15 // 逻辑指令
#define ISTOP   255 // 停机

#define FNA     0 // 比较后相等为0
#define FEQ     1 // 寄存器1中的大 置为1
#define FNE     -1 //  立即数大   置为-1

void execute(vm_state_t *state)
{
    for (;;) // 执行到挂起为止
    {
        inst_t current = state->code[state->ip];
        state->ip++; // 取出指令以后自动ip后移
        if (current.cond != FNA && current.cond != state->flag)
            // 该指令要求的状态不符合当前状态，略过
            continue;
        switch (current.code)
        {
            case IADD:
                // 将p1指向的数据加上p2指向的数据
                state->data[current.p3]
                state->ax[state->data[current.p3]] = state->data[current.p1] + state->data[current.p2];
                break;
            case ISUB:
                state->ax[state->data[current.p3]] = state->data[current.p1] - state->data[current.p2];
                break;
            case IMUL:
                state->ax[state->data[current.p3]] = state->data[current.p1] * state->data[current.p2];
                break;
            case IDIV:
                state->ax[state->data[current.p3]] = state->data[current.p1] / state->data[current.p2];
                break;
            case ICMP:
                // 比较p1指向的数据和p2指向的数据
                if (state->data[current.p1] == state->data[current.p2])
                    state->flag = FNA;
                if (state->data[current.p1] > state->data[current.p2])
                    state->flag = FEQ;
                if (state->data[current.p1] > state->data[current.p2])
                    state->flag = FNE;
                break;
            case IJMP:
                // 跳转，指令根据p2(立即数)进行偏移
                state->ip += current.p2;
                break;
            case IMOV:
                // 把寄存器1到4中的数传送到寄存器5到8所指向的内存单元
                Memory[state->data[current.p2]] = state->data[current.p1];
                //state->data[current.p1] = state->data[current.p2];
                break;
            case IGIV:
                //把寄存器5到8所指向的内存单元中的数传送到寄存器1到4中
                state->ax[state->data[current.p2]] = Memory[state->data[current.p1]];
            /*case ISTIP:
                // 把IP保存到p1指向的数据
                state->data[current.p1] = (data_t) state->ip;
                break;
            case ILDIP:
                // 将IP设置为p1指向的数据，该指令会导致跳转
                state->ip = state->data[current.p1];
                break;*/
            case ISED:
                //把立即数传送给寄存器1到8；
                state->ax[state->data[current.p3]] = state->data[current.p1];
            case ILD:
                // 将立即数p2加载到p1指向的数据
                state->data[current.p1] = current.p2;
                //printf("ax%d=%d\n",current.p1,state->data[current.p1]);
                break;
            case ILOG:
                if(state->data[current.p1]>0&&state->data[current.p2]>0)
                    state->ax[state->data[current.p3]] = 1;
                else
                    state->ax[state->data[current.p3]] = 0;
            case ILOG:
            if(state->data[current.p1]=0&&state->data[current.p2]=0)
                state->ax[state->data[current.p3]] = 0;
            else
                state->ax[state->data[current.p3]] = 1;
            case IPUT:
                scanf("in:\n");
                scanf("%d",state->ax[state->data[current.p3]]);
            case IOUT:
                // 输出寄存器ax[n]中的数值
                printf("out: ")
                printf("%d\n",state->ax[state->data[current.p3]]);
                break;
            case ISTOP:
                //停机
                return;
        }
    }
}

inst_t sample_code[] =
{
    { ILD,   FNA,  2, 101 ,2},
    { ILD,   FNA,  3, 1 },
    { ILD,   FNA,  1, 1 },
    { ILD,   FNA,  0, 0 },
    { ICMP,  FNA,  1, 2 },
    { IJMP,  FEQ,  3, 0 },
    { IADD,  FNA,  0, 1 },
    { IADD,  FNA,  1, 3 },
    { IJMP,  FNA, -5, 0 },
    { IOUT,  FNA,  0, 0 },
    { ISTOP, FNA,  0, 0 }
};
data_t data_seg[16];

int main(int argn, char *argv[])
{
    vm_state_t state;
    inst_t inst;
    memset(&state, 0, sizeof(state));
    state.ip=0;
    state.flag=0;
    state.code = sample_code;
    state.data = data_seg;
    state.ax[0]=state.ax[1]=state.ax[2]=state.ax[3]=state.ax[4]=state.ax[5]=state.ax[6]=state.ax[7]=0;
    //inst.ax1=inst.ax2=inst.ax3=inst.ax4=inst.ax5=inst.ax6=inst.ax7=inst.ax8=0;
    execute(&state);
}
