#include "HFT.h"


void InitHT(HTn *HT,int n,int *w,Code *code){
	int i,m=2*n-1;
	if(n<=1) return;

	for(i=1;i<=n;i++){
		HT[i].weight=w[i-1];
		HT[i].sign=code[i-1].c;
		HT[i].lchild=0;
		HT[i].parent=0;
		HT[i].rchild=0;
	}
	for(i=n+1;i<=m;i++){
		HT[i].weight=0;
		HT[i].sign='\0';
		HT[i].lchild=0;
		HT[i].parent=0;
		HT[i].rchild=0;
	}
	
	for(i=n+1;i<=m;i++){//建哈夫曼树
		//在HT[1..i-1]选择parent为0且weight最小的两个结点，其序号分别为s1和s2
		int s1=0,s2=0;
		//Select(HT,i-1,&s1,&s2);
		for(int j=1;j<i;j++){
			if(HT[j].parent==0&&s1==0){
				s1=j;
			}
			else if(HT[j].parent==0&&s2==0){
				s2=j;
			}
			else if(HT[j].parent==0&&HT[s1].weight>HT[j].weight){
				s1=j;
			}
			else if(HT[j].parent==0&&HT[s2].weight>HT[j].weight){
				s2=j;
			}
		}
		HT[s1].parent=i;HT[s2].parent=i;
		HT[i].lchild=s1;HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}
	printf("哈夫曼树建立成功\n");
}

void HFCoding(HuffmanCode HC,HTn *HT,int n){
	char *cd;
	int start,c,f;
	cd=(char *)malloc(sizeof(char)*n);
	cd[n-1]='\0';
	for(int i=1;i<=n;i++){
		start=n-1;
		for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent){
			if(HT[f].lchild==c) cd[--start]='0';
			else cd[--start]='1';
		}
		HC[i]=(char *)malloc((n-start)*sizeof(char));
		strcpy(HC[i],&cd[start]);
	}
	free(cd);
	printf("哈夫曼编码成功\n");
}

void HFunCoding(FILE *fp,HTn *HT,int n){
	char cd,unc;//cd读到一个字节，需要解码。
	FILE *wp=NULL,*tmp=NULL;
	int start;
	int node=2*n-1;
	unsigned int bit_cd=0B0;
	
	//fp=fopen("file/CodeFile.txt","r");
	wp=fopen("file/UnCode.txt","w");
	printf("解压文件：\n");
	while(fread(&bit_cd,1,1,fp)==1){
		//printf("%u ",bit_cd);
		for(int i=7;i>=0;i--){
			if(get_bit(bit_cd,i)==0){
				node=HT[node].lchild;
			}
			else if(get_bit(bit_cd,i)==1){
				node=HT[node].rchild;
			}
			else{
				printf("解压错误!");
			}
			if(HT[node].lchild==0&&HT[node].rchild==0){
				unc=HT[node].sign;
				printf("%c",unc);
				fprintf(wp,"%c",unc);
				node=2*n-1;
			}
		}//8位读取完毕
	}
	fclose(wp);
	printf("\n解压完成");
	/*
	while(fread(&cd,sizeof(char),1,fp)==1){//从根到叶子
		if(cd=='0'){
			//printf("get l\n");
			node=HT[node].lchild;
		}
		else if(cd=='1'){
			//printf("get r\n");
			node=HT[node].rchild;
		}
		else printf("解压错误");
		if(HT[node].lchild==0&&HT[node].rchild==0){
			//printf("get leaf\n");
			unc=HT[node].sign;
			printf("%c",unc);
			fprintf(wp,"%c",unc);
			node=2*n-1;
		}
		//printf("%d:",node);
	}
	fclose(wp);wp=NULL;
	printf("\n解压完成");
	*/
}



/*
void HuffmanCoding(HTn *HT,HuffmanCode HC,int *w,int n){
	//w存放权值
	int i,m=2*n-1;
	if(n<=1) return;
	HT=(HTn*)malloc((m+1)*sizeof(HTn));
	for(i=1;i<=n;i++,w++){
		HT[i].weight=w[i];
		HT[i].lchild=0;
		HT[i].parent=0;
		HT[i].rchild=0;
	}//初始化各个非叶子结点
	for(i=n+1;i<=m;i++){
		HT[i].weight=0;
		HT[i].lchild=0;
		HT[i].parent=0;
		HT[i].rchild=0;
	}//初始化各个叶子结点

	for(i=n+1;i<=m;i++){//建哈夫曼树
		//在HT[1..i-1]选择parent为0且weight最小的两个结点，其序号分别为s1和s2
		int s1=1,s2=2;
		Select(HT,i-1,&s1,&s2);
		HT[s1].parent=i;HT[s2].parent=i;
		HT[i].lchild=s1;HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}
	
	HC=(HuffmanCode)malloc((n+1)*sizeof(char *));
	char *cd=(char *)malloc(n*sizeof(char));
	cd[n-1]='\0';
	for(i=1;i<=n;i++){
		int start=n-1;
		unsigned int c,f;
		for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent){
			if(HT[f].lchild==c) cd[--start]='0';
			else cd[--start]='1';
		}
		HC[i]=(char *)malloc((n-start)*sizeof(char));
		strcpy(HC[i],&cd[start]);
	}
	free(cd);
}
*/