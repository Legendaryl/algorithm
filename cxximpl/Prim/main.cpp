/*
6
10
0 1 6
0 2 1
0 3 5
1 2 5
1 4 3
2 3 5
2 4 6
2 5 4
3 5 2
4 5 6
*/
#include "stdio.h"
#include "stdlib.h"

#define MAXINT 100

typedef struct
{
	int vexnum;
	int arcnum;
	int **arcs;
}MGraph;

void createGraph(MGraph &G)
{
	int i,j,start,end,weight;
	printf("ͼ�еĶ�����:");
	scanf("%d",&G.vexnum);
	G.arcs = (int**)malloc(G.vexnum*sizeof(int*));
	for(i=0;i<G.vexnum;i++)
	{
		G.arcs[i]=(int*)malloc(G.vexnum*sizeof(int));
		//�ڽӾ����ʼ��
		for(j=0;j<G.vexnum;j++)
		{
			G.arcs[i][j] = MAXINT;
		}
	}
	printf("ͼ�еı���:");
	scanf("%d",&G.arcnum);
	printf("������ͼ�еı�[��� �յ� Ȩֵ]:\n");
	for(i=0;i<G.arcnum;i++)
	{
		scanf("%d %d %d",&start,&end,&weight);
		G.arcs[start][end] = weight;
		G.arcs[end][start] = weight;
	}
};

void Prim(MGraph G,int v0,int lowcost[],int adjvex[])
{
	int *s = (int*)malloc(G.vexnum*sizeof(int));
	//��ʼ��
	int i;
	for(i=0;i<G.vexnum;i++)
	{
		if(i!=v0)
		{
			adjvex[i] = v0;
			lowcost[i] = G.arcs[v0][i];
			s[i] = 0;//������С��������
		}
		else
		{
			adjvex[i] = v0;
			lowcost[i] = 0;
			s[i] = 1;
		}
	}
	int j;
	for(j=0;j<G.vexnum;j++)
	{
		//ѡ����С�ı�
		int min = MAXINT;
		int k = -1;
		for(i=0;i<G.vexnum;i++)
		{
			if(s[i] == 0)
			{
				if(lowcost[i] < min)
				{
					min = lowcost[i];
					k = i;
				}
			}
		}
		if(k == -1)
		{
			break;
		}
		s[k] = 1;
		//���������������Ϣ
		for(i=0;i<G.vexnum;i++)
		{
			if(s[i] == 0)
			{
				if(lowcost[i] > G.arcs[k][i])
				{
					lowcost[i] = G.arcs[k][i];
					adjvex[i] = k;
				}
			}
		}
	}
}

int main()
{
	MGraph G;
	createGraph(G);
	int *lowcost;
	int *adjvex;
	adjvex = (int*)malloc(G.vexnum*sizeof(int));
	lowcost = (int*)malloc(G.vexnum*sizeof(int));
	Prim(G,0,lowcost,adjvex);
	printf("��С�����������ıߵ���Ϣ���£�\n");
	int i;
	for(i=0;i<G.vexnum;i++)
    {
		printf("%d->%d:%d\n",i+1,adjvex[i]+1,lowcost[i]);
    }
    return 1;
}
