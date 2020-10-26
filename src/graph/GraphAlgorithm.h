// DFS & BFS & Dijkstra & Floyd
#include "Graph.h"
#include <queue>//for BFS

//-------DFS & BFS-------
void Visit( Vertex V ){
    printf(" %d", V);
}

bool Visited_DFS[MaxVertexNum];
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

//-------Dijkstra-------
Vertex FindMinDist(MGraph Graph, int dist[], int collected[]){
    Vertex MinV, V;
    WeightType MinDist = INFINITY;

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

//-------Floyd-------
//for Directed Cyclic Graph, bugs found--TBD
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
                    if (k==3){
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

//-------Minimum Spanning Tree-------
//-------Prim-------
Vertex FindMinDist(MGraph Graph, WeightType dist[]){
    Vertex MinV;
    WeightType MinDist = INFINITY;

    for (Vertex V = 0; V < Graph->Nv; ++V)
        if (dist[V]!=0 && dist[V]<MinDist){
            MinDist = dist[V];
            MinV = V;
        }
    if (MinDist<INFINITY)
        return MinV;
    else
        return -1;    
}

int Prim(MGraph Graph, LGraph MST){
    WeightType dist[MaxVertexNum], TotalWeight;
    Vertex parent[MaxVertexNum], V, W;
    int VCount;
    Edge E;

    //初始化
    for (V = 0; V < Graph->Nv; ++V)
    {
        dist[V] = Graph->G[0][V];
        parent[V] = 0;
    }
    TotalWeight = 0;
    VCount = 0;
    MST = CreateLGraph(Graph->Nv);
    E = (Edge)malloc(sizeof(struct ENode));

    //把初始点0加入MST
    dist[0] = 0;
    ++VCount;
    parent[0] = -1;

    while (1){
        V = FindMinDist(Graph, dist);
        if (V==-1)
            break;
        
        //将顶点和边加入MST
        E->V1 = parent[V];
        E->V2 = V;
        E->Weight = dist[V];
        InsertEdge(MST, E);
        TotalWeight += dist[V];
        dist[V] = 0;
        ++VCount;
        
        for (W = 0; W < Graph->Nv; ++W)
            if (dist[W]!=0 && Graph->G[V][W]<INFINITY)
                if (Graph->G[V][W] < dist[W]){//dist[W]可能有无穷的
                    dist[W] = Graph->G[V][W];
                    parent[W] = V;
                }
    }

    if (VCount < Graph->Nv)
        TotalWeight = -1;
    return TotalWeight;
}