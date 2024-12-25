#ifndef Dictionary_H_
#define Dictionary_H_

#include<stdio.h>
#include<stdlib.h>

typedef struct{
	char character;
	int frequency;
}DicNode;

void InitDictionary(Dictionary *dic);
#endif