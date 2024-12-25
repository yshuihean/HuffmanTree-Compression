#include "Dictionary.h"

void InitDictionary(Dictionary *dic){
	dic=malloc(sizeof(Dictionary)*BasicSize);
	for(int i=0;i<BasicSize;i++){
		dic[i].frequency=0;
	}
}