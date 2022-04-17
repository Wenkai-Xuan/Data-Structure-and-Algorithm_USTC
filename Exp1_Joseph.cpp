#include<stdio.h>
#include<stdlib.h>
struct person{
	int num;
	int code;
	struct person *next;//Don't forget! 
}; //Don't forget!

struct person *createlist(void){ //struct person *head,struct person *q,int n
	int i, n;
	struct person *head;
	struct person *rear;
	struct person *p;
	head = NULL;
	printf("Input the number of people:\n");
	scanf("%d", &n);
	if(n <= 0){
		printf("It's not a legal input!\n");
	}
	else{
		for(i=0;i<n;i++){
			p = (struct person*)malloc(sizeof(struct person));
			p->num = i+1;
			printf("Input the code of the person:\n");
			scanf("%d", &p->code);
			if(head == NULL) head = p;
			else rear->next = p;
			rear = p;
		}//create a chain having head and rear
		if(rear != NULL){
			rear->next = head;
		}
		printf("The list has already been set.\n");
	}
	return head;
}

struct person *deletelist(struct person *head, int m){
	int i;
	struct person *p;
	struct person *q;
	p = head;
	printf("The order of getting out of queue is:\n");
	while(p->next != p){
		if(m == 1){
			q = p;
			while(p->next != q){
				p = p->next;
			}
			printf("%d\n", q->num);
			m = q->code;
			p->next = q->next;
			free(q);
			p = p->next;
		}
		else{
			for(i=1;i<m-1;i++){   //m=1 bug
				p = p->next;
			}
			q = p;
			q = q->next; //delete q
			printf("%d\n", q->num);  //print people's number
			m = q->code;
			p->next = q->next;
			free(q);
			p = p->next;
	 	}
	}
	printf("%d\n", p->num);//print the winner
}

main(){
	struct person *head;//���ø�head�ٶ�̬����ռ��ˣ��ǲ���Ҫ�ģ�������head��head��ռ����һ��ָ��Ŀռ��ˣ���������ʱѭ����Ҫ��̬����ʱ��ΪҪ�������ṹ�嶼����ռ� 
	int m;
	printf("First we create a list:\n");
	head = createlist();//����ֻ�Ǵ��˸���ַ��head����head�պ��д��ַ���ڴ�
	printf("Then we input an m to call:\n");
	scanf("%d", &m);
	deletelist(head, m);
	
}
