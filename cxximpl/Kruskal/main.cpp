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
} MGraph; //����ͼ�ڽӾ���

typedef struct
{
    int isIn;
    int weight;
    int u,v;//uΪ�ߵ���㣬vΪ�ߵ��յ㣬����ֵС���յ��ֵ
} Edge; //�ߵ���Ϣ

void createGraph(MGraph &G)
{
    int i,j,start,end,weight;
    printf("ͼ�еĶ�����:");
    scanf("%d",&G.vexnum);
    G.arcs = (int**)malloc(G.vexnum*sizeof(int*));
    for(i=0; i<G.vexnum; i++)
    {
        G.arcs[i]=(int*)malloc(G.vexnum*sizeof(int));
        //�ڽӾ����ʼ��
        for(j=0; j<G.vexnum; j++)
        {
            G.arcs[i][j] = MAXINT;
        }
    }
    printf("ͼ�еı���:");
    scanf("%d",&G.arcnum);
    printf("������ͼ�еı�[��� �յ� Ȩֵ]:\n");
    for(i=0; i<G.arcnum; i++)
    {
        scanf("%d %d %d",&start,&end,&weight);
        G.arcs[start][end] = weight;
        G.arcs[end][start] = weight;
    }
};

void kruskal(MGraph G,Edge edges[])
{
    //���ߵ���Ϣ�洢��edges[]��
    int i,j;
    int e = 0;
    for(i=0; i<G.vexnum; i++)
    {
        for(j=i+1; j<G.vexnum; j++)
        {
            if(G.arcs[i][j]!=MAXINT)
            {
                edges[e].weight = G.arcs[i][j];
                edges[e].u = i;
                edges[e].v = j;
                edges[e].isIn = 0;
                e++;
            }
        }
    }
    int *t;
    t = (int*)malloc(G.arcnum*sizeof(int));
    //��С��������˫�ױ�ʾ���洢
    for(i=0; i<G.vexnum; i++)
    {
        t[i] = i;//��ʼ��˫��Ϊ�Լ�;
    }
    while(1)
    {
        //ѡȡ��С��һ����
        int min = MAXINT;
        int k = -1;
        for(i=0; i<G.arcnum; i++)
        {
            if(edges[i].isIn ==0 && edges[i].weight < min)
            {
                min = edges[i].weight;
                k = i;
            }
        }
        if(k == -1)
        {
            break;
        }
        //�жϼ���ñߺ��Ƿ񹹳ɻ�·
        int u = edges[k].u;
        while(t[u]!=u)
        {
            u = t[u];
        }
        int v = edges[k].v;
        while(t[v]!=v)
        {
            v = t[v];
        }
        if(u!=v)//û�й��ɻ�·
        {
            //���ñߵ������˵���뵽��С��������
            t[v] = u;
            edges[k].isIn = 1;
        }
        else//���ɻ�·
        {
            edges[k].weight = MAXINT;
        }
    }
}

int main()
{
    MGraph G;
    createGraph(G);
    Edge *edges = (Edge*)malloc(G.arcnum*sizeof(Edge));
    kruskal(G,edges);
    printf("��С�����������ıߵ���Ϣ���£�\n");
    int i;
    for(i=0; i<G.arcnum; i++)
    {
        if(edges[i].isIn == 1)
        {
            printf("%d->%d:%d\n",edges[i].u+1,edges[i].v+1,edges[i].weight);
        }
    }
    return 1;
}
