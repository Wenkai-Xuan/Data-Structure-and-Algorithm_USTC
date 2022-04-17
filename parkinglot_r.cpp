#include<stdio.h>
#include<stdlib.h>

typedef struct elem{
	char info;
	int plate;
	int time;
	struct elem *next;
}ElemType; //Information of cars

struct SqStack{
	ElemType *stack;
	int top;
	int stacksize;	
};  //parking lot

struct SqQueue{
	ElemType *front;
	ElemType *rear;
};  //waiting lot

ElemType Popstack(struct SqStack *S, int n, int outcar){
	struct SqStack *temp;
	ElemType out;
	temp = (struct SqStack *)malloc(sizeof(struct SqStack));
	temp->stacksize = n;
	temp->stack = (ElemType *)malloc(n*sizeof(ElemType));
	temp->top = -1;
	while(S->top != outcar){
		temp->top++;
		temp->stack[temp->top] = S->stack[S->top];
		S->top--;
	}//后面的车给要出去的车让道，暂时停到另一个栈里 
	out = S->stack[S->top];//此时outcar在栈顶 
	S->top--;
	while(temp->top != -1){
		S->top++;
		S->stack[S->top] = temp->stack[temp->top];
		temp->top--;
	}
	return out;
}//某辆车出栈，并返回它的信息，用来结算停车费。 

int main(){
	char info;
	int plate;
	int time;
	int n,m,pr,i,j,outcar;
	int Qlength = 0;
	ElemType out;
	ElemType *f, *head, *q, *p;
	p = (ElemType *)malloc(sizeof(ElemType));
	struct SqStack *S;
	struct SqQueue *Q;
	S = (struct SqStack *)malloc(sizeof(struct SqStack));///给指针分配空间啊！！！ 
	Q = (struct SqQueue *)malloc(sizeof(struct SqQueue));
	printf("Input the length of parking lot, waiting lot and the price:\n");
	scanf("%d,%d,%d",&n,&m,&pr);
	S->stacksize = n;
	S->stack = (ElemType *)malloc(n*sizeof(ElemType));//长为n的栈 
	S->top = -1;
	Q->front = (ElemType *)malloc(sizeof(ElemType));
	Q->rear = (ElemType *)malloc(sizeof(ElemType));
	Q->front = NULL;
	Q->rear = NULL;	
	printf("Input the status of cars:\n");
	getchar();///多个scanf出现的时候尤其当scnaf第1个是%c时要小心 上一个scanf输完后输入的回车会被下一个scanf当作%c拿走! 
	scanf("%c,%d,%d",&info, &plate, &time);
	if(info == 'E'){
		printf("Done.\n");
		exit(0);
	}
	while(info != 'E'){
		switch(info)
		{
		case 'A' :
			if(S->top < n-1){
				S->top++;
				S->stack[S->top].info = info;
				S->stack[S->top].plate = plate;
				S->stack[S->top].time = time;
			}
			else if(Qlength < m){
				printf("Parking lot is full now. Please wait in the waiting lot.\n");
				p = (ElemType *)malloc(sizeof(ElemType));
				p->info = info;
				p->plate = plate;
				p->time = time;
				if(Q->front == NULL){
					Q->front = Q->rear = p; //Q->front 也放值 （NULL->next是不对的） 
					Q->rear->next = NULL;
				}
				else {
					Q->rear->next = p;
					Q->rear = p;
					Q->rear->next = NULL; //链表尾的next置成NULL，方便便利的时候退出while循环（第128行） 
				}  //入队列
				Qlength++;
			}
			else printf("The parking lot and the waiting lot are all full. Please find another place to park.");
			break;
		case 'D' :
			for(i=0;i<=S->top;i++){
				if(plate == S->stack[i].plate){
					outcar = i;
				}
			}// 找到要离开的car在栈中的位置 
			out = Popstack(S,n,outcar);//记下它的信息
			printf("The car has been in the parking lot for %d minutes.\n", (time - out.time));
			printf("The fee is %d dollars.\n", pr*(time - out.time));
			if(Q->front != NULL) {
				S->top++;
				S->stack[S->top] = *Q->front;
				Q->front = Q->front->next;
				Qlength--;  //waiting lot里的第一辆车进parking lot 
			}
			break;
		case 'P' :
	    	printf("The cars in the parking lot are as below:\n");
	    	if(S->top == -1){
	    		printf("The parking lot is empty.\n");
			}
			else{
				for(i=0;i<=(S->top);i++){
					printf("(%c, %d, %d)\n", S->stack[i].info,S->stack[i].plate,S->stack[i].time);//ATTENTION! S->stack[i] is not a pointer, can't use '->'
				}
			}
	    	break;
		case 'W' :
	    	printf("The cars in the waiting lot are as below:\n");
			p = Q->front;
			if(Q->front != NULL){
				while(p){
					printf("(%c, %d, %d)\n",p->info,p->plate,p->time);
					p = p->next;	
				}
			}
			else printf("The waiting lot is empty.\n");
	    	break;
	    case 'E' :
	    	exit(0);
	    	break;
		default :
	    	printf("Error!\n" );
	    	exit(0);
	   }
		printf("Input the status of cars:\n");
		getchar();
		scanf("%c,%d,%d",&info, &plate, &time);
	}
}
