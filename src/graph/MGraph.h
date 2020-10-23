// Adj Matrix
// Build Graph & DFS & BFS
#include <stdio.h>
#include <stdlib.h>
#include <queue>//for BFS

typedef int Vertex;
typedef int WeightType;
#define MaxVertexNum 100
#define INFINITY 65535

typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv, Ne;
    WeightType G[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph;

MGraph CreateGraph(int VertexNum){
    Vertex V, W;
    MGraph Graph;
    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Ne = 0;
    Graph->Nv = VertexNum;

    for (V = 0; V < Graph->Nv; ++V){
        for(W = 0; W < Graph->Nv; ++W){
            Graph->G[V][W] = INFINITY;
        }
    }
    return Graph;
}


typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;
    WeightType Weight;
};
typedef PtrToENode Edge;

void InsertEdge(MGraph Graph, Edge E){
    Graph->G[E->V1][E->V2] = E->Weight;
    //Graph->G[E->V2][E->V1] = E->Weight;//for unweighted graph
}


MGraph BuildGraph(){
    MGraph Graph;
    Edge E;
    Vertex V;
    int Nv;

    printf("input the number of vertex:\t");
    scanf("%d", &Nv);
    Graph = CreateGraph(Nv);
    printf("input the number of edge:\t");
    scanf("%d", &(Graph->Ne));
    if (Graph->Ne!=0){
        E = (Edge)malloc(sizeof(struct ENode));
        for (int i = 0; i < Graph->Ne; ++i){
            printf("input edge %d: v1 v2 weight:\t", i+1);
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}

bool Visited_DFS[MaxVertexNum];

void Visit( Vertex V ){
    printf(" %d", V);
}

void DFS(MGraph Graph, Vertex S, void (*Visit)(Vertex)){
    Visit(S);
    Visited_DFS[S] = true;

    for(Vertex W=0;W<Graph->Nv;++W)
        if (Graph->G[S][W]<INFINITY && !Visited_DFS[W])    
            DFS(Graph, W, Visit);
}

bool Visited_BFS[MaxVertexNum];
void BFS(MGraph Graph, Vertex S, void (*Visit)(Vertex)){
    std::queue<Vertex> Q;
    
    Visit(S);
    Visited_BFS[S] = true;
    Q.push(S);

    while (!Q.empty())
    {
        Vertex V = Q.front();
        Q.pop();
        for(Vertex W=0; W<Graph->Nv; ++W)
            if(Graph->G[V][W]<INFINITY && !Visited_BFS[W]){
                Visit(W);
                Visited_BFS[W] = true;
                Q.push(W);
            }
    }
}

Vertex FindMinDist(MGraph Graph, int dist[], int collected[]){
    Vertex MinV, V;
    int MinDist = INFINITY;

    for (V = 0; V < Graph->Nv; ++V)
        if(collected[V]==false && dist[V]<MinDist){
            MinDist = dist[V];
            MinV = V;
        }
    if (MinDist<INFINITY)
        return MinV;
    else
        return -1;
}

bool Dijkstra(MGraph Graph, int dist[], int path[], Vertex S){
    int collected[MaxVertexNum];
    Vertex V;

    for (V = 0; V < Graph->Nv; ++V){
        dist[V] = Graph->G[S][V];
        if (dist[V]<INFINITY)
            path[V]=S;
        else
            path[V]=-1;
        collected[V] = false;
    }

    dist[S]=0;
    collected[S] = true;

    while (1){
        V = FindMinDist(Graph, dist, collected);
        if(V==-1)
            break; 
        collected[V] = true;
        for (Vertex W = 0; W < Graph->Nv; ++W)
            if(collected[W]==false && Graph->G[V][W]<INFINITY){
                if(Graph->G[V][W]<0)//无法处理负边的情况
                    return false;
                if(dist[V]+Graph->G[V][W]<dist[W]){
                    dist[W] = dist[V]+Graph->G[V][W];
                    path[W]=V;
                }
            }
    }
    return true;
}


//for DCG, bugs found--TBD
bool Floyd(MGraph Graph, WeightType D[][MaxVertexNum], Vertex path[][MaxVertexNum]){
    Vertex i, j, k;
    for (i = 0; i < Graph->Nv; ++i)
        for (j = 0; j < Graph->Nv; ++j){
            D[i][j] = Graph->G[i][j];
            if (D[i][j]<INFINITY)
                path[i][j]=i;
            else
                path[i][j]=-1;
        }
    for (int i = 0; i < Graph->Nv; ++i){
            for (int j = 0; j < Graph->Nv; ++j)
                printf("%d ", D[i][j]);
            printf("\n");
    }
    
    for (k = 0; k < Graph->Nv; ++k)
        for (i = 0; i < Graph->Nv; ++i)
            for (j = 0; j < Graph->Nv; ++j)
                if (D[i][k]+ D[k][j] < D[i][j]){
                    if (k==3)
                    {
                        printf("\n %d %d %d \n", D[i][k], D[k][j], D[i][j]);
                        printf("\n %d %d %d \n", k,i,j);
                    }
                    D[i][j] = D[i][k]+ D[k][j];
                    // if(i==j && D[i][j]<0)
                    //     return false;
                    path[i][j] = k;
                }
    return true;
    
}