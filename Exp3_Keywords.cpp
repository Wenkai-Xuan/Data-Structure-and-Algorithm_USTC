#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int *get_next(char *P){ //char *P为模式串，即关键词串
	int *next;
	int j = 0;
	int k = -1;
	next = (int *)malloc(strlen(P)*sizeof(int));
	next[0] = -1;
	while(j < strlen(P)){
		if(k == -1 || P[j] == P[k]){
			j++;
			k++;
			if(P[j] != P[k]) next[j] = k;
			else next[j] = next[k];
		}
		else k = next[k];
	}
	return next;
}

int KMP_index(char *S, char *P, int start, int *next){ 
	int i,j,k,n;
	if(start < 0 || start > strlen(S)-strlen(P)){
		printf("The start place is illegal!\n");
		return -1;
	}
	i = start; //i为主串S的匹配开始的位置 
	j = 0; //j为子串的开头
	while(S[i] != '\0' && P[j] != '\0'){
		if(j == -1 || S[i] == P[j] || abs(S[i]-P[j]) == 32){  //小写字母和大写字母的ASCII相差32 
			i++;
			j++;
		}
		else j = next[j];
	}
	if(P[j] == '\0') return (i-j);
	return -1;
}//对比字符串S和P，并返回匹配开始的字符位置 

int main(){
	//int *text[100]; //指针数组，每个元素为指向文本每行的指针。限制了能查找的最长的文本为100行
	int line=1, index, start;
	int flag=0;
	int *next;
	char *S;
	char *P;
	char *f;
	FILE *fp; 
	P = (char *)malloc(100*sizeof(char));//限制了能查找的最长的单词为99个字母
	S = (char *)malloc(1000*sizeof(char));//限制了每一行最长为1000个字符 
	
	f = (char *)malloc(20*sizeof(char));//限制了文件名不能超过20个字符 
	printf("Please input the name of file which you want to open:\n");
	scanf("%s", f);
	fp = fopen(f, "r");
	if(!fp) {
		printf("Failed to open the specified file.\n");
		return -1;
	}
	
	printf("Please input the keyword that you want to find in this file:\n");
	scanf("%s", P);  //从终端输入完单词后，程序会自动在字符串结尾加上'\0' 
	next = get_next(P);
	
	while(!feof(fp)){
		fgets(S, 1000, fp);
		index = KMP_index(S, P, 0, next);
		while(index != -1){
			printf("The keyword is located in the line %d of this file, and its beginning index is %d.\n", line, index);
			flag++;//每找到一个单词就记录下来 
			index = KMP_index(S, P, index+strlen(P), next);//防止文件一行里有好几个目标单词 
		}
		line++;
	}
	if(flag == 0) printf("The keyword is not found in the specified file.\n");
}
