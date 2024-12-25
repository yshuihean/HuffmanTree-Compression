#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef BITSIZE
#define BITSIZE 1024
#define BYTE 8
#endif

typedef struct{
	char b[BITSIZE];
	unsigned int num;//表示二进制数据
	int size;//相当于栈指针
}Bit;

typedef struct{
	char buff[BYTE];
}Byte;

void set_bit(unsigned int *num,int n){
	*num|=(1<<n); //将num第n位数与1进行或运算
}//将第n位置为1
void clear_bit(unsigned int *num,int n){
	*num&=~(1<<n); //将num第n位数与1进行与运算,再按位取反
}//将第n位置为0

void change_bit(unsigned int *num,int n){
	*num^=(1<<n);
}//将第n位切换

int get_bit(unsigned int num,int n){
	return (num>>n)&1;
}

void set_bits(unsigned int *num,int m,int n){
	//设置从m位到n位为1
	unsigned int mask=((1<<(n-m+1))-1)<<m; //创建掩码
	*num|=mask;
}
void clear_bits(unsigned int *num,int m,int n){
	//设置从m位到n位为0
	unsigned int mask=((1<<(n-m+1))-1)<<m;
	*num&=~mask;
}
