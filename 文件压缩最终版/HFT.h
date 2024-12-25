#ifndef HFT_H_
#define HFT_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
	char sign;
	int weight;
	int parent,lchild,rchild;
}HTn,*HTPtr;//哈夫曼树结构

typedef char** HuffmanCode;
//哈夫曼编码表

typedef struct{
	char c;
}Code;//ASCII码表

void InitHT(HTn *HT,int n,int *w,Code *code);
void HFCoding(HuffmanCode HC,HTn *HT,int n);
void HFunCoding(FILE *fp,HTn *HT,int n);
#endif