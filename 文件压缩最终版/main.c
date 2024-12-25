#include <stdio.h>
#include <stdlib.h>
#include "HFT.h"
//#include "bitio.h" 网上参考文件，使用了栈
#include "Bit.h"
//按位读写后若不满足为8的倍数，则会在文件末尾写入偏移位数

void test(){
	unsigned int code=0B0;
	Bit bitbuff;
	
	bitbuff.size=strlen(bitbuff.b);
	bitbuff.num=0B0;
	for(int i=0;i<bitbuff.size;i++){
		bitbuff.num<<1;
		
	}
	set_bit(&code,0);
	code<<=2;
	printf("%u",code);
}


int interface() {
	FILE *fp=NULL,*wp=NULL;
	char c;
	int i=0,dic[128]={0};
	int *w,n=0;
	Code *code;
	
	fp=fopen("file/HT.txt","r");
	if(fp==NULL){
		perror("读取错误：");
	}
	//利用ASCII码，统计词频
	printf("原文件：\n");
	while((c=fgetc(fp))!=EOF){
		dic[c]+=1;
		printf("%c",c);
	}printf("\n");
	fclose(fp);
	//字符频率统计完成
	
	//舍弃字频为0的部分
	w=(int *)malloc(sizeof(int)*128);
	code=(Code *)malloc(sizeof(Code)*128);
	for(int i=0;i<128;i++){
		if(dic[i]!=0){
			w[n]=dic[i];
			code[n].c=(char)i;
			n++;
		}
	}
	w=(int *)realloc(w,n*sizeof(int));
	code=(Code *)realloc(code,n*sizeof(char));
	//分配字符完成，一共有n个字符
	
	HTn *HT;
	HuffmanCode HC;
	HT=(HTn *)malloc(sizeof(HTn)*2*n);//在initHT函数外部分配空间，不知道为什么但是通过了
	HC=(HuffmanCode)malloc(sizeof(char*)*(n+1));
	//在函数内部分配空间导致main域HT不能输出正确的值。
	InitHT(HT,n,w,code);
	HFCoding(HC,HT,n);
	
	/*
	for(int i=1;i<=n;i++){
		printf("%c:%s\n",code[i-1],HC[i]);
	}
	*/
	
	//写入HudffmanTree
	wp=fopen("file/HufTree.dat","wb");
	for(int i=0;i<n;i++){
		fwrite(&HT[i+1],sizeof(HTn),1,wp);
		fflush(wp);
	}
	fclose(wp);
	
	//保存HuffmanCode
	wp=fopen("file/HufCode.txt","w");
	if(wp==NULL) printf("wp打开失败");
	for(int i=0;i<n;i++){
		if(code[i].c!='\n'){
			fprintf(wp,"%c:",code[i].c);
			fprintf(wp,"%s\n",HC[i+1]);
		}
		else{
			fprintf(wp,"/n:");
			fprintf(wp,"%s\n",HC[i+1]);
		}
	}
	fclose(wp);

	//printf("二进制开始写入\n");
	FILE *wtp=NULL;
	fp=fopen("file/HT.txt","r");
	wp=fopen("file/CodeFile.dat","wb");
	wtp=fopen("file/CodeFile.txt","w");
	if(fp==NULL){
		printf("fp打开失败");
		return 0;
	}
	Bit bitbuff;//二进制数写入缓冲区，满足8的倍数写入。
	bitbuff.num=0;
	strcpy(bitbuff.b,"");
	bitbuff.size=0;
	//保存CodeFile.dat
	while((c=fgetc(fp))!=EOF){
		int p=0;
		while(c!=code[p].c){
			p++;
		}
		//找到对应字符
		//printf("%c",code[p]);
		
		char *copy;
		strcat(bitbuff.b,HC[p+1]);
		
		int len=strlen(HC[p+1]);
		bitbuff.size+=len;
		fprintf(wtp,"%s",HC[p+1]);
		
		//永远在低位存入，高位写出。即栈
		while(bitbuff.size>=8){
			for(int i=0;i<8;i++){
				if(bitbuff.b[i]=='0'){
					bitbuff.num<<=1;
					//clear_bit(&bitbuff.num,0);
					bitbuff.size--;
				}
				else if(bitbuff.b[i]=='1'){
					bitbuff.num<<=1;
					set_bit(&bitbuff.num,0);
					bitbuff.size--;
				}
				else{
					printf("特殊字符：%c\n",bitbuff.b[i]);
					bitbuff.size--;
				}
			}
			fwrite(&bitbuff.num,1,1,wp);
			bitbuff.num=0B0;
			copy=&bitbuff.b[8];
			strcpy(bitbuff.b,copy);
		}
	}
	//printf("退出while");
	if(bitbuff.size>0){
		//如果结束还有未处理的01编码
		int offset=8-bitbuff.size;//偏移位数
		unsigned int mask=0B0;
		
		while(bitbuff.size>0){
			//printf("%d",bitbuff.size);
			if(bitbuff.b[bitbuff.size-1]=='0'){
				bitbuff.num*=2;
				clear_bit(&bitbuff.num,0);
				bitbuff.size--;
			}
			else if(bitbuff.b[bitbuff.size-1]=='1'){
				bitbuff.num*=2;
				set_bit(&bitbuff.num,1);
				bitbuff.size--;
			}
			else{
				printf("特殊字符：%c\n",bitbuff.b[bitbuff.size-1]);
				bitbuff.size--;
			}
		}
		//printf("退出while");
		set_bit(&mask,offset-1);//得到补位码
		for(int i=0;i<offset;i++){
			bitbuff.num<<=1;
		}
		bitbuff.num|=mask;//补满为8位。
	}fwrite(&bitbuff.num,1,1,wp);
	
	printf("HF.txt已经压缩为CodeFile.dat\n");
	fclose(fp);
	fclose(wp);
	fclose(wtp);
	
    fp=fopen("file/CodeFile.dat","rb");
    HFunCoding(fp,HT,n);
    fclose(fp);
    
	return 0;
}


int main(void){
	//test();
	interface();
	return 0;
}