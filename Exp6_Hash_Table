#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<math.h>

//本次实验主要是查找3个程序中这些关键词：bool void int if while else cout 出现的频度 

typedef struct HNode{
	char word[6];
	int frq;
	struct HNode *next;
}HNode; 


HNode *Hashtable(FILE *fp, HNode *hashtable, char **key){
	char str[1000];  //存放文件里的单词 
	int hash_key;
	int i, j, k;
	int c;

	for(i=0;i<7;i++){
		hash_key = (key[i][0]*100 + key[i][strlen(key[i])-1])%41; //求哈希函数值，hash表无冲突 
		strcpy(hashtable[hash_key].word, key[i]);
		hashtable[hash_key].frq = 0; //初始化关键字的频率为0 
	}//创建hash表 

	while(!feof(fp)){
		i = 0;
		c = fgetc(fp);
		while((char) c != ' ' && (char) c != '\n' &&(char) c != '(' && !feof(fp)){ //这里退出循环的条件尤其多，要注意 
			str[i] = (char) c; //fgetc()返回值的类型是int 
			i++;
			c = fgetc(fp);
		}//拿取文件中的一个单词
		str[i] = '\0';//在单词末尾加上结束符 
		
		for(j=0;j<7;j++){
			if(strcmp(str, key[j]) == 0){
				k = (key[j][0]*100 + key[j][strlen(key[j])-1])%41;
				hashtable[k].frq++;
				break;
			}//找到了一个关键字，让它的频率+1 
		} //把拿到的这个单词和关键词比较 
//		printf("%d\n", hashtable[k].frq);
//		printf("%s\n", str);
	}//扫描一个文件 

	return hashtable;	
}

double Sim(int *x1, int *x2, int len){
	double x12, modu1, modu2;
	double S;
	int i,j;
	x12 = 0;
	modu1 = 0;
	modu2 = 0;
	for(i=0;i<len;i++){
		x12 += x1[i]*x2[i];
		modu1 += x1[i]*x1[i];
		modu2 += x2[i]*x2[i]; 
	}
	modu1 = sqrt(modu1);
	modu2 = sqrt(modu2);
	S = x12/(modu1*modu2);
	
	return S;
}

double Dis(int *x1, int *x2, int len){
	int dist;
	int i;
	for(i=0;i<len;i++){
		dist += (x1[i] - x2[i])*(x1[i] - x2[i]);
	}
	dist = sqrt(dist);
	
	return dist;
}

int main(){
	HNode *hashtable_1;
	HNode *hashtable_2;
	FILE *fp, *fq;
	char *f, *g;
	char **key;
	int x1[7];
	int x2[7];
	int i, hash_key;
	double S, D;
	hashtable_1 = (HNode *)malloc(43*sizeof(HNode));
	hashtable_2 = (HNode *)malloc(43*sizeof(HNode));
	key = (char **)malloc(7*sizeof(char *));
	for(i=0;i<7;i++){
		key[i] = (char *)malloc(6*sizeof(char));
	}
	strcpy(key[0], "bool");
	strcpy(key[1], "void");
	strcpy(key[2], "int");
	strcpy(key[3], "if");
	strcpy(key[4], "while");
	strcpy(key[5], "else");
	strcpy(key[6], "cout");
	
	f = (char *)malloc(20*sizeof(char));//限制了文件名不能超过20个字符 
	g = (char *)malloc(20*sizeof(char));
	
	printf("Please input the name of the file which you want to open:\n");
	scanf("%s", f);
	fp = fopen(f,"r");
	if(!fp) {
		printf("Failed to open the specified file.\n");
		return -1;
	}
	hashtable_1 = Hashtable(fp, hashtable_1, key);
	
	printf("Then input the name of the file which you want to compare with:\n");
	scanf("%s", g);
	fq = fopen(g,"r");
	if(!fq) {
		printf("Failed to open the specified file.\n");
		return -1;
	}
	hashtable_2 = Hashtable(fq, hashtable_2, key);
	
	for(i=0;i<7;i++){
		hash_key = (key[i][0]*100+key[i][strlen(key[i])-1])%41; //求哈希函数值
		x1[i] = hashtable_1[hash_key].frq;
		x2[i] = hashtable_2[hash_key].frq;
	}//求向量x1和x2 
	
	S = Sim(x1, x2, 7);
	printf("The similarity S(x1,x2) of these two code files is %lf\n", S);

	D = Dis(x1, x2, 7);
	printf("The distance of these two code files is %lf\n", D);
}
