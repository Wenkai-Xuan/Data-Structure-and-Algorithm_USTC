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
	}//����ĳ���Ҫ��ȥ�ĳ��õ�����ʱͣ����һ��ջ�� 
	out = S->stack[S->top];//��ʱoutcar��ջ�� 
	S->top--;
	while(temp->top != -1){
		S->top++;
		S->stack[S->top] = temp->stack[temp->top];
		temp->top--;
	}
	return out;
}//ĳ������ջ��������������Ϣ����������ͣ���ѡ� 

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
	S = (struct SqStack *)malloc(sizeof(struct SqStack));///��ָ�����ռ䰡������ 
	Q = (struct SqQueue *)malloc(sizeof(struct SqQueue));
	printf("Input the length of parking lot, waiting lot and the price:\n");
	scanf("%d,%d,%d",&n,&m,&pr);
	S->stacksize = n;
	S->stack = (ElemType *)malloc(n*sizeof(ElemType));//��Ϊn��ջ 
	S->top = -1;
	Q->front = (ElemType *)malloc(sizeof(ElemType));
	Q->rear = (ElemType *)malloc(sizeof(ElemType));
	Q->front = NULL;
	Q->rear = NULL;	
	printf("Input the status of cars:\n");
	getchar();///���scanf���ֵ�ʱ�����䵱scnaf��1����%cʱҪС�� ��һ��scanf���������Ļس��ᱻ��һ��scanf����%c����! 
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
					Q->front = Q->rear = p; //Q->front Ҳ��ֵ ��NULL->next�ǲ��Եģ� 
					Q->rear->next = NULL;
				}
				else {
					Q->rear->next = p;
					Q->rear = p;
					Q->rear->next = NULL; //����β��next�ó�NULL�����������ʱ���˳�whileѭ������128�У� 
				}  //�����
				Qlength++;
			}
			else printf("The parking lot and the waiting lot are all full. Please find another place to park.");
			break;
		case 'D' :
			for(i=0;i<=S->top;i++){
				if(plate == S->stack[i].plate){
					outcar = i;
				}
			}// �ҵ�Ҫ�뿪��car��ջ�е�λ�� 
			out = Popstack(S,n,outcar);//����������Ϣ
			printf("The car has been in the parking lot for %d minutes.\n", (time - out.time));
			printf("The fee is %d dollars.\n", pr*(time - out.time));
			if(Q->front != NULL) {
				S->top++;
				S->stack[S->top] = *Q->front;
				Q->front = Q->front->next;
				Qlength--;  //waiting lot��ĵ�һ������parking lot 
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
