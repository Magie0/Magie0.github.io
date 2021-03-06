//
//  main.m
//  执行指令
//
//  Created by 陆泽意 on 2020/5/5.
//  Copyright © 2020 陆泽意. All rights reserved.
//
//executiveInstruction
#import <Foundation/Foundation.h>

int Memory[32767];
#define IADD    1 // 加法
#define ISUB    2 // 减法
#define IMUL    3 // 乘法
#define IDIV    4 // 除法
#define ICMP    5 // 判断
#define IJMP    6 // 跳转
#define IMOV    7 // 赋值
#define IGIV    8 // 赋值
#define ILD     9 // 加载一个立即数
#define IPUT    10 // 输入
#define IOUT    11 // 输出
#define ILOG    12 //逻辑指令
#define ILOV    13 //逻辑指令
#define ISTOP   255 //  停机

#define FNA     0 //  比较后相等为0
#define FEQ     1 //   寄存器1中的大 置为1
#define FNE     -1 //  立即数大   置为-1

void execute(vm_state_t *state)
{
    for (;;) // 执行到挂起为止
    {
        inst_t current = state->code[state->ip];
        //state->ip++; // 取出指令以后自动ip后移 +4
        state->ip=state->ip+4;
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
                scanf("%d\n",state->ax[state->data[current.p3]]);
            case IOUT:
                // 输出寄存器ax[n]中的数值
                printf("out: ")
                printf("%d\n",state->ax[state->data[current.p3]]);
                break;
            case ISTOP:
                //停机
                return;
        }
        printf("ip = %d\n",state->ip);
        printf("flag = %d\n",state->flag);
        printf("ir = %d\n",TranslationRef(*CODESET[i]));
        printf("ax1 = %d ax2 = %d ax3 = %d ax4 = %d\n",state->ax[1],state->ax[2],state->ax[3],state->ax[4]);
        printf("ax5 = %d ax6 = %d ax7 = %d ax8 = %d\n",state->ax[5],state->ax[6],state->ax[7],state->ax[8]);
    }
}
