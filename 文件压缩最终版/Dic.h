#ifndef Dic_H_
#define Dic_H_

#include<stdio.h>
#include<stdlib.h>
#define Dic_size 128

typedef struct{
	char c;
	int frequency;
}Dic;

void InitDic(Dic *dic);

#endif