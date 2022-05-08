#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
	char word;
	int weight;
	int parent, rchild, lchild;
}NTNode, *HuffmanTree;
typedef NTNode *HuffTree;

struct node{
	char word;
	int fre;
};

struct SqStack{
	char *stack;
	int top;
	int stacksize;
};
 
//struct SqStack S;  //顺序栈，记录遍历路径，定义一个结构体存栈的指针和top应该就可以了，不用结构体指针。结构体变量在定义的时候就会自动分配空间，和int啥的一样 
                   //栈用来临时存huffman树上一条路径上的编码（即某个叶子结点的编码） 
//NTNode *HT = NULL;  //指向huffman树的指针 
//char **HC = NULL;  //存储各叶子结点对应的编码字符串   //HT,HC的下标是一一对应的 
//struct node *w;


int InitialTree(NTNode * &HT, struct node * &w){
	int i, j, n, num_code;
	int s1, s2, min1, min2, temp;

	printf("Input the size of character set:\n");
	scanf("%d", &n);
	num_code = n*2-1;
//	printf("%d", num_code);
	HT = (NTNode *)malloc((num_code+1)*sizeof(NTNode));  //HT[0]空着 
	w = (struct node *)malloc(n*sizeof(struct node));
	printf("Please input the characters and their frequency:\n");
	getchar();   //拿走上一句scanf输入完结尾处的'\n' 
	scanf("%c,%d", &w[0].word, &w[0].fre);
	for(i=1;i<n;i++){
		printf("Go ahead:\n");
		getchar();  //拿走上一句scanf输入完结尾处的'\n'
		scanf("%c,%d", &w[i].word, &w[i].fre);   //空格,A,B,C...必须按顺序输入，从而分别对应w[n]的0,1,2...下标 
//		printf("%c\n", w[i].word);
	}  //从终端输入字符及其频度
	
	for(i=1;i<=num_code;i++){
		HT[i].word =  (i<=n) ? w[i-1].word : '*';
		HT[i].weight = (i<=n) ? w[i-1].fre : 0;  //HT[i]和w[i-1]对应，所以空格,A,B,C...分别对应HT[n]的1,2,3...下标,HT[0]什么也不存 
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0; 
	}  //初始化HT[]
	

	for(i=n+1;i<=num_code;i++){ 
		min1 = 1000;  //min1 = HT[1].weight;是不行的，因为如果HT[1].weight是最小的话，第一次整合后它就不再参与整合了 
		min2 = 1000;
		s1 = 1;
		s2 = 1;
		for(j=1;j<=i-1;j++){
			if(HT[j].parent == 0){
				temp = HT[j].weight;
				if(temp < min2){
					if(temp > min1) {
						min2 = temp;
						s2 = j;
					}
					else {
						min2 = min1;
						s2 = s1;
						min1 = temp;
						s1 = j;
					}
				}
			}  //HT[j].parent == 0才参与整合 
		} //Select(HT, n, i, s1, s2),注意筛选的时候一定只能选parent=0的那些;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight+HT[s2].weight;
		HT[s1].parent = i;
		HT[s2].parent = i;
	}
	FILE *fp = fopen("hfmTree.txt", "w");
	if(fp == NULL)  printf("Can't open the file!\n");
	for(i=1;i<=num_code;i++)  fprintf(fp, "%c,%d,%d,%d,%d\n", HT[i].word, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
	fclose(fp);  //将生成的Huffman树放入文件hfmTree.txt中 
	return n;   //返回叶子结点数 
}

void Coding(NTNode *HT, int n, int root, char ** &HC, SqStack &S){
	if(root != 0){
		if(HT[root].lchild == 0){   //root为树叶 
			S.top++;
			S.stack[S.top] = '\0';
			HC[root] = (char *)malloc((2*n-1)*sizeof(char));
			strcpy(HC[root], S.stack);
			S.top--;   //'\0'出栈 
		}
		S.top++;
		S.stack[S.top] = '0';
		Coding(HT, n, HT[root].lchild, HC, S);
		S.top--;    //左子树 
		S.top++;
		S.stack[S.top] = '1';
		Coding(HT, n, HT[root].rchild, HC, S);
		S.top--;   //右子树 
	}
}//这个代码只是建立好了各字母对应的编码 

Encoding(NTNode *HT, int n, int root, char ** &HC){    //int n为Huffman树的叶子结点总数，为n 
	struct SqStack S;
	S.stack = (char *)malloc((2*n-1)*sizeof(char));
	S.top = -1;   //定义一个全局的栈，因为后面递归的时候需要一个全局的栈 
	HC = (char **)malloc((n+1)*sizeof(char *));
	Coding(HT, n, root, HC, S);
}  //HC[]建立完成

//Decoding(NTNode *HT, int n, int root, char **HC, FILE *codefile, FILE * &textfile){
//	char s[100];   //设置一个字符串数组来存储一个编码 
//	int i,j,k,b=1;
//	while(!feof(codefile)){
//		j=0;
//		while(b && !feof(codefile)){    //逐个从FILE中拿编码并存在字符串数组s里，再将每次的s和HC中的编码比对，一样就输出编码对应的字符
//			s[j] = fgetc(codefile);   //用了fgetc后这个codefile指针会从一开始指向文件开头不断向后移动
//			s[j+1] = '\0';
//			for(i=1;i<=n;i++){
//				if(!strcmp(s, HC[i])) {
//					b = 0;
//					k = i;
//				}
//			}
//			j++;
//		}     //这里翻译编码也可以通过走huffman树来实现
//		fprintf(textfile, "%c", HT[k].word);
//		b = 1;
//	}
//}//这种解法会导致最后一串编码被解码两次，感觉是因为feof的问题，读到最后一个编码时b就等于0了，但feof的指针好像还没指向文件的末端，不知道是不是也指向最后一个编码，所以就又进入了循环。 

Decoding(NTNode *HT, int n, int root, char **HC, FILE * &codefile, FILE * &textfile){
	char c;   //设置一个字符来存储一个编码
	if(root != 0){
		if(HT[root].lchild == 0){
			fprintf(textfile, "%c", HT[root].word);
			Decoding(HT, n, 2*n-1, HC, codefile, textfile);   
		} //一进来就先判断root是不是叶子结点，是,就直接打印，不是再让c去文件里拿字符，这样可以防止c在开头就拿字符导致的，print的时候c是又从文件里拿了一个字符的，即打印叶子结点的时候，c多拿了一个字符  
		else{
			c=fgetc(codefile);
			if(c == '0'){
				Decoding(HT, n, HT[root].lchild, HC, codefile, textfile);
			}
			if(c == '1'){
				Decoding(HT, n, HT[root].rchild, HC, codefile, textfile);
			}
		}
	}
}

//void TreePrint(NTNode *HT, int root, int n, int tag){
//	int i;
//	if(root == 0) return;
//	else{
//		for(i=0;i<n;i++){
//			printf("\t"); 
//		}
//		if(root > n) printf("*");
//		else printf("%c", HT[root].word);
//		if(tag == 0 && HT[root].lchild != 0) printf("\n");
//		
//		TreePrint(HT, HT[root].lchild, n-1, 0);
//		TreePrint(HT, HT[root].rchild, n+1, 1);
//	}
//}//二叉树的先序遍历，有问题 

void TreePrint(NTNode *HT, int root, int n, int j){
	int i;
	if(root == 0) return;
	else{
		TreePrint(HT, HT[root].rchild, n, j+1);
		
		for(i=0;i<j;i++){
			printf("\t"); 
		}
		if(root > n) printf("*\n");  //打印的是Huffman树的合成结点 
		else printf("%c\n", HT[root].word);
		
		TreePrint(HT, HT[root].lchild, n, j+1);
	}
} //凹入形式横向打印二叉树

void Menu(){
	printf("*******************************************\n");
	printf("Huffman Encoding & Decoding Menu: \n");
	printf("* I Initialization \n");
	printf("* E Encoding \n");
	printf("* D Decoding \n");
	printf("* P Print \n");
	printf("* T Tree Printing \n");
	printf("* Q Quit \n");
	printf("*******************************************\n");
	printf("Choose what you want to do:\n");
}
int main(){
	char op, c;
	char s[51];
	NTNode *HT = NULL;
	char **HC = NULL;
	struct node *w;
	int root, n, i;  //huffman树根下标为2n-1 
	FILE *tobetran, *codefile, *textfile;
	Menu();
	scanf("%c", &op);
	if(op == 'Q') exit(0);
	while(op != 'Q'){
		switch(op)
		{
			case 'I' :
				n = InitialTree(HT, w);
				break;
			case 'E' :
				if(HT == NULL) {
					printf("You have not create a huffman tree, so you can't encode the text.\n");
					break;
				}
				
				tobetran = fopen("ToBeTran1.txt", "r");
				if(!tobetran) {
					printf("Failed to open the ToBeTran.txt.\n");
					return -1;
				}
				codefile = fopen("CodeFile.txt", "w+");
				if(!codefile) {
					printf("Failed to open the CodeFile.txt.\n");
					return -1;
				}
//				n = InitialTree(); 
				Encoding(HT, n, 2*n-1, HC);   //huffman树根节点下标为2*n-1 
				while(!feof(tobetran)){      //如果文件未到末尾 
					c = fgetc(tobetran);   //依次取文件里的一个字符
					for(i=1;i<=n;i++){
						if(c == HT[i].word) fprintf(codefile, "%s", HC[i]); //将一个字符对应的编码写进CodeFile.txt文件 
//						printf("%c",c);
					}
				}  //对文件里的所有字符进行遍历
				fclose(tobetran);
				fclose(codefile);
				break;
			case 'D' :
				if(HT == NULL) {
					printf("You have not create a huffman tree, so you can't encode the text.\n");
					break;
				}
				if(HC == NULL) {
					printf("You have not create a method to encode a text, so you can't decode the file.\n");
					break;
				}
				
				codefile = fopen("CodeFile.txt", "r");
				if(!codefile) {
					printf("Failed to open the CodeFile.txt.\n");
					return -1;
				}
				textfile = fopen("TextFile.txt", "w+");
				if(!textfile) {
					printf("Failed to open the TextFile.txt.\n");
					return -1;
				}
//				n = InitialTree();

				Decoding(HT, n, 2*n-1, HC, codefile, textfile);
				
				fclose(codefile);
				fclose(textfile);
				break;
			case 'P' :		
				if(HT == NULL) {
					printf("You have not create a huffman tree, so you can't encode the text.\n");
					break;
				}
				if(HC == NULL) {
					printf("You have not create a method to encode a text, so you can't decode the file.\n");
					break;
				}
				
				codefile = fopen("CodeFile.txt", "r");
				if(!codefile) {
					printf("Failed to open the CodeFile.txt.\n");
					return -1;
				}
				
				while(!feof(codefile)){   //如果文件未到末尾
					fgets(s, 50, codefile);   //以这种投机的方法在终端上一行打印50个字符 
					printf("%s\n", s);  //用printf的格式设置 printf("%.50s\n", s) ，让它一行打印50个字符 
				}
				fclose(codefile);
				break;
			case 'T' :
				if(HT == NULL) {
					printf("You have not create a huffman tree, so you can't print it.\n");
					break;
				}		
				
				TreePrint(HT, n*2-1, n, 0);
				
				break;
			case 'Q' :
				exit(0);
				break;
			default :
				printf("Error!\n");
				exit(0);
		}
	Menu();
	getchar();
	scanf("%c", &op);
	}
}
