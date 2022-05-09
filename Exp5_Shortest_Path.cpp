#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<math.h>

//#define INFINITY (1.0/0.0)   //C语言中自带INFINITY 
#define MAX_VERTEX_NUM 20

typedef struct{
	char vexs[MAX_VERTEX_NUM];
	float arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int vexnum, arcnum;
	int kind;
}MGraph;

void Prim(MGraph G, int v0, int *adjvex){
	int i,j,k;
	float lowcost[MAX_VERTEX_NUM];
	float min;
	for(j=0;j<G.vexnum;j++){
		if(j != v0){
			lowcost[j] = G.arcs[v0][j];
			adjvex[j] = v0;
		}
	}
	lowcost[v0] = 0;  //0表示v0已在生成树内 
	for(i=0;i<G.vexnum;i++){
		min = INFINITY;
		for(j=0;j<G.vexnum;j++){
			if(lowcost[j] <= min && lowcost[j] > 0){  //注意 lowcost[j]=0表示的是j结点在生成树中，选取最小值时不能把它算入 
				min = lowcost[j];
				k = j;
			}
		}
		printf("(%d, %d), %.1f\n", k, adjvex[k], lowcost[k]); //打印某个点到生成树上距离最小点之间的点对以及对应的权值 
		lowcost[k] = 0;
		for(j=0;j<G.vexnum;j++){
			if(G.arcs[k][j] < lowcost[j]){
				lowcost[j] = G.arcs[k][j];
				adjvex[j] = k;
			}
		} //将邻接矩阵k行的值拿下来和lowcost各值做比较，更小的就放到lowcost相应下标处，同时更新adjvex对应的下标处 
	}
}

int main(){
	MGraph G;
	int i, j, k, temp1, temp2, flag, v0;
	char v1,v2,v;
	float w;
	int adjvex[MAX_VERTEX_NUM]; //存放邻接点 
	printf("**Please create a graph first**\n");
	printf("Please input the number of the graph's vertexes and arcs:\n");
	scanf("%d,%d", &G.vexnum, &G.arcnum);  //测试数据是 9,15 
	printf("Please input the names of the vertexes one by one:\n");
	getchar();
	scanf("%c", &G.vexs[0]);
	for(i=1;i<G.vexnum;i++){
		printf("Go ahead:\n");
		getchar();
		scanf("%c", &G.vexs[i]);
	} //创建顶点名数组
	
	for(i=0;i<G.vexnum;i++){
		for(j=0;j<G.vexnum;j++) G.arcs[i][j] = INFINITY;
	}  //初始化邻接矩阵
	for(k=0;k<G.arcnum;k++){
		printf("Please input vertex one, vertex two, and the weight on arc between them one by one:\n");
		getchar();
		scanf("%c,%c,%f", &v1, &v2, &w);  //顶点v1、v2之间的权重为w
		for(i=0;i<G.vexnum;i++){
			if(v1 == G.vexs[i]) temp1 = i;
		}
		for(j=0;j<G.vexnum;j++){
			if(v2 == G.vexs[j]) temp2 = j;
		}
		G.arcs[temp1][temp2] = w;
		G.arcs[temp2][temp1] = w;  //该图为网
	} //邻接矩阵构造完成 
	getchar();
	flag = 0; //用来表示开始的顶点v0在不在图中
	while(flag == 0){
		printf("Please input one vertex to begin:\n");
		scanf("%c", &v);
		for(i=0;i<G.vexnum;i++){
			if(v == G.vexs[i]) {
				flag++;
				v0 = i;
			}
		}
		if(flag == 0) printf("The vertex is not in the graph!\n");
	}
	
	Prim(G, v0, adjvex);
}
