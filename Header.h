//
//  Header.h
//  冯诺依曼式计算机CPU模拟器
//
//  Created by 陆泽意 on 2020/5/5.
//  Copyright © 2020 陆泽意. All rights reserved.
//

#ifndef Header_h
#define Header_h


#endif /* Header_h */
void execute(vm_state_t *state);
char Instruct(char *Code1,*Code2,*Code3);
int returnNumber1(char *Code1,*Code2,*Code3);
int returnNumber2(char *Code1,*Code2,*Code3);
int serialNumber(char *Code1,*Code2,*Code3);
int TranslationRef(*Code);

typedef struct inst
{
    unsigned char code; // 指令
    short p1, p2 ,p3;// 参数1、2、3  1，2传入执行指令所需的值，3代表结果保存的寄存器编号
} inst_t;
typedef struct vm_state
{
    int ip; // 指令ptr
    int flag; // 记录最后判断的标志
    inst_t *code; // 代码段地址
    data_t *data; // 数据段地址
    short ax[9];//寄存器
} vm_state_t;


int Memory[32767];
char CodeMemory1[100][9],CodeMemory2[100][5],CodeMemory3[100][5],CodeMemory4[100][17];
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
#define ILOG    13 //逻辑指令
#define ILOV    14 //逻辑指令
#define ILON    15 //逻辑指令
#define ISTOP   255 // 挂起虚拟机  停机

#define FNA     0 // 任何状态下都执行  比较后相等为0
#define FEQ     1 // 状态为“相等”时执行  寄存器1中的大 置为1
#define FNE     -1 // 状态为“不等”时执行  立即数大   置为-1
